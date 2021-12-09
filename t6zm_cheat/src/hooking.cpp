#include "common.hpp"
#include "logger.hpp"
#include "gui.hpp"
#include "hooking.hpp"
#include "memory/module.hpp"
#include "pointers.hpp"
#include "renderer.hpp"

#include <MinHook.h>

namespace t6zm
{
	hooking::hooking() :
		m_swapchain_present_hook("SwapChainPresent", (void*)g_pointers->m_swapchain_methods[hooks::swapchain_present_index], &hooks::swapchain_present),
		m_swapchain_resizebuffers_hook("SwapChainResizeBuffers", (void*)g_pointers->m_swapchain_methods[hooks::swapchain_resizebuffers_index], &hooks::swapchain_resizebuffers),
		
		m_set_cursor_pos_hook("SetCursorPos", memory::module("user32.dll").get_export("SetCursorPos").as<void*>(), &hooks::set_cursor_pos)
	{
		g_hooking = this;
	}

	hooking::~hooking()
	{
		if (m_enabled)
			disable();

		g_hooking = nullptr;
	}

	void hooking::enable()
	{
		m_swapchain_present_hook.enable();
		m_swapchain_resizebuffers_hook.enable();
		m_og_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(g_pointers->m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&hooks::wndproc)));
		//m_set_cursor_pos_hook.enable();

		m_enabled = true;
	}

	void hooking::disable()
	{
		m_enabled = false;

		//m_set_cursor_pos_hook.disable();
		SetWindowLongPtrW(g_pointers->m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_og_wndproc));
		m_swapchain_resizebuffers_hook.disable();
		m_swapchain_present_hook.disable();
	}

	minhook_keepalive::minhook_keepalive()
	{
		MH_Initialize();
	}

	minhook_keepalive::~minhook_keepalive()
	{
		MH_Uninitialize();
	}

	HRESULT __stdcall hooks::swapchain_present(IDXGISwapChain* this_, UINT sync_interval, UINT flags)
	{
		if (g_running && (g_renderer->m_init || g_renderer->init(this_)))
			g_renderer->on_present();

		return g_hooking->m_swapchain_present_hook.get_original<decltype(&swapchain_present)>()(this_, sync_interval, flags);
	}

	HRESULT __stdcall hooks::swapchain_resizebuffers(IDXGISwapChain* this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags)
	{
		if (g_running)
		{
			g_renderer->pre_reset();

			auto result = g_hooking->m_swapchain_resizebuffers_hook.get_original<decltype(&swapchain_resizebuffers)>()
				(this_, buffer_count, width, height, new_format, swapchain_flags);

			if (SUCCEEDED(result))
				g_renderer->post_reset();

			return result;
		}

		return g_hooking->m_swapchain_resizebuffers_hook.get_original<decltype(&swapchain_resizebuffers)>()
			(this_, buffer_count, width, height, new_format, swapchain_flags);
	}

	LRESULT hooks::wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		if (g_running)
			g_renderer->wndproc(hwnd, msg, wparam, lparam);

		return CallWindowProcW(g_hooking->m_og_wndproc, hwnd, msg, wparam, lparam);
	}

	BOOL hooks::set_cursor_pos(int x, int y)
	{
		if (g_gui.m_opened)
			return TRUE;

		return g_hooking->m_set_cursor_pos_hook.get_original<decltype(&set_cursor_pos)>()(x, y);
	}
}
