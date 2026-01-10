// HTML构建器实现
#include"HtmlBuilder.h"
#include<sstream>

// 构建下拉选择框的选项HTML
std::string HtmlBuilder::buildOptions(
		const std::vector<std::string>& items, const std::string& selected) {
	std::stringstream ss;
	// 遍历所有选项项
	for (const auto& item : items) {
		// 添加option标签和值
		ss << "<option value=\"" << item << "\"";
		// 检查是否是选中项: 是则加selected属性
		if (selected == item) {
			ss << " selected";
		}
		// 添加选项文字内容和结束标签
		ss << ">" << item << "</option>";
	}
	return ss.str();
}

// 构建角色表格的一行HTML
std::string HtmlBuilder::buildCharacterRow(const Character& c) {
	std::stringstream ss;
	// 开始表格行
	ss << "<tr>";
	// 第1列: 角色名称成为可点击链接
	ss << "<td><a href=\"/character?name=" << c.name << "\">" << c.name << "</a></td>";
	// 第2列: 元素信息
	ss << "<td>" << c.element << "</td>";
	// 第3列: 地区信息
	ss << "<td>" << c.from << "</td>";
	// 第4列: 武器信息
	ss << "<td>" << c.weapon << "</td>";
	// 第5列: 星级信息
	ss << "<td>" << c.stars << "</td>";
	// 结束表格行
	ss << "</tr>";
	return ss.str();
}

// 构建完整的角色信息表格HTML
std::string HtmlBuilder::buildCharacterTable(
		const std::vector<Character>& characters) {
	std::stringstream ss;
	ss << "<table border='1'><tr><th>姓名</th><th>元素</th>"
	   << "<th>地区</th><th>武器</th><th>星级</th></tr>";
	for (const auto& c : characters) {
		ss << buildCharacterRow(c);
	}
	ss << "</table>";
	return ss.str();
}

// 构建未找到角色的提示页面HTML
std::string HtmlBuilder::buildNotFoundPage(
		const std::string& element, const std::string& from,
		const std::string& weapon, const std::string& stars) {
	std::stringstream ss;
	// 构建提示容器外层div
	ss << "<div style=\"text-align: center; padding: 40px;\">";
	// 显示主标题
	ss << "<h2>未找到匹配的角色</h2>";
	// 显示筛选条件
	ss << "<p style=\"font-size: 16px; color: #666;\">当前筛选条件：";
	// 按顺序添加每个已选筛选条件
	if (!element.empty()) { ss << u8"元素=" << element << " "; }
	if (!from.empty()) { ss << u8"地区=" << from << " "; }
	if (!weapon.empty()) { ss << u8"武器=" << weapon << " "; }
	if (!stars.empty()) { ss << u8"星级=" << stars << " "; }
	ss << u8"</p>";
	// 提示修改筛选条件
	ss << u8"<p>请修改筛选条件重试</p>";
	// 结束提示段
	ss << u8"</div>";
	return ss.str();
}

