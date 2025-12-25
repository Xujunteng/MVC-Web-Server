#pragma once
#include<string>
#include<vector>
#include"Dao.h"


class HtmlBuilder {
public:
	static std::string buildOptions(const std::vector<std::string>& items, const std::string& selected);
	
	static std::string buildCharacterRow(const Character& c);
	
	static std::string buildCharacterTable(const std::vector<Character>& characters);
	
	static std::string buildNotFoundPage(const std::string& element, const std::string& from, 
										 const std::string& weapon, const std::string& stars);
};
