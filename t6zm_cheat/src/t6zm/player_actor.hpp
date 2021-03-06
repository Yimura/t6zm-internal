#pragma once
#include "natives.hpp"

namespace t6zm
{
	class PlayerActor
	{
	public:
		uint32_t m_server_time; //0x0000
		char pad_0004[36]; //0x0004
		Vector3 m_origin; //0x0028
		Vector3 m_velocity; //0x0034
		char pad_0040[76]; //0x0040
		uint32_t m_gravity; //0x008C
		char pad_0090[4]; //0x0090
		uint32_t m_speed; //0x0094
		char pad_0098[352]; //0x0098
		Vector2 m_view_angles; //0x01F8
		char pad_0200[4]; //0x0200
		uint32_t m_player_height; //0x0204
		float m_player_height_f; //0x0208
		char pad_020C[44]; //0x020C
		uint32_t m_health; //0x0238
		char pad_023C[40]; //0x023C
		uint32_t m_primary_weapon; //0x0264
		char pad_0268[24]; //0x0268
		uint32_t m_lethal_weapon; //0x0280
		char pad_0284[24]; //0x0284
		uint32_t m_secondary_weapon; //0x029C
		char pad_02A0[24]; //0x02A0
		uint32_t m_tactical_weapon; //0x02B8
		char pad_02BC[24]; //0x02BC
		uint32_t m_melee_weapon; //0x02D4
		char pad_02D8[280]; //0x02D8
		uint32_t m_primary_ammo; //0x03F0
		uint32_t m_secondary_ammo; //0x03F4
		uint32_t m_unk_ammo; //0x03F8
		char pad_03FC[44]; //0x03FC
		uint32_t m_lethal_ammo; //0x0428
		uint32_t m_primary_clip; //0x042C
		uint32_t m_secondary_clip; //0x0430
		uint32_t m_primary_akimbo_clip; //0x0434
		uint32_t m_tactical_ammo; //0x0438
		char pad_043C[4]; //0x043C
		uint32_t m_secondary_akimbo_clip; //0x0440
		char pad_0444[80]; //0x0444
		bool m_can_interact; //0x0494
		char pad_0495[183]; //0x0495
		uint32_t m_perk_flags; //0x054C
		char pad_0550[20348]; //0x0550
		uint32_t m_max_health; //0x54CC
		char pad_54D0[100]; //0x54D0
		char m_name[16]; //0x5534
		char pad_5544[132]; //0x5544
		uint32_t m_money; //0x55C8
	}; //Size: 0x55CC
	static_assert(sizeof(PlayerActor) == 0x55CC);
}