#include"CharacterFilter.h"

std::vector<Character> CharacterFilter::filter(const std::vector<Character>& all,
												const std::string& element,
												const std::string& region,
												const std::string& weapon,
												const std::string& stars) {
	std::vector<Character> result;
	for (const auto& c : all) {
		bool match = true;
		if (!element.empty() && c.element != element) match = false;
		if (!region.empty() && c.from != region) match = false;
		if (!weapon.empty() && c.weapon != weapon) match = false;
		if (!stars.empty() && c.stars != stars) match = false;
		if (match) {
			result.push_back(c);
		}
	}
	return result;
}
