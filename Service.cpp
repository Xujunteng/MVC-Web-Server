#include"Service.h"

std::vector<Character>Service::getAllCharacters() {
	return Dao::findAll();
}

Character Service::getCharacterByName(const std::string& name) {
    auto all = getAllCharacters();
    for (const auto& c : all) {
        if (c.name == name) return c;
    }
    return Character{};
}