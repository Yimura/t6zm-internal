#pragma once
#include "common.hpp"

namespace t6zm
{
	class pointers
	{
	public:
		explicit pointers();
		~pointers();
	public:
		HWND m_hwnd{};

		uint32_t* m_swapchain_methods = NULL;

	private:
		bool get_swapchain();

	};

	inline pointers* g_pointers{};
}
