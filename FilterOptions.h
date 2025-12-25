#pragma once
#include<vector>
#include<string>

class FilterOptions {
public:
	static const std::vector<std::string>& getElements();
	static const std::vector<std::string>& getRegions();
	static const std::vector<std::string>& getWeapons();
	static const std::vector<std::string>& getStars();
};
