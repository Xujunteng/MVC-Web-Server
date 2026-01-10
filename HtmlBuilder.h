// HTML构建器类，用于构建各种HTML元素和页面片段
#pragma once
#include<string>
#include<vector>
#include"Dao.h"


class HtmlBuilder {
public:
	// 构建HTML下拉选项列表
	static std::string buildOptions(
		const std::vector<std::string>& items, const std::string& selected);
	// 构建角色表格的一行
	static std::string buildCharacterRow(const Character& c);
	// 构建完整的角色信息表格
	static std::string buildCharacterTable(
		const std::vector<Character>& characters);
	// 构建未找到角色的提示页面
	static std::string buildNotFoundPage(
		const std::string& element, const std::string& from, 
										 const std::string& weapon, const std::string& stars);
};
