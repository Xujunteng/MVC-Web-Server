#include"Dao.h"
#include<fstream>
#include<sstream>

namespace {
    Character parseCharacterLine(const std::string& line) {
        std::stringstream ss(line);
        Character c;
        getline(ss, c.name, ',');
        getline(ss, c.element, ',');
        getline(ss, c.from, ',');
        getline(ss, c.weapon, ',');
        getline(ss, c.stars, ',');
        getline(ss, c.birthday, ',');
        getline(ss, c.belong, ',');
        getline(ss, c.position, ',');
        getline(ss, c.constellation, ',');
        getline(ss, c.title, ',');
        return c;
    }
}

std::vector<Character>Dao::findAll() {
	std::vector<Character>result;
	std::ifstream infile("Dao/characters.csv");
	if (!infile.is_open()) {
		return result;  
	}
	std::string line;
	if (!getline(infile, line)) {
		return result;  
	}
	while (getline(infile, line)) {
		if (line.empty()) continue;
		result.push_back(parseCharacterLine(line));
	}
	return result;
}