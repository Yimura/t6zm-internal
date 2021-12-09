#include "features.hpp"

namespace t6zm
{
	void features::self_godmode()
	{
		if (g_settings->self.godmode)
		{
			g_pointers->m_player->m_max_health = INT_MAX;
		}
	}
}