#pragma once
#include "logger.hpp"

namespace t6zm
{
	class settings;
	inline settings* g_settings{};

	class settings {
		nlohmann::json default_options;
		nlohmann::json options;

		struct self
		{
			bool godmode = false;
			bool noclip = false;
		};

		struct weapons
		{
			bool unlimited_ammo = false;
			bool unlimited_clip = false;
			bool unlimited_lethals = false;
			bool unlimited_tacticals = false;
		};

		struct window {
			bool log = false;
			bool main = true;
		};

	public:
		settings()
		{
			g_settings = this;
		}

		~settings()
		{
			g_settings = nullptr;
		}

		self self{};
		weapons weapons{};
		window window{};

		void from_json(const nlohmann::json& j)
		{
			this->self.godmode = j["self"]["godmode"];
			this->self.noclip = j["self"]["noclip"];

			this->weapons.unlimited_ammo = j["weapons"]["unlimited_ammo"];
			this->weapons.unlimited_clip = j["weapons"]["unlimited_clip"];
			this->weapons.unlimited_clip = j["weapons"]["unlimited_lethals"];
			this->weapons.unlimited_clip = j["weapons"]["unlimited_tacticals"];

			this->window.log = j["window"]["log"];
			this->window.main = j["window"]["main"];
		}

		nlohmann::json to_json()
		{
			return nlohmann::json{
				{
					"self", {
						{ "godmode", this->self.godmode },
						{ "noclip", this->self.noclip }
					}
				},
				{
					"weapons", {
						{ "unlimited_ammo", this->weapons.unlimited_ammo },
						{ "unlimited_clip", this->weapons.unlimited_clip },
						{ "unlimited_lethals", this->weapons.unlimited_lethals },
						{ "unlimited_tacticals", this->weapons.unlimited_tacticals }
					}
				},
				{
					"window", {
						{ "log", this->window.log },
						{ "main", this->window.main }
					}
				}
			};
		}

		void attempt_save()
		{
			nlohmann::json& j = this->to_json();

			if (deep_compare(this->options, j, true))
				this->save();
		}

		bool load()
		{
			this->default_options = this->to_json();

			std::string settings_file = std::getenv("appdata");
			settings_file += this->settings_location;

			std::ifstream file(settings_file);

			if (!file.is_open())
			{
				this->write_default_config();

				file.open(settings_file);
			}

			try
			{
				file >> this->options;
			}
			catch (const std::exception&)
			{
				g_log->warning("SETTINGS", "Detected corrupt settings, writing default config...");

				this->write_default_config();

				return this->load();
			}

			bool should_save = this->deep_compare(this->options, this->default_options);

			this->from_json(this->options);

			if (should_save)
			{
				g_log->verbose("SETTINGS", "Updating settings...");
				save();
			}

			return true;
		}

	private:
		const char* settings_location = "\\t6zm_cheat\\settings.json";

		bool deep_compare(nlohmann::json& current_settings, const nlohmann::json& default_settings, bool compare_value = false)
		{
			bool should_save = false;

			for (auto& e : default_settings.items())
			{
				const std::string& key = e.key();

				if (current_settings.count(key) == 0 || (compare_value && current_settings[key] != e.value()))
				{
					current_settings[key] = e.value();

					should_save = true;
				}
				else if (current_settings[key].is_structured() && e.value().is_structured())
				{
					if (deep_compare(current_settings[key], e.value(), compare_value))
						should_save = true;
				}
				else if (!current_settings[key].is_structured() && e.value().is_structured()) {
					current_settings[key] = e.value();

					should_save = true;
				}
			}

			return should_save;
		}

		bool save()
		{
			std::string settings_file = std::getenv("appdata");
			settings_file += this->settings_location;

			std::ofstream file(settings_file, std::ios::out | std::ios::trunc);
			file << this->to_json().dump(4);
			file.close();

			return true;
		}

		bool write_default_config()
		{
			std::string settings_file = std::getenv("appdata");
			settings_file += this->settings_location;

			std::ofstream file(settings_file, std::ios::out);
			file << this->to_json().dump(4);
			file.close();

			return true;
		}
	};
}