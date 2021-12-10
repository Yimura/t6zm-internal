#pragma once

namespace t6zm
{
	enum class eWeaponSlot
	{
		PRIMARY,
		SECONDARY,
		LETHAL,
		TACTICAL,
		MELEE
	};

	struct WeaponSlot
	{
		char name[32];
		eWeaponSlot slot;

		WeaponSlot(const char* slot_name, eWeaponSlot slot)
		{
			strcpy(this->name, slot_name);
			this->slot = slot;
		}
	};

	const WeaponSlot weapon_slots[] = {
		{ "Primary Weapon", eWeaponSlot::PRIMARY },
		{ "Secondary Weapon", eWeaponSlot::SECONDARY },
		{ "Lethals", eWeaponSlot::LETHAL },
		{ "Tacticals", eWeaponSlot::TACTICAL }
	};

	enum class eWeaponType
	{
		RIFLE_LIKE,
		LETHAL,
		TACTICAL,
		MELEE
	};

	enum class eWeapon
	{
		INVALID,
		DEFAULT_WEAPON,
		AK74U,
		MP5K,
		QCW05,
		AK74U_UPGRADED,
		MP5K_UPGRADED,
		QCW05_UPGRADED,
		M14 = 9,
		M16,
		SARITCH,
		XM8,
		TYPE95,
		TAR21,
		M14_UPGRADED,
		M16_UPGRADED,
		SARITCH_UPGRADED = 18,
		XM8_UPGRADED = 20,
		TYPE95_UPGRADED = 22,
		TAR21_UPGRADED = 24,
		_870MCS = 26,
		ROTTWEIL72,
		SAIGA12,
		SRM1216,
		_870MCS_UPGRADED,
		ROTTWEIL72_UPGRADED,
		SAIGA12_UPGRADED,
		SRM1216_UPGRADED,
		GALIL,
		FNFAL,
		RPD,
		HAMR,
		GALIL_UPGRADED,
		FNFAL_UPGRADED,
		RPD_UPGRADED,
		HAMR_UPGRADED,
		DSR50,
		BARRETM82,
		DSR50_UPGRADED,
		BARRETM82_UPGRADED,
		KNIFE,
		M1911,
		PYTHON,
		JUDGE,
		KARD,
		FIVESEVEN,
		BERETTA93R,
		FIVESEVENDW,
		M1911_UPGRADED = 55,
		PYTHON_UPGRADED = 57,
		JUDGE_UPGRADED,
		KARD_UPGRADED,
		FIVESEVEN_UPGRADED,
		BERETTA93R_UPGRADED,
		FIVESEVENDW_UPGRADED,
		USRPG = 64,
		M32,
		USRPG_UPGRADED,
		M32_UPGRADED,
		RAY_GUN,
		JETGUN,
		RIOTSHIELD,
		TAZER_KNUCKLES,
		KNIFE_BALLISTIC,
		KNIFE_BALLISTIC_UPGRADED,
		KNIFE_BALLISTIC_BOWIE,
		KNIFE_BALLISTIC_BOWIE_UPGRADED,
		RAYGUN_MARK2,
		RAYGUN_MARK2_UPGRADED,
		RAYGUN_UPGRADED,
		FRAG_GRENADE,
		STICKY_GRENADE,
		CYMBAL_MONKEY,
		EMP_GRENADE,
		CLAYMORE,
		KNIFE_BALLISTIC_NO_MELEE,
		KNIFE_BALLISTIC_NO_MELEE_UPGRADED,
		EQUIP_TURBINE,
		EQUIP_TURRET,
		EQUIP_ELECTRIC_TRAP,
		ZOMBIE_BUILDER,
		BUILDABLE_PIECE,
		SYRETTE,
		ZOMBIE_KNUCKLE_CRACK,
		ZOMBIE_PERK_DOUBLETAP,
		ZOMBIE_PERK_JUGG,
		ZOMBIE_PERK_MARATHON,
		ZOMBIE_PERK_REVIVE,
		ZOMBIE_PERK_SLEIGHT,
		ZOMBIE_PERK_TOMBSTONE,
		ZOMBIE_FISTS,
		ZOMBIE_TAZER_FLOURISH,
		BOWIE_KNIFE,
		ZOMBIE_BOWIE_FLOURISH,
		DEATH_THROE,
		DEATH_SELF
	};
}