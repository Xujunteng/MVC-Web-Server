#include"FilterOptions.h"

const std::vector<std::string>& FilterOptions::getElements() {
	static const std::vector<std::string> elements = {u8"火", u8"水", u8"冰", u8"雷", u8"风", u8"草", u8"岩"};
	return elements;
}

const std::vector<std::string>& FilterOptions::getRegions() {
	static const std::vector<std::string> regions = {u8"蒙德", u8"璃月", u8"稻妻", u8"须弥", u8"枫丹", u8"纳塔", u8"至冬", u8"挪德卡莱", u8"群星"};
	return regions;
}

const std::vector<std::string>& FilterOptions::getWeapons() {
	static const std::vector<std::string> weapons = {u8"单手剑", u8"双手剑", u8"长柄武器", u8"弓", u8"法器"};
	return weapons;
}

const std::vector<std::string>& FilterOptions::getStars() {
	static const std::vector<std::string> stars = {u8"四星", u8"五星"};
	return stars;
}
