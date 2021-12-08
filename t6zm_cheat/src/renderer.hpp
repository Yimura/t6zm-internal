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

		HWND m_hwnd = NULL;
		ID3D11Device* m_d3d_device = NULL;
		ID3D11DeviceContext* m_d3d_device_context = NULL;
		ID3D11RenderTargetView* m_d3d_render_target_view;
	private:
	};

	inline renderer* g_renderer{};
}
