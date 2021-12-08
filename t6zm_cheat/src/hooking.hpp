#pragma once
#include "common.hpp"
#include "hooking/detour_hook.hpp"

namespace t6zm
{
	struct hooks
	{
		static constexpr auto swapchain_present_index = 8;
		static constexpr auto swapchain_resizebuffers_index = 13;
		static HRESULT __stdcall swapchain_present(IDXGISwapChain* swapchain, UINT sync_interval, UINT flags);
		static HRESULT __stdcall swapchain_resizebuffers(IDXGISwapChain* swapchain, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags);

		static LRESULT wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		static BOOL set_cursor_pos(int x, int y);
	};

	struct minhook_keepalive
	{
		minhook_keepalive();
		~minhook_keepalive();
	};

	class hooking
	{
		friend hooks;
	public:
		explicit hooking();
		~hooking();

		void enable();
		void disable();

	private:
		bool m_enabled{};
		minhook_keepalive m_minhook_keepalive;

		WNDPROC m_og_wndproc;
		detour_hook m_set_cursor_pos_hook;
		detour_hook m_swapchain_present_hook;
		detour_hook m_swapchain_resizebuffers_hook;
	};

	inline hooking* g_hooking{};
}
