// 筛选选项实现
#include"FilterOptions.h"

// 返回所有元素类型
const std::vector<std::string>& FilterOptions::getElements() {
	// 静态变量，第一次调用时初始化，后续返回同一个引用
	static const std::vector<std::string> elements = {
		// 按原神游戏中的元素类型排列
		u8"火",		// 火元素
		u8"水",		// 水元素
		u8"冰",		// 冰元素
		u8"雷",		// 雷元素
		u8"风",		// 风元素
		u8"草",		// 草元素
		u8"岩"		// 岩元素
	};
	return elements;
}

// 返回所有地区
const std::vector<std::string>& FilterOptions::getRegions() {
	// 静态变量存储所有可用地区
	static const std::vector<std::string> regions = {
		// 按游戏中的国家顺序排列
		u8"蒙德",		// 蒙德城邦
		u8"璃月",		// 璃月港
		u8"稻妻",		// 稻妻国
		u8"须弥",		// 须弥国
		u8"枫丹",		// 枫丹国
		u8"纳塔",		// 纳塔国
		u8"至冬",		// 至冬国
		u8"挪德卡莱",	// 挪德卡莱（虚拟国度）
		u8"群星"		// 群星（其他）
	};
	return regions;
}

// 返回所有武器类型
const std::vector<std::string>& FilterOptions::getWeapons() {
	// 静态变量存储所有可用武器类型
	static const std::vector<std::string> weapons = {
		// 游戏中的五大武器类型
		u8"单手剑",		// 单手剑
		u8"双手剑",		// 双手剑
		u8"长柄武器",	// 长柄武器（矛、戟等）
		u8"弓",			// 弓箭
		u8"法器"		// 法器（魔法武器）
	};
	return weapons;
}

// 返回所有星级选项
const std::vector<std::string>& FilterOptions::getStars() {
	// 静态变量存储所有稀有度等级
	static const std::vector<std::string> stars = {
		u8"四星",		// 四星稀有度
		u8"五星"		// 五星稀有度
	};
	return stars;
}
