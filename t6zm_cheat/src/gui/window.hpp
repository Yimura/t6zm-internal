#pragma once
#include <imgui.h>
#include "settings.hpp"

namespace t6zm
{
	struct window
	{
		static void top_bar();
		static void main_menu();
		static void log();

		static void draw_all()
		{
			window::top_bar();

			window::log();

			window::main_menu();
		}
	};
}