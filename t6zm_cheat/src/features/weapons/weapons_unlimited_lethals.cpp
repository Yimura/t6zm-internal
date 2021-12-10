#include "features.hpp"

namespace t6zm
{
	void features::weapons_unlimited_lethals()
	{
		if (g_settings->weapons.unlimited_lethals)
		{
			g_pointers->m_player->m_lethal_ammo = 7;
		}
	}
}