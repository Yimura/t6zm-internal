#include "gui/window.hpp"
#include "main/main_tabs.hpp"
#include "pointers.hpp"

namespace t6zm
{
	void window::main_menu()
	{
		ImGui::SetNextWindowSize({ 800, 840 }, ImGuiCond_FirstUseEver);
		if (g_settings->window.main && ImGui::Begin("Main Menu"))
		{
			ImGui::BeginTabBar("main_menu_tabbar");
			tab_main::tab_self();
			tab_main::tab_weapons();
			ImGui::EndTabBar();

			ImGui::End();
		}
	}
}