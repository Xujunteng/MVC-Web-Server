// 角色筛选器类，提供角色数据的多条件筛选功能
#pragma once
#include<vector>
#include<string>
#include"Dao.h"

class CharacterFilter {
public:
	// 根据元素、地区、武器、星级筛选角色列表
	static std::vector<Character> filter(const std::vector<Character>& all,
										 const std::string& element,
										 const std::string& region,
										 const std::string& weapon,
										 const std::string& stars);
};
