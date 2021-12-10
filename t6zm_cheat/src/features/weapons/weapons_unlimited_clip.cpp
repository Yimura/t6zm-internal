#include "features.hpp"

namespace t6zm
{
	void features::weapons_unlimited_clip()
	{
		if (g_settings->weapons.unlimited_clip)
		{
			g_pointers->m_player->m_primary_clip = 69;
			g_pointers->m_player->m_primary_akimbo_clip = 69;
			g_pointers->m_player->m_secondary_clip = 69;
			g_pointers->m_player->m_secondary_akimbo_clip = 69;
		}
	}
}