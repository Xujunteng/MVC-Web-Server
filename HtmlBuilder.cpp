#include"HtmlBuilder.h"
#include<sstream>

std::string HtmlBuilder::buildOptions(const std::vector<std::string>& items, const std::string& selected) {
	std::stringstream ss;
	for (const auto& item : items) {
		ss << "<option value=\"" << item << "\"";
		if (selected == item) {
			ss << " selected";
		}
		ss << ">" << item << "</option>";
	}
	return ss.str();
}

std::string HtmlBuilder::buildCharacterRow(const Character& c) {
	std::stringstream ss;
	ss << "<tr>";
	ss << "<td><a href=\"/character?name=" << c.name << "\">" << c.name << "</a></td>";
	ss << "<td>" << c.element << "</td>";
	ss << "<td>" << c.from << "</td>";
	ss << "<td>" << c.weapon << "</td>";
	ss << "<td>" << c.stars << "</td>";
	ss << "</tr>";
	return ss.str();
}

std::string HtmlBuilder::buildCharacterTable(const std::vector<Character>& characters) {
	std::stringstream ss;
	ss << "<table border='1'><tr><th>姓名</th><th>元素</th><th>地区</th><th>武器</th><th>星级</th></tr>";
	for (const auto& c : characters) {
		ss << buildCharacterRow(c);
	}
	ss << "</table>";
	return ss.str();
}

std::string HtmlBuilder::buildNotFoundPage(const std::string& element, const std::string& from,
											const std::string& weapon, const std::string& stars) {
	std::stringstream ss;
	ss << "<div style=\"text-align: center; padding: 40px;\">";
	ss << "<h2>未找到匹配的角色</h2>";
	ss << "<p style=\"font-size: 16px; color: #666;\">当前筛选条件：";
	if (!element.empty()) { ss << u8"元素=" << element << " "; }
	if (!from.empty()) { ss << u8"地区=" << from << " "; }
	if (!weapon.empty()) { ss << u8"武器=" << weapon << " "; }
	if (!stars.empty()) { ss << u8"星级=" << stars << " "; }
	ss << u8"</p>";
	ss << u8"<p>请修改筛选条件重试</p>";
	ss << u8"</div>";
	return ss.str();
}

