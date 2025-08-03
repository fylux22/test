#pragma once

#include "../nlohmann/json.hpp"
#include "../options.h"
#include "../globals.h"
#include <fstream>  

using json = nlohmann::json;

inline json CreateConfig(std::string configName)
{
    json j;

    j["ESP"] = 
    {
        { "Team Check", Options::ESP::TeamCheck },
        { "Box", Options::ESP::Box },
        { "Tracers", Options::ESP::Tracers },
        { "TracersStart", Options::ESP::TracersStart },
        { "Skeleton", Options::ESP::Skeleton },
        { "Name", Options::ESP::Name },
        { "Distance", Options::ESP::Distance },
        { "Health", Options::ESP::Health },
        { "3D ESP", Options::ESP::ESP3D },
        { "Tracer Thickness", Options::ESP::TracerThickness },
        { "Head Circles", Options::ESP::HeadCircle },
        { "Remove Borders", Options::ESP::RemoveBorders },

        { "Name Color", Options::ESP::Color },
        { "Box Color", Options::ESP::BoxColor },
        { "Box Fill Color", Options::ESP::BoxFillColor },
        { "Skeleton Color", Options::ESP::SkeletonColor },
        { "Distance Color", Options::ESP::DistanceColor },
        { "Tracers Color", Options::ESP::TracerColor },
        { "3D ESP Color", Options::ESP::ESP3DColor },
        { "Head Circles Color", Options::ESP::HeadCircleColor }
    };

    j["Parry"] =
    {
        {"Enabled", Options::Parry::Enabled},
        {"Parry Key", Options::Parry::ParryKey},
        {"Auto Parry", Options::Parry::AutoParry},
        {"Hold Time", Options::Parry::HoldTime},
        {"Delay Time", Options::Parry::DelayTime},
        {"Parry Window", Options::Parry::ParryWindow}
    };

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

    //ESP Loading

    Options::ESP::TeamCheck = data["ESP"]["Team Check"];
    Options::ESP::Box = data["ESP"]["Box"];
    Options::ESP::Tracers = data["ESP"]["Tracers"];
    Options::ESP::TracersStart = data["ESP"]["TracersStart"];
    Options::ESP::Skeleton = data["ESP"]["Skeleton"];
    Options::ESP::Name = data["ESP"]["Name"];
    Options::ESP::Distance = data["ESP"]["Distance"];
    Options::ESP::Health = data["ESP"]["Health"];
    Options::ESP::ESP3D = data["ESP"]["3D ESP"];
    Options::ESP::TracerThickness = data["ESP"]["Tracer Thickness"];
    Options::ESP::HeadCircle = data["ESP"]["Head Circles"];
    Options::ESP::RemoveBorders = data["ESP"]["Remove Borders"];

    Options::ESP::Color[0] = data["ESP"]["Name Color"][0];
    Options::ESP::Color[1] = data["ESP"]["Name Color"][1];
    Options::ESP::Color[2] = data["ESP"]["Name Color"][2];

    Options::ESP::BoxColor[0] = data["ESP"]["Box Color"][0];
    Options::ESP::BoxColor[1] = data["ESP"]["Box Color"][1];
    Options::ESP::BoxColor[2] = data["ESP"]["Box Color"][2];

    Options::ESP::BoxFillColor[0] = data["ESP"]["Box Fill Color"][0];
    Options::ESP::BoxFillColor[1] = data["ESP"]["Box Fill Color"][1];
    Options::ESP::BoxFillColor[2] = data["ESP"]["Box Fill Color"][2];
    Options::ESP::BoxFillColor[3] = data["ESP"]["Box Fill Color"][3];

    Options::ESP::DistanceColor[0] = data["ESP"]["Distance Color"][0];
    Options::ESP::DistanceColor[1] = data["ESP"]["Distance Color"][1];
    Options::ESP::DistanceColor[2] = data["ESP"]["Distance Color"][2];

    Options::ESP::TracerColor[0] = data["ESP"]["Tracers Color"][0];
    Options::ESP::TracerColor[1] = data["ESP"]["Tracers Color"][1];
    Options::ESP::TracerColor[2] = data["ESP"]["Tracers Color"][2];

    Options::ESP::ESP3DColor[0] = data["ESP"]["3D ESP Color"][0];
    Options::ESP::ESP3DColor[1] = data["ESP"]["3D ESP Color"][1];
    Options::ESP::ESP3DColor[2] = data["ESP"]["3D ESP Color"][2];

    Options::ESP::HeadCircleColor[0] = data["ESP"]["Head Circles Color"][0];
    Options::ESP::HeadCircleColor[1] = data["ESP"]["Head Circles Color"][1];
    Options::ESP::HeadCircleColor[2] = data["ESP"]["Head Circles Color"][2];

    // Parry Loading

    Options::Parry::Enabled = data["Parry"]["Enabled"];
    Options::Parry::ParryKey = data["Parry"]["Parry Key"];
    Options::Parry::AutoParry = data["Parry"]["Auto Parry"];
    Options::Parry::HoldTime = data["Parry"]["Hold Time"];
    Options::Parry::DelayTime = data["Parry"]["Delay Time"];
    Options::Parry::ParryWindow = data["Parry"]["Parry Window"];

    // Misc Loading

    Options::Misc::Walkspeed = data["Misc"]["Walkspeed"];
    Options::Misc::JumpPower = data["Misc"]["JumpPower"];
    Options::Misc::FOV = data["Misc"]["FOV"];
}