#include"Dao.h"
#include<fstream>
#include<sstream>

std::vector<Character>Dao::findAll() {
	std::vector<Character>result;
	std::ifstream infile("Dao/characters.csv");
	std::string line;
	getline(infile, line);
	while (getline(infile, line)) {
		std::stringstream ss(line);
		std::string item;
		Character s;

		getline(ss, s.name, ',');
		getline(ss, s.element, ',');
		getline(ss, s.from, ',');
		getline(ss, s.weapon, ',');
		getline(ss, s.stars, ',');
		getline(ss, s.birthday, ',');
		getline(ss, s.belong, ',');
		getline(ss, s.position, ',');
		getline(ss, s.constellation, ',');
		getline(ss, s.title, ',');

		result.push_back(s);
	}
	return result;
}