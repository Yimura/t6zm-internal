#pragma once
#include "pointers.hpp"
#include "settings.hpp"

namespace t6zm
{
	struct features
	{
		static void self_noclip();

		static void script_tick()
		{
			features::self_noclip();
		}
		static void script_run()
		{
			while (g_running)
				features::script_tick();
		}
	};
}