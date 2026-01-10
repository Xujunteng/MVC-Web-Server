// 筛选选项提供类，提供元素、地区、武器、星级等筛选选项
#pragma once
#include<vector>
#include<string>

class FilterOptions {
public:
	// 获取所有元素类型选项
	static const std::vector<std::string>& getElements();
	// 获取所有地区选项
	static const std::vector<std::string>& getRegions();
	// 获取所有武器类型选项
	static const std::vector<std::string>& getWeapons();
	// 获取所有星级选项
	static const std::vector<std::string>& getStars();
};
