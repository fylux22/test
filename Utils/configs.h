#pragma once

#include "../nlohmann/json.hpp"
#include "../options.h"
#include "../globals.h"
#include <fstream>  

using json = nlohmann::json;

inline json CreateConfig(std::string configName)
{
    json j;



    j["Misc"] =
    {
        {"Walkspeed", Options::Misc::Walkspeed},
        {"JumpPower", Options::Misc::JumpPower},
        {"FOV", Options::Misc::FOV}
    };

    std::ofstream out(Globals::configsPath + "\\" + configName);
    out << j.dump(4);
    out.close();

    return j;
}

inline void LoadConfig(std::string configName)
{
    std::ifstream f(Globals::configsPath + "\\" + configName);
    json data = json::parse(f);



    // Misc Loading

    Options::Misc::Walkspeed = data["Misc"]["Walkspeed"];
    Options::Misc::JumpPower = data["Misc"]["JumpPower"];
    Options::Misc::FOV = data["Misc"]["FOV"];
}