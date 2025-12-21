#pragma once
#include"Dao.h"

class Service {
public:
	static std::vector<Character> getAllCharacters();
	static Character getCharacterByName(const std::string& name);
};