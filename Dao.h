#pragma once
#include<vector>
#include<string>

struct Character {
	std::string name;
	std::string element;
	std::string from;
	std::string weapon;
	std::string stars;
	std::string birthday;
	std::string belong;
	std::string position;
	std::string constellation;
	std::string title;
};

class Dao {
public:
	static std::vector<Character>findAll();
};