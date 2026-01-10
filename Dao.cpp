// 数据访问对象实现，从CSV文件读取角色数据
#include"Dao.h"
#include<fstream>
#include<sstream>

namespace {
    // 解析CSV中的一行数据为Character对象
    Character parseCharacterLine(const std::string& line) {
        // 创建字符串流用于分割CSV
        std::stringstream ss(line);
        Character c;
        // 按逗号分隔读取各字段
        getline(ss, c.name, ',');          // 角色名称
        getline(ss, c.element, ',');       // 元素属性
        getline(ss, c.from, ',');          // 所属地区
        getline(ss, c.weapon, ',');        // 武器类型
        getline(ss, c.stars, ',');         // 星级
        getline(ss, c.birthday, ',');      // 生日
        getline(ss, c.belong, ',');        // 所属组织
        getline(ss, c.position, ',');      // 战斗定位
        getline(ss, c.constellation, ','); // 命之座
        getline(ss, c.title, ',');         // 称号
        return c;
    }
}

// 读取CSV文件并返回所有角色数据
std::vector<Character>Dao::findAll() {
	// 创建结果容器
	std::vector<Character>result;
	// 打开CSV文件
	std::ifstream infile("Dao/characters.csv");
	if (!infile.is_open()) {
		// 文件打开失败，返回空列表
		return result;  
	}
	std::string line;
	// 跳过第一行表头
	if (!getline(infile, line)) {
		// 文件为空，返回空列表
		return result;  
	}
	// 逐行读取数据
	while (getline(infile, line)) {
		// 跳过空行
		if (line.empty()) continue;
		// 解析并添加到结果集
		result.push_back(parseCharacterLine(line));
	}
	return result;
}