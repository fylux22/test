#pragma once

#include "../nlohmann/json.hpp"
#include "../options.h"
#include "../globals.h"
#include <fstream>  

inline std::string deobf_tOVXYl() {
    const unsigned char data[] = {0xd0, 0xe1, 0xf2, 0xf2, 0xf9, 0xa0, 0xd7, 0xe9, 0xee, 0xe4, 0xef, 0xf7};
    const int key = 128;
    std::string result;
    for (int i = 0; i < 12; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_gUNLZK() {
    const unsigned char data[] = {0x44, 0x62, 0x71, 0x73, 0x75, 0x62, 0x30, 0x44, 0x78, 0x79, 0x73, 0x7b, 0x7e, 0x75, 0x63, 0x63};
    const int key = 16;
    std::string result;
    for (int i = 0; i < 16; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_uhdsxT() {
    const unsigned char data[] = {0xa6, 0x80, 0x93, 0x91, 0x97, 0x80, 0x81, 0xd2, 0xb1, 0x9d, 0x9e, 0x9d, 0x80};
    const int key = 242;
    std::string result;
    for (int i = 0; i < 13; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_nPdvXt() {
    const unsigned char data[] = {0xba, 0x97, 0x8d, 0x8a, 0x9f, 0x90, 0x9d, 0x9b, 0xde, 0xbd, 0x91, 0x92, 0x91, 0x8c};
    const int key = 254;
    std::string result;
    for (int i = 0; i < 14; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_gYGdpo() {
    const unsigned char data[] = {0x05, 0x34, 0x30, 0x3c, 0x71, 0x12, 0x39, 0x34, 0x32, 0x3a};
    const int key = 81;
    std::string result;
    for (int i = 0; i < 10; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_TcHeLq() {
    const unsigned char data[] = {0xdd, 0xf0, 0xe7, 0xbf, 0xdc, 0xf0, 0xf3, 0xf0, 0xed};
    const int key = 159;
    std::string result;
    for (int i = 0; i < 9; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_xPFArt() {
    const unsigned char data[] = {0x02, 0x2f, 0x2b, 0x2e, 0x6a, 0x09, 0x23, 0x38, 0x29, 0x26, 0x2f, 0x39, 0x6a, 0x09, 0x25, 0x26, 0x25, 0x38};
    const int key = 74;
    std::string result;
    for (int i = 0; i < 18; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_zTthid() {
    const unsigned char data[] = {0xba, 0x9d, 0x9e, 0x96, 0xd2, 0xa6, 0x9b, 0x9f, 0x97};
    const int key = 242;
    std::string result;
    for (int i = 0; i < 9; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_NVDVmK() {
    const unsigned char data[] = {0x45, 0x68, 0x6c, 0x69, 0x2d, 0x4e, 0x64, 0x7f, 0x6e, 0x61, 0x68, 0x7e};
    const int key = 13;
    std::string result;
    for (int i = 0; i < 12; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_SCxEsa() {
    const unsigned char data[] = {0x0e, 0x3a, 0x3b, 0x20, 0x6f, 0x1f, 0x2e, 0x3d, 0x3d, 0x36};
    const int key = 79;
    std::string result;
    for (int i = 0; i < 10; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_BVmqCO() {
    const unsigned char data[] = {0x89, 0xbe, 0xb6, 0xb4, 0xad, 0xbe, 0xfb, 0x99, 0xb4, 0xa9, 0xbf, 0xbe, 0xa9, 0xa8};
    const int key = 219;
    std::string result;
    for (int i = 0; i < 14; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_BNvraF() {
    const unsigned char data[] = {0x31, 0x46, 0x22, 0x47, 0x51, 0x52, 0x22, 0x41, 0x6d, 0x6e, 0x6d, 0x70};
    const int key = 2;
    std::string result;
    for (int i = 0; i < 12; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_ugpZTq() {
    const unsigned char data[] = {0x0c, 0x21, 0x36, 0x6e, 0x08, 0x27, 0x22, 0x22, 0x6e, 0x0d, 0x21, 0x22, 0x21, 0x3c};
    const int key = 78;
    std::string result;
    for (int i = 0; i < 14; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_nOvgIl() {
    const unsigned char data[] = {0x89, 0xfe, 0x9a, 0xff, 0xe9, 0xea};
    const int key = 186;
    std::string result;
    for (int i = 0; i < 6; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_SeGqOY() {
    const unsigned char data[] = {0x76, 0x4e, 0x40, 0x49, 0x40, 0x51, 0x4a, 0x4b, 0x05, 0x66, 0x4a, 0x49, 0x4a, 0x57};
    const int key = 37;
    std::string result;
    for (int i = 0; i < 14; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_YcQARP() {
    const unsigned char data[] = {0x12, 0x23, 0x30, 0x30, 0x3b, 0x62, 0x09, 0x27, 0x3b};
    const int key = 66;
    std::string result;
    for (int i = 0; i < 9; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_bLcWLx() {
    const unsigned char data[] = {0x10, 0x31, 0x38, 0x35, 0x2d, 0x74, 0x00, 0x3d, 0x39, 0x31};
    const int key = 84;
    std::string result;
    for (int i = 0; i < 10; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_myCvVC() {
    const unsigned char data[] = {0x04, 0x2b, 0x27, 0x2f, 0x6a, 0x09, 0x25, 0x26, 0x25, 0x38};
    const int key = 74;
    std::string result;
    for (int i = 0; i < 10; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

using json = nlohmann::json;

inline json CreateConfig(std::string configName)
{
    json j;

    j["ESP"] = 
    {
        { deobf_gYGdpo(), Options::ESP::TeamCheck },
        { "Box", Options::ESP::Box },
        { "Tracers", Options::ESP::Tracers },
        { "TracersStart", Options::ESP::TracersStart },
        { "Skeleton", Options::ESP::Skeleton },
        { "Name", Options::ESP::Name },
        { "Distance", Options::ESP::Distance },
        { "Health", Options::ESP::Health },
        { deobf_nOvgIl(), Options::ESP::ESP3D },
        { deobf_gUNLZK(), Options::ESP::TracerThickness },
        { deobf_NVDVmK(), Options::ESP::HeadCircle },
        { deobf_BVmqCO(), Options::ESP::RemoveBorders },

        { deobf_myCvVC(), Options::ESP::Color },
        { deobf_TcHeLq(), Options::ESP::BoxColor },
        { deobf_ugpZTq(), Options::ESP::BoxFillColor },
        { deobf_SeGqOY(), Options::ESP::SkeletonColor },
        { deobf_nPdvXt(), Options::ESP::DistanceColor },
        { deobf_uhdsxT(), Options::ESP::TracerColor },
        { deobf_BNvraF(), Options::ESP::ESP3DColor },
        { deobf_xPFArt(), Options::ESP::HeadCircleColor }
    };

    j["Parry"] =
    {
        {"Enabled", Options::Parry::Enabled},
        {deobf_YcQARP(), Options::Parry::ParryKey},
        {deobf_SCxEsa(), Options::Parry::AutoParry},
        {deobf_zTthid(), Options::Parry::HoldTime},
        {deobf_bLcWLx(), Options::Parry::DelayTime},
        {deobf_tOVXYl(), Options::Parry::ParryWindow}
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

    Options::ESP::TeamCheck = data["ESP"][deobf_gYGdpo()];
    Options::ESP::Box = data["ESP"]["Box"];
    Options::ESP::Tracers = data["ESP"]["Tracers"];
    Options::ESP::TracersStart = data["ESP"]["TracersStart"];
    Options::ESP::Skeleton = data["ESP"]["Skeleton"];
    Options::ESP::Name = data["ESP"]["Name"];
    Options::ESP::Distance = data["ESP"]["Distance"];
    Options::ESP::Health = data["ESP"]["Health"];
    Options::ESP::ESP3D = data["ESP"][deobf_nOvgIl()];
    Options::ESP::TracerThickness = data["ESP"][deobf_gUNLZK()];
    Options::ESP::HeadCircle = data["ESP"][deobf_NVDVmK()];
    Options::ESP::RemoveBorders = data["ESP"][deobf_BVmqCO()];

    Options::ESP::Color[0] = data["ESP"][deobf_myCvVC()][0];
    Options::ESP::Color[1] = data["ESP"][deobf_myCvVC()][1];
    Options::ESP::Color[2] = data["ESP"][deobf_myCvVC()][2];

    Options::ESP::BoxColor[0] = data["ESP"][deobf_TcHeLq()][0];
    Options::ESP::BoxColor[1] = data["ESP"][deobf_TcHeLq()][1];
    Options::ESP::BoxColor[2] = data["ESP"][deobf_TcHeLq()][2];

    Options::ESP::BoxFillColor[0] = data["ESP"][deobf_ugpZTq()][0];
    Options::ESP::BoxFillColor[1] = data["ESP"][deobf_ugpZTq()][1];
    Options::ESP::BoxFillColor[2] = data["ESP"][deobf_ugpZTq()][2];
    Options::ESP::BoxFillColor[3] = data["ESP"][deobf_ugpZTq()][3];

    Options::ESP::DistanceColor[0] = data["ESP"][deobf_nPdvXt()][0];
    Options::ESP::DistanceColor[1] = data["ESP"][deobf_nPdvXt()][1];
    Options::ESP::DistanceColor[2] = data["ESP"][deobf_nPdvXt()][2];

    Options::ESP::TracerColor[0] = data["ESP"][deobf_uhdsxT()][0];
    Options::ESP::TracerColor[1] = data["ESP"][deobf_uhdsxT()][1];
    Options::ESP::TracerColor[2] = data["ESP"][deobf_uhdsxT()][2];

    Options::ESP::ESP3DColor[0] = data["ESP"][deobf_BNvraF()][0];
    Options::ESP::ESP3DColor[1] = data["ESP"][deobf_BNvraF()][1];
    Options::ESP::ESP3DColor[2] = data["ESP"][deobf_BNvraF()][2];

    Options::ESP::HeadCircleColor[0] = data["ESP"][deobf_xPFArt()][0];
    Options::ESP::HeadCircleColor[1] = data["ESP"][deobf_xPFArt()][1];
    Options::ESP::HeadCircleColor[2] = data["ESP"][deobf_xPFArt()][2];

    // Parry Loading

    Options::Parry::Enabled = data["Parry"]["Enabled"];
    Options::Parry::ParryKey = data["Parry"][deobf_YcQARP()];
    Options::Parry::AutoParry = data["Parry"][deobf_SCxEsa()];
    Options::Parry::HoldTime = data["Parry"][deobf_zTthid()];
    Options::Parry::DelayTime = data["Parry"][deobf_bLcWLx()];
    Options::Parry::ParryWindow = data["Parry"][deobf_tOVXYl()];

    // Misc Loading

    Options::Misc::Walkspeed = data["Misc"]["Walkspeed"];
    Options::Misc::JumpPower = data["Misc"]["JumpPower"];
    Options::Misc::FOV = data["Misc"]["FOV"];
}