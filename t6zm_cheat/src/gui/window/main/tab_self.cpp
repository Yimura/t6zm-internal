#include "gui/window/main/main_tabs.hpp"
#include "pointers.hpp"
#include "settings.hpp"

namespace t6zm
{
	void tab_main::tab_self()
	{
		if (ImGui::BeginTabItem("Self"))
		{
			if (ImGui::Checkbox("God Mode", &g_settings->self.godmode))
				g_pointers->m_player->m_max_health = g_settings->self.godmode ? INT_MAX : 100;
			ImGui::Checkbox("No Clip", &g_settings->self.noclip);

			ImGui::DragInt("Money", (int*)&g_pointers->m_player->m_money, 0, 5555);

			ImGui::EndTabItem();
		}
	}
}