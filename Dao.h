// 数据访问对象，负责从CSV文件读取角色数据
#pragma once
#include<vector>
#include<string>

// 角色数据结构
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
	// 从CSV文件读取所有角色数据
	static std::vector<Character>findAll();
};