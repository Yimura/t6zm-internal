#pragma once
#include "common.hpp"
#include <imgui.h>
#include <wrl/client.h>

namespace t6zm
{
	class renderer
	{
	public:
		explicit renderer();
		~renderer();

		bool m_init = false;
		bool init(IDXGISwapChain* swapchain);
		void imgui_init();

		void on_present();

		void pre_reset();
		void post_reset();

		void wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	public:
		ImFont* m_font;
		ImFont* m_monospace_font;
	};

	inline renderer* g_renderer{};
}
