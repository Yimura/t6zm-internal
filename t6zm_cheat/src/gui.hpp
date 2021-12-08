#pragma once
#include "common.hpp"

namespace t6zm
{
	class gui
	{
	public:
		void dx_init();
		void dx_on_tick();

		void script_init();
		void script_on_tick();
		static void script_func();
	public:
		bool m_opened = false;
	};

	inline gui g_gui;
}
