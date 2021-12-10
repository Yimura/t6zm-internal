#include "gui/window/main/main_tabs.hpp"
#include "pointers.hpp"
#include "settings.hpp"
#include "util/weapons.hpp"

namespace t6zm
{
	void tab_main::tab_weapons()
	{
		if (ImGui::BeginTabItem("Weapons"))
		{
			if (ImGui::TreeNode("Unlimited Stuffs"))
			{
				ImGui::Checkbox("Unlimited Ammo", &g_settings->weapons.unlimited_ammo);
				ImGui::Checkbox("Unlimited Clip", &g_settings->weapons.unlimited_clip);

				ImGui::Checkbox("Unlimited Lethals", &g_settings->weapons.unlimited_lethals);
				ImGui::Checkbox("Unlimited Tacticals", &g_settings->weapons.unlimited_tacticals);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Give Weapon"))
			{
				static eWeaponSlot active_slot = eWeaponSlot::PRIMARY;

				if (ImGui::BeginCombo("Weapon Slot", weapon_slots[(int)active_slot].name))
				{
					for (const WeaponSlot& weapon_slot : weapon_slots)
					{
						if (ImGui::Selectable(weapon_slot.name, weapon_slot.slot == active_slot))
							active_slot = weapon_slot.slot;

						if (weapon_slot.slot == active_slot)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				static uint32_t weapon_id = 47;
				ImGui::InputInt("WeaponID", (int*)&weapon_id);

				if (ImGui::Button("Give"))
					weapons::equip_weapon((eWeapon)weapon_id, active_slot);

				ImGui::TreePop();
			}

			ImGui::EndTabItem();
		}
	}
}