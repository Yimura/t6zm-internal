#include "features.hpp"

namespace t6zm
{
	void features::weapons_unlimited_ammo()
	{
		if (g_settings->weapons.unlimited_ammo)
		{
			g_pointers->m_player->m_primary_ammo = 420;
			g_pointers->m_player->m_secondary_ammo = 420;
		}
	}
}