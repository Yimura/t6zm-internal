#include "common.hpp"
#include "detour_hook.hpp"
#include "logger.hpp"
#include "memory/handle.hpp"
#include <MinHook.h>

namespace t6zm
{
	detour_hook::detour_hook(std::string name, void* target, void* detour) :
		m_name(std::move(name)),
		m_target(target),
		m_detour(detour)
	{
		fix_hook_address();

		if (auto status = MH_CreateHook(m_target, m_detour, &m_original); status == MH_OK)
		{
			g_log->verbose("DETOUR_HOOK", "Created hook '%s'.", m_name.c_str());
			//LOG(INFO_TO_FILE) << "Created hook '" << m_name << "'.";
		}
		else
		{
			g_log->error("DETOUR_HOOK", "Failed to create hook '%s' at %x (error: %s)", m_name.c_str(), reinterpret_cast<std::uintptr_t>(m_target), MH_StatusToString(status));
			//throw std::runtime_error(fmt::format("Failed to create hook '{}' at 0x{:X} (error: {})", m_name, reinterpret_cast<std::uintptr_t>(m_target), MH_StatusToString(status)));
		}
	}

	detour_hook::~detour_hook() noexcept
	{
		if (m_target)
		{
			MH_RemoveHook(m_target);
		}

		g_log->info("DETOUR_HOOK", "Removed hook '%s'.", m_name.c_str());
		//LOG(INFO) << "Removed hook '" << m_name << "'.";
	}

	void detour_hook::enable()
	{
		if (auto status = MH_EnableHook(m_target); status == MH_OK)
		{
			g_log->info("DETOUR_HOOK", "Enabled hook '%s'.", m_name.c_str());
			//LOG(INFO) << "Enabled hook '" << m_name << "'.";
		}
		else
		{
			g_log->error("DETOUR_HOOK", "Failed to enable hook '%s' at %x (error: %s)", m_name.c_str(), reinterpret_cast<std::uintptr_t>(m_target), MH_StatusToString(status));
			//throw std::runtime_error(fmt::format("Failed to enable hook 0x{:X} ({})", reinterpret_cast<std::uintptr_t>(m_target), MH_StatusToString(status)));
		}
	}

	void detour_hook::disable()
	{
		if (auto status = MH_DisableHook(m_target); status == MH_OK)
		{
			g_log->verbose("DETOUR_HOOK", "Disabled hook '%s'", m_name.c_str());
			//LOG(INFO_TO_FILE) << "Disabled hook '" << m_name << "'.";
		}
		else
		{
			g_log->warning("DETOUR_HOOK", "Failed to disable hook '%s'", m_name.c_str());
			//LOG(WARNING) << "Failed to disable hook '" << m_name << "'.";
		}
	}

	DWORD exp_handler(PEXCEPTION_POINTERS exp, std::string const& name)
	{
		return exp->ExceptionRecord->ExceptionCode == STATUS_ACCESS_VIOLATION
			? EXCEPTION_EXECUTE_HANDLER
			: EXCEPTION_CONTINUE_SEARCH;
	}

	void detour_hook::fix_hook_address()
	{
		__try
		{
			auto ptr = memory::handle(m_target);
			while (ptr.as<std::uint8_t&>() == 0xE9)
			{
				ptr = ptr.add(1).rip();
			}

			m_target = ptr.as<void*>();
		}
		__except (exp_handler(GetExceptionInformation(), m_name))
		{
			[this]()
			{
				g_log->error("DETOUR_HOOK", "Failed to fix hook address for '%s'", m_name.c_str());
				//throw std::runtime_error(fmt::format("Failed to fix hook address for '{}'", m_name));
			}();
		}
	}
}
