// 控制器实现，处理各种HTTP请求
#include"Controller.h"
#include"ModelAndView.h"
#include"Service.h"
#include"HtmlBuilder.h"
#include"FilterOptions.h"
#include"CharacterFilter.h"
#include<sstream>

// 首页处理函数
std::string Controller::index(HttpRequest&) {
	// 创建模型视图对象
	ModelAndView mv;
	// 指定使用的模板文件
	mv.viewName = "index.htm";
	// 设置页面欢迎信息
	mv.data["messages"] = u8"欢迎来到原神 观测枢！";
	// 渲染模板并返回HTML
	return View::renderFromView(mv);
}

// 角色列表页面处理函数，支持多条件筛选
std::string Controller::characters(HttpRequest& req) {
	// 创建模型视图对象
	ModelAndView mv;
	// 指定角色列表模板
	mv.viewName = "characters.htm";

	// 从数据源获取所有角色
	auto allCharacters = Service::getAllCharacters();

	// 提取请求参数中的筛选条件
	std::string filterElement = req.params["element"];
	std::string filterFrom = req.params["from"];
	std::string filterWeapon = req.params["weapon"];
	std::string filterStars = req.params["stars"];

	// 根据当前的筛选条件构建下拉选项（保持选中状态）
	mv.data["elementOptions"] = 
		HtmlBuilder::buildOptions(FilterOptions::getElements(), filterElement);
	mv.data["fromOptions"] = 
		HtmlBuilder::buildOptions(FilterOptions::getRegions(), filterFrom);
	mv.data["weaponOptions"] = 
		HtmlBuilder::buildOptions(FilterOptions::getWeapons(), filterWeapon);
	mv.data["starsOptions"] = 
		HtmlBuilder::buildOptions(FilterOptions::getStars(), filterStars);

	// 执行角色筛选，返回符合条件的子集
	auto filteredCharacters = CharacterFilter::filter(
		allCharacters, filterElement, filterFrom, filterWeapon, filterStars);
	// 检查是否应用了任何筛选条件
	bool hasFilter = !filterElement.empty() || !filterFrom.empty() || 
		!filterWeapon.empty() || !filterStars.empty();

	// 创建字符串流用于构建HTML内容
	std::stringstream ss;

	// 分次处理：找到结果或找不到的所有情况
	if (filteredCharacters.empty() && !hasFilter) {
		// 情况一: 没有筛选条件且没有结果，显示所有角色
		ss << u8"<p style=\"color: #666;\">共 " << allCharacters.size() << u8" 个角色</p>";
		ss << HtmlBuilder::buildCharacterTable(allCharacters);
	} else if (filteredCharacters.empty()) {
		// 情况二: 有筛选条件但没有结果，显示未找到页面
		ss << HtmlBuilder::buildNotFoundPage(
			filterElement, filterFrom, filterWeapon, filterStars);
	} else {
		// 情况三: 找到符合条件的角色，显示筛选结果
		ss << u8"<p style=\"color: #666;\">找到 " << filteredCharacters.size() << u8" 个角色</p>";
		ss << HtmlBuilder::buildCharacterTable(filteredCharacters);
	}

	// 将构建的HTML添加到模板数据中
	mv.data["characters"] = ss.str();
	return View::renderFromView(mv);
}

// 角色详情页面处理函数
std::string Controller::characterDetail(HttpRequest& req) {
    // 创建模型视图对象
    ModelAndView mv;
    // 指定详情页模板
    mv.viewName = "characterdetails.htm";

    // 从请求参数中提取角色名称
    std::string name = req.params["name"];
    // 检查名称是否为空，为空则返回404
    if (name.empty()) {
    	return HtmlBuilder::buildNotFoundPage("", "", "", "");
    }
    
    // 根据名称查询角色数据
    Character c = Service::getCharacterByName(name);
    
	// 检查是否找到角色（字符串为空表示没有找到）
	if (c.name.empty()) {
		// 构建空输出 HTML
		std::stringstream ss;
		ss << u8"<div style=\"text-align: center; padding: 40px;\">";
		ss << u8"<h2>未找到角色</h2>";
		ss << u8"<p>请检查角色名称是否正确。</p>";
		ss << u8"</div>";
		mv.data["characterDetail"] = ss.str();
		return View::renderFromView(mv);
	}

    // 使用字符串流构建角色详情HTML
    std::stringstream ss;
    // 添加角色名称为标题
    ss << "<h2>" << c.name << "</h2>";
    // 闭合上层div并开始内容区
    ss << "</div><div class=\"content\">";
    // 使用网格布局容器
    ss << "<div class=\"detail-layout\">";
    
    // 第一列: 信息列表
    ss << "<div class=\"info-section\">";
    ss << "<ul class=\"info-list\">";
    // 按顺序添加角色的各个属性
    ss << u8"<li><span class=\"label\">生日：</span>"
       << "<span class=\"value\">" << c.birthday << "</span></li>";
    ss << u8"<li><span class=\"label\">所属：</span>"
       << "<span class=\"value\">" << c.belong << "</span></li>";
	ss << u8"<li><span class=\"label\">定位：</span>"
	   << "<span class=\"value\">" << c.position << "</span></li>";
    ss << u8"<li><span class=\"label\">武器类型：</span>"
       << "<span class=\"value\">" << c.weapon << "</span></li>";
    ss << u8"<li><span class=\"label\">命之座：</span>"
       << "<span class=\"value\">" << c.constellation << "</span></li>";
	ss << u8"<li><span class=\"label\">称号：</span>"
	   << "<span class=\"value\">" << c.title << "</span></li>";
    // 关闭信息列表
    ss << "</ul>";
    // 关闭信息区容器
    ss << "</div>";
    
	// 第二列: 角色图片
	ss << "<div class=\"image-section\">";
	// 根据角色名称加载对应的图片，失败时使用派蒙作为默认图片
	ss << "<img src=\"/images/" << c.name << ".jpg\" alt=\"" << c.name 
	   << "\" class=\"character-image\" "
	   << "onerror=\"this.onerror=null; "
	   << "this.src='/images/派蒙.jpg';\">";
	// 关闭图片区容器
	ss << "</div>";
    
    // 关闭网格布局容器
    ss << "</div>";

    // 将详情HTML添加到模板数据
    mv.data["characterDetail"] = ss.str();
    return View::renderFromView(mv);
}