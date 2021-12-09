#include "gui/window.hpp"
#include "renderer.hpp"
#include "logger.hpp"

namespace t6zm
{
	static int last_log_count;
	void window::log()
	{
		ImGui::SetNextWindowSize({ 500, 250 }, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos({ 50, 50 }, ImGuiCond_FirstUseEver);
		if (g_settings->window.log && ImGui::Begin("Log"))
		{
			ImGui::PushFont(g_renderer->m_monospace_font);
			auto msgs = g_log->get_messages();

			for (size_t i = 0; i < msgs.second; i++)
			{
				ImGui::TextUnformatted(msgs.first[i].get());
			}

			if (last_log_count != msgs.second)
			{
				last_log_count = msgs.second;
				ImGui::SetScrollHereY(1.f);
			}

			ImGui::PopFont();

			ImGui::End();
		}
	}
}
