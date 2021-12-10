#pragma once
#include "t6zm/weapons.hpp"

namespace t6zm
{
	struct weapons
	{
		static void equip_weapon(eWeapon weapon, eWeaponSlot weapon_slot)
		{
			switch (weapon_slot)
			{
			case eWeaponSlot::PRIMARY:
				g_pointers->m_player->m_primary_weapon = (uint32_t)weapon;
				break;
			case eWeaponSlot::SECONDARY:
				g_pointers->m_player->m_secondary_weapon = (uint32_t)weapon;
				break;
			case eWeaponSlot::LETHAL:
				g_pointers->m_player->m_lethal_weapon = (uint32_t)weapon;
				break;
			case eWeaponSlot::TACTICAL:
				g_pointers->m_player->m_tactical_weapon = (uint32_t)weapon;
			}
		}

		static bool is_akimbo(uint32_t weapon_id)
		{
			const eWeapon akimbo_weapons[] = {
				eWeapon::FIVESEVENDW,
				eWeapon::FIVESEVENDW_UPGRADED,
				eWeapon::M1911_UPGRADED
			};

			for (const eWeapon& weapon : akimbo_weapons)
				if (weapon == (eWeapon)weapon_id) return true;
			return false;
		}
	};
}