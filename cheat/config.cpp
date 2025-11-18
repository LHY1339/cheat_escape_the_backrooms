#include "config.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include "gvalue.h"

void config::create(const std::string& path)
{
    std::filesystem::path p(path);
    auto dir = p.parent_path();

    if (!dir.empty()) 
    {
        std::error_code ec;
        std::filesystem::create_directories(dir, ec);
        if (ec) 
        {
            std::cerr << "目录创建失败: " << ec.message() << '\n';
            return;
        }
    }

    std::ofstream file(path);
    if (!file.is_open()) 
    {
        printf("创建文件失败\n");
        return;
    }

    std::vector<std::string> lines =
    {
        "//这个文件是用来绑定按键的",
        "//双斜杠是注释，不会被读取到",
        "//比如逆向绑定F到飞天遁地，那就写：bind f 飞天遁地",
        "//如果啥都不想绑定那就写：bind none 飞天遁地",
        "//注意一定要小写",
        "//可以用的按键有：ins del f1到f12 所有的数字和字母按键",
        "//可以绑定的功能如下",
        " ",
        "bind ins 打开菜单",
        "bind del 退出菜单",
        "bind none 绘制周围网格体",
        "bind none 第三人称",
        "bind none 无限耐力",
        "bind none 灵魂出窍",
        "bind none 无限跳跃",
        "bind none 飞天遁地",
        "bind none X键删除",
        "bind none 干死所有实体"
    };

    for (const auto& line : lines)
    {
        file << line << '\n';
    }

    file.close();
}

void config::load(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        printf("打开文件失败\n");
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) 
    {
        lines.push_back(line);
    }

    file.close();

    for (const std::string& l : lines)
    {
        bool success;
        std::vector<std::string> cmd = get_command(l, success);
        if (success)
        {
            execute(cmd);
        }
    }
}

bool config::file_exists(const std::string& path)
{
    std::ifstream f(path);
    return f.is_open();
}

std::vector<std::string> config::get_command(const std::string& line, bool& success)
{
    std::vector<std::string> value;
    if (line.find("//") == 0)
    {
        success = false;
        return value;
    }

    std::string last_line = line;
    while (true)
    {
        size_t pos = last_line.find(' ');
        if (pos == std::string::npos)
        {
            value.emplace_back(last_line);
            break;
        }
        value.emplace_back(last_line.substr(0, pos));
        last_line = last_line.substr(pos + 1);
    }
    success = true;
    return value;
}

void config::execute(const std::vector<std::string>& param)
{
    if (param.size() != 3)
    {
        return;
    }

    if (param[0] == "bind")
    {
        if (param[2] == "打开菜单")
        {
            gvalue::key_open_menu = param[1];
            return;
        }
        if (param[2] == "退出菜单")
        {
            gvalue::key_close_menu = param[1];
            return;
        }
        if (param[2] == "绘制周围网格体")
        {
            gvalue::key_draw_mesh = param[1];
            return;
        }
        if (param[2] == "第三人称")
        {
            gvalue::key_third_person = param[1];
            return;
        }
        if (param[2] == "灵魂出窍")
        {
            gvalue::key_fly_mode = param[1];
            return;
        }
        if (param[2] == "无限跳跃")
        {
            gvalue::key_inf_jump = param[1];
            return;
        }
        if (param[2] == "飞天遁地")
        {
            gvalue::key_fly_mode = param[1];
            return;
        }
        if (param[2] == "X键删除")
        {
            gvalue::key_x_delete = param[1];
            return;
        }
        if (param[2] == "干死所有实体")
        {
            gvalue::key_kill_all = param[1];
            return;
        }
    }
}
