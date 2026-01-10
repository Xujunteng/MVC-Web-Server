// 角色筛选器实现
#include"CharacterFilter.h"

// 根据多个条件筛选角色列表
std::vector<Character> CharacterFilter::filter(const std::vector<Character>& all,
												const std::string& element,
												const std::string& region,
												const std::string& weapon,
												const std::string& stars) {
	std::vector<Character> result;
	// 遍历所有角色，逐一检查是否满足筛选条件
	for (const auto& c : all) {
		bool match = true;
		// 检查元素是否匹配（非空则必须相等）
		if (!element.empty() && c.element != element) match = false;
		// 检查地区是否匹配
		if (!region.empty() && c.from != region) match = false;
		// 检查武器是否匹配
		if (!weapon.empty() && c.weapon != weapon) match = false;
		// 检查星级是否匹配
		if (!stars.empty() && c.stars != stars) match = false;
		// 所有条件都满足，加入结果集
		if (match) {
			result.push_back(c);
		}
	}
	return result;
}
