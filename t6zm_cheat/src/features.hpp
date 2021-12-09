#pragma once
#include "pointers.hpp"
#include "settings.hpp"

namespace t6zm
{
	struct features
	{
		static void self_godmode();

		static void script_tick()
		{
			features::self_godmode();

			std::this_thread::sleep_for(0ms);
		}
		static void script_run()
		{
			while (g_running)
				features::script_tick();
		}
	};
}