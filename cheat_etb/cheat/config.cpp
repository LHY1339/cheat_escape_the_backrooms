#include "config.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "gvalue.h"
#include "command.h"

config* config::get()
{
    static config inst;
    return &inst;
}

void config::save()
{
    std::vector<std::string> cmd = command::get()->value_to_cmd();

    std::filesystem::path file_path = "C:\\LHY1339\\escape_the_backrooms\\config.cheat";

    std::ofstream file(file_path, std::ios::out | std::ios::trunc);
    if (!file.is_open())
    {
        return;
    }

    for (const std::string& line : cmd)
    {
        file << line << "\n";
    }
    file.close();
}

void config::load(std::filesystem::path file_path)
{
    std::vector<std::string> lines;
    std::ifstream file(file_path);

    if (!file.is_open())
    {
        std::ofstream create_file(file_path);
        create_file.close();
        return;
    }

    std::string line;
    while (std::getline(file, line)) 
    {
        if (!line.empty() && line.back() == '\r') 
        {
            line.pop_back();
        }
        lines.push_back(line);
    }
    file.close();

    for (const std::string& line : lines)
    {
        command::get()->run(line);
    }
}

