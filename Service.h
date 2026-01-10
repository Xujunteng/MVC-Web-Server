// 服务层类，处理业务逻辑
#pragma once
#include"Dao.h"

class Service {
public:
	// 获取所有角色数据
	static std::vector<Character> getAllCharacters();
	// 根据角色名称查询角色信息
	static Character getCharacterByName(const std::string& name);
};