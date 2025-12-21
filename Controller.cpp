#include"Controller.h"
#include"ModelAndView.h"
#include"Service.h"
#include<sstream>

std::string Controller::index(HttpRequest&) {
	ModelAndView mv;
	mv.viewName = "index.htm";
	mv.data["messages"] = u8"欢迎来到原神 观测枢！";
	return View::renderFromView(mv);
}

std::string Controller::characters(HttpRequest&) {
	ModelAndView mv;
	mv.viewName = "characters.htm";

	auto characters = Service::getAllCharacters();

	std::stringstream ss;
	ss << u8"<table border='1'><tr><th>姓名</th><th>元素</th><th>地区</th><th>武器</th><th>星级</th></tr>";
	for (const auto& c : characters) {
		ss << "<tr>";
		ss << "<td><a href=\"/character?name=" << c.name << "\">" << c.name << "</a></td>";
		ss << "<td>" << c.element << "</td>";
		ss << "<td>" << c.from << "</td>";
		ss << "<td>" << c.weapon << "</td>";
		ss << "<td>" << c.stars << "</td>";
		ss << "</tr>";
	}
	ss << "</table>";

	mv.data["characters"] = ss.str();
	return View::renderFromView(mv);
}

std::string Controller::characterDetail(HttpRequest& req) {
    ModelAndView mv;
    mv.viewName = "characterdetails.htm";

    std::string name = req.params["name"];
    Character c = Service::getCharacterByName(name);

    std::stringstream ss;
    ss << "<h2>" << c.name << "</h2>";
    ss << "<ul>";
    ss << "<li>生日：" << c.birthday << "</li>";
    ss << "<li>所属：" << c.belong << "</li>";
	ss << "<li>定位：" << c.position << "</li>";
    ss << "<li>武器类型：" << c.weapon << "</li>";
    ss << "<li>命之座：" << c.constellation << "</li>";
	ss << "<li>称号：" << c.title << "</li>";
    ss << "</ul>";
    ss << "<a href=\"/View/characters\">返回角色列表</a>";

    mv.data["characterDetail"] = ss.str();
    return View::renderFromView(mv);
}