#pragma once
#include "pointers.hpp"
#include "settings.hpp"

namespace t6zm
{
	struct features
	{
		static void self_noclip();

		static void weapons_unlimited_ammo();
		static void weapons_unlimited_clip();
		static void weapons_unlimited_lethals();
		static void weapons_unlimited_tacticals();

		static void script_tick()
		{
			features::self_noclip();

			features::weapons_unlimited_ammo();
			features::weapons_unlimited_clip();
			features::weapons_unlimited_lethals();
			features::weapons_unlimited_tacticals();
		}
		static void script_run()
		{
			while (g_running)
				features::script_tick();
		}
	};
}