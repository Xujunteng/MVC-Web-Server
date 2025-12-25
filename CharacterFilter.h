#pragma once
#include<vector>
#include<string>
#include"Dao.h"

class CharacterFilter {
public:
	static std::vector<Character> filter(const std::vector<Character>& all,
										 const std::string& element,
										 const std::string& region,
										 const std::string& weapon,
										 const std::string& stars);
};
