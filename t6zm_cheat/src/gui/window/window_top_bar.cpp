#include "gui/window.hpp"

namespace t6zm
{
	void window::top_bar()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Windows"))
			{
				ImGui::MenuItem("Main", nullptr, &g_settings->window.main);
				ImGui::MenuItem("Logs", nullptr, &g_settings->window.log);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Quit"))
			{
				if (ImGui::MenuItem("Unload"))
					g_running = false;

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}
}