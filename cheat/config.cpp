#include "config.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include "gvalue.h"

void config::create(const std::string& path)
{
    //初始化path
    std::filesystem::path p(path);
    auto dir = p.parent_path();

    //判断路径是否为空
    if (!dir.empty()) 
    {
        //创建路径
        std::error_code ec;
        std::filesystem::create_directories(dir, ec);
        //错误处理
        if (ec) 
        {
            printf("create file error : %s\n", ec.message().c_str());
            return;
        }
    }

    //在路径创建文件
    std::ofstream file(path);
    //错误处理
    if (!file.is_open()) 
    {
        printf("创建文件失败\n");
        return;
    }

    //初始化要写入的字符串
    std::vector<std::string> lines =
    {
        "//这个文件是用来绑定按键的",
        "//双斜杠是注释，不会被读取到",
        "//比如逆向绑定F到飞天遁地，那就写：bind f 飞天遁地",
        "//如果啥都不想绑定那就写：bind none 飞天遁地",
        "//注意一定要小写",
        "//可以用的按键有：ins del f1到f12 所有的数字和字母按键",
        "//可以绑定的功能如下",
        "",
        "bind ins 打开菜单",
        "bind del 退出菜单",
        "bind none 绘制周围网格体",
        "bind none 第三人称",
        "bind none 灵魂出窍",
        "bind none 无限跳跃",
        "bind none 飞天遁地",
        "bind none X键删除",
        "bind none 干死所有实体"
    };

    //获取每一行写入文件
    for (const auto& line : lines)
    {
        file << line << '\n';
    }

    //关闭文件
    file.close();
}

void config::load(const std::string& path)
{
    //获取文件
    std::ifstream file(path);
    //错误处理
    if (!file.is_open())
    {
        printf("open file error\n");
        return;
    }

    //初始化读取行和buffer
    std::vector<std::string> lines;
    std::string line;
    //读取每一行
    while (std::getline(file, line)) 
    {
        lines.push_back(line);
    }
    //关闭文件
    file.close();

    //解析每一行
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
    //判断文件是否可以打开
    std::ifstream f(path);
    return f.is_open();
}

std::vector<std::string> config::get_command(const std::string& line, bool& success)
{
    std::vector<std::string> value;
    //判断是否已//开头
    if (line.find("//") == 0)
    {
        success = false;
        return value;
    }

    //以空格分隔
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
    //判断参数数量是否正确
    if (param.size() != 3)
    {
        return;
    }

    //判断第一个参数是否是bind
    if (param[0] == "bind")
    {

//设置快捷键
#define SET_KEY(name,key_name) \
if (param[2] == #name) \
{ \
    gvalue::key_name = param[1]; \
    return; \
} \

        SET_KEY(打开菜单, key_open_menu);
        SET_KEY(退出菜单, key_close_menu);
        SET_KEY(绘制周围网格体, key_draw_mesh);
        SET_KEY(第三人称, key_third_person);
        SET_KEY(灵魂出窍, key_ghost_mode);
        SET_KEY(X键删除, key_x_delete);
        SET_KEY(无限跳跃, key_inf_jump);
        SET_KEY(飞天遁地, key_fly_mode);
        SET_KEY(干死所有实体, key_kill_all);
        return;
    }
    if (param[0] == "set")
    {
        return;
    }
}
