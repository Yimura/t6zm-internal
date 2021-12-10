#include "features.hpp"

namespace t6zm
{
	void features::weapons_unlimited_tacticals()
	{
		if (g_settings->weapons.unlimited_tacticals)
		{
			g_pointers->m_player->m_tactical_ammo = 7;
		}
	}
}