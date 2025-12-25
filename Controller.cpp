#include"Controller.h"
#include"ModelAndView.h"
#include"Service.h"
#include"HtmlBuilder.h"
#include"FilterOptions.h"
#include"CharacterFilter.h"
#include<sstream>

std::string Controller::index(HttpRequest&) {
	ModelAndView mv;
	mv.viewName = "index.htm";
	mv.data["messages"] = u8"欢迎来到原神 观测枢！";
	return View::renderFromView(mv);
}

std::string Controller::characters(HttpRequest& req) {
	ModelAndView mv;
	mv.viewName = "characters.htm";

	auto allCharacters = Service::getAllCharacters();

	std::string filterElement = req.params["element"];
	std::string filterFrom = req.params["from"];
	std::string filterWeapon = req.params["weapon"];
	std::string filterStars = req.params["stars"];

	mv.data["elementOptions"] = HtmlBuilder::buildOptions(FilterOptions::getElements(), filterElement);
	mv.data["fromOptions"] = HtmlBuilder::buildOptions(FilterOptions::getRegions(), filterFrom);
	mv.data["weaponOptions"] = HtmlBuilder::buildOptions(FilterOptions::getWeapons(), filterWeapon);
	mv.data["starsOptions"] = HtmlBuilder::buildOptions(FilterOptions::getStars(), filterStars);

	auto filteredCharacters = CharacterFilter::filter(allCharacters, filterElement, filterFrom, filterWeapon, filterStars);
	bool hasFilter = !filterElement.empty() || !filterFrom.empty() || !filterWeapon.empty() || !filterStars.empty();

	std::stringstream ss;

	if (filteredCharacters.empty() && !hasFilter) {
		ss << u8"<p style=\"color: #666;\">共 " << allCharacters.size() << u8" 个角色</p>";
		ss << HtmlBuilder::buildCharacterTable(allCharacters);
	} else if (filteredCharacters.empty()) {
		ss << HtmlBuilder::buildNotFoundPage(filterElement, filterFrom, filterWeapon, filterStars);
	} else {
		ss << u8"<p style=\"color: #666;\">找到 " << filteredCharacters.size() << u8" 个角色</p>";
		ss << HtmlBuilder::buildCharacterTable(filteredCharacters);
	}

	mv.data["characters"] = ss.str();
	return View::renderFromView(mv);
}

std::string Controller::characterDetail(HttpRequest& req) {
    ModelAndView mv;
    mv.viewName = "characterdetails.htm";

    std::string name = req.params["name"];
    if (name.empty()) {
    	return HtmlBuilder::buildNotFoundPage("", "", "", "");
    }
    
    Character c = Service::getCharacterByName(name);
    
	if (c.name.empty()) {
		std::stringstream ss;
		ss << u8"<div style=\"text-align: center; padding: 40px;\">";
		ss << u8"<h2>未找到角色</h2>";
		ss << u8"<p>请检查角色名称是否正确。</p>";
		ss << u8"</div>";
		mv.data["characterDetail"] = ss.str();
		return View::renderFromView(mv);
	}

    std::stringstream ss;
    ss << "<h2>" << c.name << "</h2>";
    ss << "</div><div class=\"content\">";
    ss << "<div class=\"detail-layout\">";
    
    ss << "<div class=\"info-section\">";
    ss << "<ul class=\"info-list\">";
    ss << u8"<li><span class=\"label\">生日：</span><span class=\"value\">" << c.birthday << "</span></li>";
    ss << u8"<li><span class=\"label\">所属：</span><span class=\"value\">" << c.belong << "</span></li>";
	ss << u8"<li><span class=\"label\">定位：</span><span class=\"value\">" << c.position << "</span></li>";
    ss << u8"<li><span class=\"label\">武器类型：</span><span class=\"value\">" << c.weapon << "</span></li>";
    ss << u8"<li><span class=\"label\">命之座：</span><span class=\"value\">" << c.constellation << "</span></li>";
	ss << u8"<li><span class=\"label\">称号：</span><span class=\"value\">" << c.title << "</span></li>";
    ss << "</ul>";
    ss << "</div>";
    
	ss << "<div class=\"image-section\">";
	ss << "<img src=\"/images/" << c.name << ".jpg\" alt=\"" << c.name << "\" class=\"character-image\" onerror=\"this.onerror=null; this.src='/images/派蒙.jpg';\">"; // prevent infinite retry loop when fallback is missing
	ss << "</div>";
    
    ss << "</div>";

    mv.data["characterDetail"] = ss.str();
    return View::renderFromView(mv);
}