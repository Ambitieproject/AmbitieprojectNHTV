#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <map>

#include "json.hpp"

using json = nlohmann::json;

namespace LVL {
	class Level {
	public:
		int level;
		std::vector<sf::Vector2f> Translations;

	public:
		void to_json(json& j) {
			j = json{ { "Level", level } };
		}

		void from_json(const json& j) {
			level = j.at("Level").get<int>();
		}
	};
}
