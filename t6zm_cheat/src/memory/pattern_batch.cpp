#include "common.hpp"
#include "logger.hpp"
#include "pattern_batch.hpp"
#include "range.hpp"

namespace memory
{
	using namespace t6zm;

	void pattern_batch::add(std::string name, pattern pattern, std::function<void(handle)> callback)
	{
		m_entries.emplace_back(std::move(name), std::move(pattern), std::move(callback));
	}

	void pattern_batch::run(range region)
	{
		bool all_found = true;
		for (auto& entry : m_entries)
		{
			if (auto result = region.scan(entry.m_pattern); entry.m_callback)
			{
				std::invoke(std::move(entry.m_callback), result);

				g_log->verbose("MEMORY", "Found '%s' t6zm.exe+%x", entry.m_name, result.as<DWORD32>() - region.begin().as<DWORD32>());
				//LOG(INFO) << "Found '" << entry.m_name << "' GTA5.exe+" << HEX_TO_UPPER(result.as<DWORD64>() - region.begin().as<DWORD64>());
				
				continue;
			}

			all_found = false;
			g_log->warning("MEMORY", "Failed to find '%s'.", entry.m_name);
			//LOG(WARNING) << "Failed to find '" << entry.m_name << "'.";
		}

		m_entries.clear();
		if (!all_found)
		{
			throw std::runtime_error("Failed to find some patterns.");
		}
	}
}
