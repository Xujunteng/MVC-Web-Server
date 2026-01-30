# 原神角色信息 Web 服务器

一个基于 C++ 开发的轻量级 Web 服务器，用于展示原神游戏角色信息。该项目采用 MVC 架构设计，支持角色列表浏览、详细信息查看和多条件筛选功能。

## 功能特性

- 🌐 **HTTP 服务器**：基于 Windows Socket 的自定义 HTTP 服务器实现
- 🏗️ **MVC 架构**：清晰的三层架构设计（Model-View-Controller）
- 🔍 **筛选功能**：支持按元素、地区、武器类型、星级等多维度筛选角色
- 📄 **动态页面**：服务端 HTML 模板渲染
- 🎨 **静态资源**：支持 CSS 样式和图片资源服务
- 📝 **日志系统**：完整的请求日志记录

## 项目结构

```
Web Server/
├── main.cpp                  # 程序入口
├── HttpServer.cpp/h          # HTTP 服务器核心
├── Router.cpp/h              # 路由管理
├── Controller.cpp/h          # 控制器层
├── Service.cpp/h             # 业务逻辑层
├── Dao.cpp/h                 # 数据访问层
├── HttpRequest.h             # HTTP 请求结构
├── HttpRequestParser.cpp/h   # HTTP 请求解析器
├── HttpResponse.cpp/h        # HTTP 响应生成
├── View.cpp/h                # 视图渲染
├── HtmlBuilder.cpp/h         # HTML 构建工具
├── FilterOptions.cpp/h       # 筛选选项处理
├── CharacterFilter.cpp/h     # 角色过滤器
├── ImageHandler.cpp/h        # 图片处理
├── Logger.cpp/h              # 日志系统
├── ModelAndView.h            # MVC 数据传递结构
├── Dao/
│   └── characters.csv        # 角色数据文件
├── View/
│   ├── index.htm             # 首页模板
│   ├── characters.htm        # 角色列表页模板
│   ├── characterdetails.htm  # 角色详情页模板
│   └── css/                  # 样式文件
├── images/                   # 角色图片资源
└── output/                   # 编译输出目录
    └── main.exe
```

## 技术栈

- **语言**：C++
- **网络库**：Windows Sockets (WS2_32)
- **编译器**：g++ (MinGW)
- **数据存储**：CSV 文件
- **模板引擎**：自定义 HTML 模板系统

## 构建与运行

### 环境要求

- Windows 操作系统
- MinGW (g++ 编译器)
- Visual Studio Code (推荐)

### 编译

使用 VS Code 内置任务：

1. 打开项目文件夹
2. 按 `Ctrl+Shift+B` 执行构建任务
3. 或者在终端运行：

```powershell
g++ -Wall -Wextra -g3 -finput-charset=UTF-8 -fexec-charset=UTF-8 `
    main.cpp HttpServer.cpp Router.cpp Controller.cpp Service.cpp Dao.cpp `
    HttpResponse.cpp View.cpp Logger.cpp HttpRequestParser.cpp HtmlBuilder.cpp `
    FilterOptions.cpp CharacterFilter.cpp ImageHandler.cpp `
    -o output/main.exe -lws2_32
```

### 运行

```powershell
cd output
.\main.exe
```

服务器启动后，访问：http://localhost:8080

## 路由说明

| 路径 | 功能 | 说明 |
|------|------|------|
| `/` 或 `/index` | 首页 | 项目欢迎页面 |
| `/characters` | 角色列表 | 展示所有角色，支持筛选 |
| `/character?name=角色名` | 角色详情 | 查看特定角色的详细信息 |
| `/View/css/*.css` | CSS 文件 | 静态样式资源 |
| `/images/*.png` | 图片文件 | 角色图片资源 |

## 筛选参数

在 `/characters` 页面支持以下查询参数：

- `element` - 元素类型（火/水/风/雷/冰/岩/草）
- `from` - 所属地区（蒙德/璃月/稻妻/须弥/枫丹/纳塔等）
- `weapon` - 武器类型（单手剑/双手剑/长柄武器/弓/法器）
- `stars` - 星级（四星/五星）

示例：`http://localhost:8080/characters?element=火&stars=五星`

## 数据格式

角色数据存储在 `Dao/characters.csv` 文件中，包含以下字段：

- `name` - 角色名称
- `element` - 元素属性
- `from` - 所属地区
- `weapon` - 武器类型
- `stars` - 稀有度
- `birthday` - 生日
- `belong` - 所属组织
- `position` - 定位
- `constellation` - 命之座
- `title` - 称号

## 架构说明

### MVC 模式

- **Model (Dao/Service)**：数据层，负责从 CSV 读取和处理角色数据
- **View (View)**：视图层，HTML 模板渲染
- **Controller (Controller)**：控制器层，处理请求并协调 Model 和 View

### 请求处理流程

```
客户端请求 
    ↓
HttpServer (接收连接)
    ↓
HttpRequestParser (解析请求)
    ↓
Router (路由分发)
    ↓
Controller (业务处理)
    ↓
Service (数据处理)
    ↓
Dao (数据访问)
    ↓
View (模板渲染)
    ↓
HttpResponse (构建响应)
    ↓
客户端接收
```

## 开发说明

### 添加新路由

在 [Router.cpp](Router.cpp) 的 `ensureInit()` 方法中添加：

```cpp
addRoute("/your-path", Controller::yourHandler);
```

### 添加新角色

编辑 `Dao/characters.csv` 文件，按照现有格式添加新行即可。

### 自定义样式

修改 `View/css/` 目录下的对应 CSS 文件。

## 日志

服务器运行时会输出详细的日志信息，包括：
- 服务器启动信息
- 客户端连接信息
- 请求详情（方法、路径、参数）
- 响应状态

## 许可

本项目仅用于学习和研究目的。

## 贡献

欢迎提交 Issue 和 Pull Request！

---

**Note**: 原神角色数据和图片版权归米哈游所有。
