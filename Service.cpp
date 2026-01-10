// 服务层实现
#include"Service.h"

// 获取所有角色列表
std::vector<Character>Service::getAllCharacters() {
	// 从数据层读取所有角色
	return Dao::findAll();
}

// 根据名称查找指定角色
Character Service::getCharacterByName(const std::string& name) {
    // 获取所有角色数据
    auto all = getAllCharacters();
    // 遍历查找匹配的角色
    for (const auto& c : all) {
        // 找到匹配名称的角色，立即返回
        if (c.name == name) return c;
    }
    // 未找到则返回空对象
    return Character{};
}