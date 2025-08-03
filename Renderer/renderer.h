#pragma once

#pragma comment (lib, deobf_qxgQFw())

#pragma comment(lib, deobf_QbrirI())
#include <dwmapi.h>

#include <Windows.h>

#include <d3d11.h>
#include <tchar.h>
#include <algorithm>
#include <string>
#include <thread>
#include <iostream>
#include <filesystem>

#include deobf_cmUOLk()
#include deobf_NipDqL()
#include deobf_sHrjOG()
#include deobf_qpfyMN()

#include deobf_lmiLJp()

#include "../globals.h"
#include "../options.h"

#include "../Utils/configs.h"

#include "../Hacks/esp.h"
#include "W2S.h"

inline std::string deobf_sckcCJ() {
    const unsigned char data[] = {0x64, 0x49, 0x53, 0x54, 0x41, 0x4e, 0x43, 0x45, 0x00, 0x65, 0x73, 0x70};
    const int key = 32;
    std::string result;
    for (int i = 0; i < 12; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_iuHKWy() {
    const unsigned char data[] = {0x7f, 0x4e, 0x5d, 0x5d, 0x56, 0x0f, 0x53, 0x0f};
    const int key = 47;
    std::string result;
    for (int i = 0; i < 8; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_invDGD() {
    const unsigned char data[] = {0xae, 0x88, 0x9b, 0x99, 0x9f, 0x88, 0xda, 0xb9, 0x95, 0x96, 0x95, 0x88};
    const int key = 250;
    std::string result;
    for (int i = 0; i < 12; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_luYdtV() {
    const unsigned char data[] = {0xd9, 0xe8, 0xe1, 0xe8, 0xfd, 0xe2, 0xff, 0xf9, 0xae, 0xae};
    const int key = 141;
    std::string result;
    for (int i = 0; i < 10; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_SUksjl() {
    const unsigned char data[] = {0x87, 0x8c, 0x93, 0xc4};
    const int key = 162;
    std::string result;
    for (int i = 0; i < 4; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_bzDRlk() {
    const unsigned char data[] = {0x16, 0x3b, 0x21, 0x26, 0x33, 0x3c, 0x31, 0x37, 0x72, 0x11, 0x3d, 0x3e, 0x3d, 0x20};
    const int key = 82;
    std::string result;
    for (int i = 0; i < 14; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_kSKTma() {
    const unsigned char data[] = {0x0c, 0x2f, 0x3a, 0x3c, 0x2b, 0x3e, 0x2b, 0x3a, 0x7c, 0x7c};
    const int key = 95;
    std::string result;
    for (int i = 0; i < 10; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_ZtfLCR() {
    const unsigned char data[] = {0x37, 0x3c, 0x22, 0x74};
    const int key = 18;
    std::string result;
    for (int i = 0; i < 4; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_BzESyU() {
    const unsigned char data[] = {0x42, 0x4b, 0x4a, 0x50, 0x57, 0x0b, 0x42, 0x45, 0x09, 0x46, 0x56, 0x45, 0x4a, 0x40, 0x57, 0x09, 0x10, 0x14, 0x14, 0x0a, 0x50, 0x50, 0x42};
    const int key = 36;
    std::string result;
    for (int i = 0; i < 23; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_izUSne() {
    const unsigned char data[] = {0x36, 0x41, 0x25, 0x40, 0x56, 0x55, 0x25, 0x46, 0x6a, 0x69, 0x6a, 0x77};
    const int key = 5;
    std::string result;
    for (int i = 0; i < 12; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_cmUOLk() {
    const unsigned char data[] = {0x87, 0x83, 0x89, 0x9b, 0x87, 0xc1, 0x87, 0x83, 0x89, 0x9b, 0x87, 0xc0, 0x86};
    const int key = 238;
    std::string result;
    for (int i = 0; i < 13; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_PIvCeH() {
    const unsigned char data[] = {0x51, 0x69, 0x67, 0x6e, 0x67, 0x76, 0x6d, 0x6c, 0x22, 0x41, 0x6d, 0x6e, 0x6d, 0x70};
    const int key = 2;
    std::string result;
    for (int i = 0; i < 14; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_Rzslsp() {
    const unsigned char data[] = {0xce, 0xea, 0xf0, 0xe0, 0xe6, 0xef, 0xef, 0xe2, 0xed, 0xe6, 0xec, 0xf6, 0xf0, 0xa3, 0xff, 0xa3};
    const int key = 131;
    std::string result;
    for (int i = 0; i < 16; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_zETowE() {
    const unsigned char data[] = {0x4d, 0x79, 0x78, 0x63, 0x2c, 0x5c, 0x6d, 0x7e, 0x7e, 0x75, 0x2c, 0x41, 0x63, 0x68, 0x69};
    const int key = 12;
    std::string result;
    for (int i = 0; i < 15; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_zijbxl() {
    const unsigned char data[] = {0x4c, 0x6b, 0x68, 0x60, 0x24, 0x50, 0x6d, 0x69, 0x61, 0x24, 0x2c, 0x77, 0x2d};
    const int key = 4;
    std::string result;
    for (int i = 0; i < 13; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_MVdeAj() {
    const unsigned char data[] = {0x87, 0x8c, 0x90, 0xc4};
    const int key = 162;
    std::string result;
    for (int i = 0; i < 4; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_LTAuew() {
    const unsigned char data[] = {0x8d, 0xfa, 0x9e, 0xfb, 0xed, 0xee};
    const int key = 190;
    std::string result;
    for (int i = 0; i < 6; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_spiAGh() {
    const unsigned char data[] = {0x3d, 0x00, 0x08, 0x14, 0x17, 0x0a, 0x1d, 0x0a, 0x58, 0x04, 0x58};
    const int key = 120;
    std::string result;
    for (int i = 0; i < 11; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_GmHJic() {
    const unsigned char data[] = {0xd3, 0xef, 0xe2, 0xfa, 0xe6, 0xf1, 0xa3, 0xcf, 0xea, 0xf0, 0xf7};
    const int key = 131;
    std::string result;
    for (int i = 0; i < 11; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_UxcrPE() {
    const unsigned char data[] = {0xf7, 0xfc, 0xd6, 0xda, 0x82, 0x83, 0x81, 0x97, 0x91, 0x97, 0xf7, 0xc5, 0xd2, 0xd3, 0xc4, 0xc3, 0xd8, 0xd9, 0xd2, 0xc7, 0xc5, 0xd8, 0xdd, 0xc5, 0xdd, 0xc5, 0x97, 0xcb, 0x97};
    const int key = 183;
    std::string result;
    for (int i = 0; i < 29; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_IasVeV() {
    const unsigned char data[] = {0x52, 0x45, 0x44, 0x53, 0x54, 0x4f, 0x4e, 0x45, 0x50, 0x52, 0x4f, 0x4a, 0x52, 0x4a, 0x52, 0x06, 0x4b, 0x41, 0x4d, 0x15, 0x14, 0x16};
    const int key = 32;
    std::string result;
    for (int i = 0; i < 22; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_ekRrLN() {
    const unsigned char data[] = {0xc9, 0xe4, 0xf3, 0xab, 0xc8, 0xe4, 0xe7, 0xe4, 0xf9};
    const int key = 139;
    std::string result;
    for (int i = 0; i < 9; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_tqLJvY() {
    const unsigned char data[] = {0xc0, 0xf1, 0xe2, 0xe2, 0xe9, 0xb0, 0xc7, 0xf9, 0xfe, 0xf4, 0xff, 0xe7, 0xb0, 0xb8, 0xe3, 0xb9};
    const int key = 144;
    std::string result;
    for (int i = 0; i < 16; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_WcCAWF() {
    const unsigned char data[] = {0xc9, 0xfd, 0xfc, 0xe7, 0xa8, 0xd8, 0xe9, 0xfa, 0xfa, 0xf1};
    const int key = 136;
    std::string result;
    for (int i = 0; i < 10; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_hIejFi() {
    const unsigned char data[] = {0xb5, 0x88, 0x84, 0x95, 0x82, 0x9e, 0x91, 0x9c, 0xd0, 0x8c, 0xd0, 0xb0, 0xbb, 0x91, 0x9d, 0xc5, 0xc4, 0xc6, 0xd0, 0xd6, 0xd0, 0xb0, 0x82, 0x95, 0x94, 0x83, 0x84, 0x9f, 0x9e, 0x95, 0x80, 0x82, 0x9f, 0x9a, 0x82, 0x9a, 0x82};
    const int key = 240;
    std::string result;
    for (int i = 0; i < 37; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_jskdfI() {
    const unsigned char data[] = {0xb4, 0x98, 0x99, 0x91, 0x9e, 0x90, 0x82, 0x85, 0x96, 0x83, 0x9e, 0x98, 0x99, 0x84, 0xd7, 0x8b, 0xd7};
    const int key = 247;
    std::string result;
    for (int i = 0; i < 17; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_bxkRzK() {
    const unsigned char data[] = {0xfb, 0xda, 0xd3, 0xde, 0xc6, 0x9f, 0xeb, 0xd6, 0xd2, 0xda, 0x9f, 0x97, 0xcc, 0x96};
    const int key = 191;
    std::string result;
    for (int i = 0; i < 14; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_IgBTBG() {
    const unsigned char data[] = {0x4b, 0x66, 0x62, 0x67, 0x23, 0x40, 0x6a, 0x71, 0x60, 0x6f, 0x66};
    const int key = 3;
    std::string result;
    for (int i = 0; i < 11; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_nxyvNK() {
    const unsigned char data[] = {0x5e, 0x73, 0x64, 0x3c, 0x59, 0x4f, 0x4c};
    const int key = 28;
    std::string result;
    for (int i = 0; i < 7; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_gTGllF() {
    const unsigned char data[] = {0xec, 0xd4, 0xda, 0xd3, 0xda, 0xcb, 0xd0, 0xd1, 0x9f, 0xfa, 0xec, 0xef};
    const int key = 191;
    std::string result;
    for (int i = 0; i < 12; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_sosNzs() {
    const unsigned char data[] = {0xe9, 0xd5, 0xd8, 0xc0, 0xdc, 0xcb, 0xca, 0x99, 0xc5, 0x99};
    const int key = 185;
    std::string result;
    for (int i = 0; i < 10; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_drJyDE() {
    const unsigned char data[] = {0x4b, 0x2d, 0x3b, 0x38};
    const int key = 107;
    std::string result;
    for (int i = 0; i < 4; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_BYQiNA() {
    const unsigned char data[] = {0xc5, 0xcc, 0xcd, 0xd7, 0xd0, 0x8c, 0xc5, 0xc2, 0x8e, 0xd0, 0xcc, 0xcf, 0xca, 0xc7, 0x8e, 0x9a, 0x93, 0x93, 0x8d, 0xd7, 0xd7, 0xc5};
    const int key = 163;
    std::string result;
    for (int i = 0; i < 22; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_lmiLJp() {
    const unsigned char data[] = {0xb6, 0xbf, 0xbe, 0xa4, 0xff, 0x99, 0xb3, 0xbf, 0xbe, 0xa3, 0x96, 0xbf, 0xbe, 0xa4, 0x91, 0xa7, 0xb5, 0xa3, 0xbf, 0xbd, 0xb5, 0xe6, 0xfe, 0xb8};
    const int key = 208;
    std::string result;
    for (int i = 0; i < 24; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_HVgcfY() {
    const unsigned char data[] = {0x13, 0x3e, 0x3a, 0x3f, 0x7b, 0x18, 0x34, 0x37, 0x34, 0x29};
    const int key = 91;
    std::string result;
    for (int i = 0; i < 10; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_jamFOx() {
    const unsigned char data[] = {0xfb, 0xd6, 0xd2, 0xdf, 0xc7, 0xdb, 0x93, 0xf1, 0xd2, 0xc1};
    const int key = 179;
    std::string result;
    for (int i = 0; i < 10; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_kAFJwM() {
    const unsigned char data[] = {0xa7, 0x81, 0x92, 0x90, 0x96, 0x81, 0xd3, 0xa7, 0x9b, 0x9a, 0x90, 0x98, 0x9d, 0x96, 0x80, 0x80};
    const int key = 243;
    std::string result;
    for (int i = 0; i < 16; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_qxgQFw() {
    const unsigned char data[] = {0xbf, 0xe8, 0xbf, 0xea, 0xea, 0xf5, 0xb7, 0xb2, 0xb9};
    const int key = 219;
    std::string result;
    for (int i = 0; i < 9; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_woPtYD() {
    const unsigned char data[] = {0x91, 0xa0, 0xa4, 0xa8, 0xe5, 0x86, 0xad, 0xa0, 0xa6, 0xae};
    const int key = 197;
    std::string result;
    for (int i = 0; i < 10; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_ajFPTo() {
    const unsigned char data[] = {0xf1, 0xde, 0xd2, 0xda, 0x9f, 0xfa, 0xec, 0xef};
    const int key = 191;
    std::string result;
    for (int i = 0; i < 8; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_sHrjOG() {
    const unsigned char data[] = {0x6f, 0x6b, 0x61, 0x73, 0x6f, 0x29, 0x6f, 0x6b, 0x61, 0x73, 0x6f, 0x59, 0x6f, 0x6b, 0x76, 0x6a, 0x59, 0x62, 0x7e, 0x37, 0x37, 0x28, 0x6e};
    const int key = 6;
    std::string result;
    for (int i = 0; i < 23; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_QbrirI() {
    const unsigned char data[] = {0x09, 0x1a, 0x00, 0x0c, 0x1d, 0x04, 0x43, 0x01, 0x04, 0x0f};
    const int key = 109;
    std::string result;
    for (int i = 0; i < 10; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_DyKhTk() {
    const unsigned char data[] = {0xf9, 0xdf, 0xcc, 0xce, 0xc8, 0xdf, 0xde, 0x8d, 0xfe, 0xd9, 0xcc, 0xdf, 0xd9};
    const int key = 173;
    std::string result;
    for (int i = 0; i < 13; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_mZIFDp() {
    const unsigned char data[] = {0x61, 0x45, 0x6f, 0x5d, 0x41, 0x08, 0x6d, 0x50, 0x49, 0x45, 0x58, 0x44, 0x4d};
    const int key = 40;
    std::string result;
    for (int i = 0; i < 13; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_OVMEyu() {
    const unsigned char data[] = {0xbe, 0xb5, 0xa8, 0xfd};
    const int key = 155;
    std::string result;
    for (int i = 0; i < 4; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_qpfyMN() {
    const unsigned char data[] = {0x9e, 0x9a, 0x90, 0x82, 0x9e, 0xd8, 0xbc, 0x92, 0x8e, 0xb5, 0x9e, 0x99, 0x93, 0xd9, 0x9f};
    const int key = 247;
    std::string result;
    for (int i = 0; i < 15; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_KtbDpH() {
    const unsigned char data[] = {0x3e, 0x13, 0x04, 0x5c, 0x3a, 0x15, 0x10, 0x10, 0x5c, 0x3f, 0x13, 0x10, 0x13, 0x0e};
    const int key = 124;
    std::string result;
    for (int i = 0; i < 14; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_NipDqL() {
    const unsigned char data[] = {0x3a, 0x3e, 0x34, 0x26, 0x3a, 0x7c, 0x3a, 0x3e, 0x34, 0x26, 0x3a, 0x0c, 0x3a, 0x3e, 0x23, 0x3f, 0x0c, 0x24, 0x3a, 0x3d, 0x60, 0x61, 0x7d, 0x3b};
    const int key = 83;
    std::string result;
    for (int i = 0; i < 24; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_PrXGum() {
    const unsigned char data[] = {0xf5, 0xfc, 0xfd, 0xe7, 0xe0, 0xbc, 0xf5, 0xf2, 0xbe, 0xe1, 0xf6, 0xf4, 0xe6, 0xff, 0xf2, 0xe1, 0xbe, 0xa7, 0xa3, 0xa3, 0xbd, 0xe7, 0xe7, 0xf5};
    const int key = 147;
    std::string result;
    for (int i = 0; i < 24; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_quljEU() {
    const unsigned char data[] = {0x74, 0x4b, 0x51, 0x57, 0x43, 0x4e, 0x51, 0x02, 0x5e, 0x02};
    const int key = 34;
    std::string result;
    for (int i = 0; i < 10; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_UfYeZE() {
    const unsigned char data[] = {0x63, 0x4c, 0x40, 0x48, 0x0d, 0x6e, 0x42, 0x41, 0x42, 0x5f};
    const int key = 45;
    std::string result;
    for (int i = 0; i < 10; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static bool                     g_SwapChainOccluded = false;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool IsGameOnTop(const std::string& expectedTitle) {
    HWND hwnd = GetForegroundWindow();
    if (!hwnd) return false;

    char windowTitle[256];
    int length = GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));

    if (length == 0) return false;

    return expectedTitle == std::string(windowTitle);
}

void SetTransparency(HWND hwnd, bool boolean)
{
    LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
    if (boolean)
    {
        exStyle |= WS_EX_TRANSPARENT;
        SetWindowLong(hwnd, GWL_EXSTYLE, exStyle);
    }
    else
    {
        exStyle &= ~WS_EX_TRANSPARENT;
        SetWindowLong(hwnd, GWL_EXSTYLE, exStyle);
    }
}

void DrawNode(RobloxInstance& node)
{
    const auto& children = node.GetChildren();
    if (children.empty())
    {
        ImGui::BulletText(node.Name().c_str());
    }
    else
    {
        if (ImGui::TreeNode(node.Name().c_str()))
        {
            for (auto child : children)
            {
                DrawNode(child);
            }
            ImGui::TreePop();
        }
    }
}

void ShowImgui()
{
    ImGui_ImplWin32_EnableDpiAwareness();
    float main_scale = ImGui_ImplWin32_GetDpiScaleForMonitor(::MonitorFromPoint(POINT{ 0, 0 }, MONITOR_DEFAULTTOPRIMARY));

    size_t width = (size_t)GetSystemMetrics(SM_CXSCREEN);
    size_t height = (size_t)GetSystemMetrics(SM_CYSCREEN);

    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, Ldeobf_mZIFDp(), nullptr };
    ::RegisterClassExW(&wc);

    HWND hwnd = ::CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW,
        wc.lpszClassName,
        Ldeobf_IasVeV(),
        WS_POPUP,
        0, 0, width + 1, height + 1,
        nullptr, nullptr, wc.hInstance, nullptr);

    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 255, LWA_ALPHA);
    MARGINS Margin = { -1 };
    DwmExtendFrameIntoClientArea(hwnd, &Margin);

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
    }

    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();

    ImFontConfig config;
    config.MergeMode = false;
    config.PixelSnapH = true;

    ImFont* baseFont = io.Fonts->AddFontDefault(&config);

    config.MergeMode = true;

    static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

    io.Fonts->AddFontFromFileTTF(deobf_PrXGum(), 10.0f, &config, icon_ranges);
    io.Fonts->AddFontFromFileTTF(deobf_BYQiNA(), 10.0f, &config, icon_ranges);
    io.Fonts->AddFontFromFileTTF(deobf_BzESyU(), 10.0f, &config, icon_ranges);

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
    ImGui_ImplDX11_CreateDeviceObjects();

    ImVec4 clear_color = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    bool done = false;
    while (!done)
    {
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        if (g_SwapChainOccluded && g_pSwapChain->Present(0, 0) == DXGI_STATUS_OCCLUDED)
        {
            ::Sleep(10);
            continue;
        }
        g_SwapChainOccluded = false;

        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            g_ResizeWidth = g_ResizeHeight = 0;
            CreateRenderTarget();
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        static bool showMenu = true;
        static bool playerList = false;
        static bool explorer = false;

        static std::string spectatingSubject;

        if (GetAsyncKeyState(VK_INSERT) & 1) // change this if u don't have an insert key
        {
            SetTransparency(hwnd, showMenu);
            showMenu = !showMenu;
        }

        static int category = 0;

        ImGui::SetNextWindowSize(ImVec2(675, 550));

        auto character = Globals::Roblox::LocalPlayer.Character();

        if (showMenu)
        {
            ImGui::Begin(deobf_hIejFi(), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);

            if (ImGui::Button(deobf_quljEU() ICON_FA_EYE))
                category = 0;
            ImGui::SameLine();
            if (ImGui::Button(deobf_iuHKWy() ICON_FA_SHIELD))
                category = 1;
            ImGui::SameLine();
            if (ImGui::Button(deobf_Rzslsp() ICON_FA_CHESS))
                category = 2;
            ImGui::SameLine();
            if (ImGui::Button(deobf_spiAGh() ICON_FA_FOLDER))
                explorer = !explorer;
            ImGui::SameLine();
            if (ImGui::Button(deobf_sosNzs() ICON_FA_PEOPLE_GROUP))
                playerList = !playerList;
            ImGui::SameLine();
            if (ImGui::Button(deobf_jskdfI() ICON_FA_GEAR))
                category = 3;

            switch (category)
            {
                case 0: // Visuals
                {
                    ImGui::Checkbox(deobf_woPtYD(), &Options::ESP::TeamCheck);
                    ImGui::SameLine(540);
                    ImGui::ColorEdit3(deobf_ekRrLN(), Options::ESP::BoxColor, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
                    ImGui::Checkbox(deobf_nxyvNK(), &Options::ESP::Box);
                    ImGui::SameLine(540);
                    ImGui::ColorEdit4(deobf_KtbDpH(), Options::ESP::BoxFillColor, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
                    ImGui::Checkbox(deobf_gTGllF(), &Options::ESP::Skeleton);
                    ImGui::SameLine(540);
                    ImGui::ColorEdit3(deobf_PIvCeH(), Options::ESP::SkeletonColor, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
                    ImGui::NewLine();
                    ImGui::Checkbox(deobf_ajFPTo(), &Options::ESP::Name);
                    ImGui::SameLine(540);
                    ImGui::ColorEdit3(deobf_UfYeZE(), Options::ESP::Color, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
                    ImGui::Checkbox(deobf_sckcCJ(), &Options::ESP::Distance);
                    ImGui::SameLine(540);
                    ImGui::ColorEdit3(deobf_bzDRlk(), Options::ESP::DistanceColor, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
                    ImGui::Checkbox(deobf_jamFOx(), &Options::ESP::Health);
                    ImGui::NewLine();

                    ImGui::Checkbox(deobf_LTAuew(), &Options::ESP::ESP3D);
                    ImGui::SameLine(540);
                    ImGui::ColorEdit3(deobf_izUSne(), Options::ESP::ESP3DColor, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
                    ImGui::NewLine();

                    ImGui::Checkbox(deobf_IgBTBG(), &Options::ESP::HeadCircle);
                    ImGui::SameLine(540);
                    ImGui::ColorEdit3(deobf_HVgcfY(), Options::ESP::HeadCircleColor, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
                    ImGui::NewLine();

                    ImGui::Checkbox("Tracers", &Options::ESP::Tracers);
                    ImGui::SameLine(540);
                    ImGui::ColorEdit3(deobf_invDGD(), Options::ESP::TracerColor, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);

                    ImGui::SliderFloat(deobf_kAFJwM(), &Options::ESP::TracerThickness, 1.0f, 10.0f, deobf_SUksjl());

                    static const char* tracersStarts[]{ "Bottom","Top","Mouse","Torso" };

                    ImGui::Combo(deobf_DyKhTk(), &Options::ESP::TracersStart, tracersStarts, IM_ARRAYSIZE(tracersStarts));
                    break;
                }

                case 1: // Parry
                {
                    ImGui::Checkbox(deobf_WcCAWF(), &Options::Parry::Enabled);

                    ImGui::SameLine(564);
                    ImGui::SetNextItemWidth(100);
                    KeyBind::KeyBindButton("##ParryKey", &Options::Parry::ParryKey);

                    ImGui::Checkbox(deobf_zETowE(), &Options::Parry::AutoParry);

                    ImGui::NewLine();
                    ImGui::SliderFloat(deobf_zijbxl(), &Options::Parry::HoldTime, 0.01f, 5.0f, deobf_MVdeAj());
                    ImGui::SliderFloat(deobf_bxkRzK(), &Options::Parry::DelayTime, 0.001f, 1.0f, deobf_OVMEyu());
                    ImGui::SliderFloat(deobf_tqLJvY(), &Options::Parry::ParryWindow, 0.01f, 1.0f, deobf_MVdeAj());
                    
                    break;

                }
                case 2: // Misc.
                {
                    ImGui::SliderFloat("Walkspeed", &Options::Misc::Walkspeed, 0.f, 500.f, deobf_ZtfLCR());
                    ImGui::SliderFloat("JumpPower", &Options::Misc::JumpPower, 0.f, 500.f, deobf_ZtfLCR());
                    ImGui::SliderFloat("FOV", &Options::Misc::FOV, 1.f, 120, deobf_ZtfLCR());
                    break;
                }
                case 3:
                {
                    Globals::configsArray.clear();
                    for (const auto& entry : std::filesystem::directory_iterator(Globals::configsPath))
                    {
                        if (entry.path().extension() == ".json")
                        {
                            Globals::configsArray.push_back(entry.path().filename().string());
                        }
                    }

                    for (auto& config : Globals::configsArray)
                    {
                        ImVec2 cursorPos = ImGui::GetCursorScreenPos();
                        ImVec2 contentRegion = ImGui::GetContentRegionAvail();

                        float height = 30.0f;
                        float paddingX = 8.0f;

                        float buttonWidth = 30.0f;
                        float spacing = 5.0f;
                        float totalButtonWidth = (buttonWidth * 2) + spacing;
                        float labelWidth = contentRegion.x - totalButtonWidth - spacing;

                        ImVec2 rectMin = cursorPos;
                        ImVec2 rectMax = ImVec2(cursorPos.x + labelWidth - 6.f, cursorPos.y + height);

                        ImU32 rectColor = IM_COL32(35, 68, 108, 255);
                        ImU32 textColor = IM_COL32(255, 255, 255, 255);

                        ImGui::GetWindowDrawList()->AddRectFilled(rectMin, rectMax, rectColor);

                        ImVec2 textSize = ImGui::CalcTextSize(config.c_str());
                        ImVec2 textPos = ImVec2(
                            rectMin.x + (labelWidth - textSize.x) / 2.0f,
                            rectMin.y + (height - textSize.y) / 2.0f
                        );
                        ImGui::GetWindowDrawList()->AddText(textPos, textColor, config.c_str());

                        ImGui::SetCursorScreenPos(ImVec2(rectMax.x + spacing, rectMin.y));

                        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6.f, 6.f));

                        std::string loadId = std::string(ICON_FA_RECYCLE) + "##load" + config;
                        std::string deleteId = std::string(ICON_FA_TRASH) + "##delete" + config;

                        if (ImGui::Button(loadId.c_str(), ImVec2(buttonWidth, height)))
                        {
                            LoadConfig(config);
                        }

                        ImGui::SameLine();

                        if (ImGui::Button(deleteId.c_str(), ImVec2(buttonWidth, height)))
                        {
                            std::filesystem::remove(Globals::configsPath + "\\" + config);
                        }

                        ImGui::PopStyleVar();

                        ImGui::SetCursorScreenPos(ImVec2(cursorPos.x, rectMax.y + 5.0f));
                        ImGui::Dummy(ImVec2(1, 1));
                    }

                    static char buf[256] = "";

                    ImGui::InputText("##SaveIconInput", buf, sizeof(buf));
                    ImGui::SameLine();

                    if (ImGui::Button(ICON_FA_FLOPPY_DISK))
                        CreateConfig(std::string(static_cast<std::string>(buf) + ".json"));

                    ImGui::SetNextItemWidth(120);
                }
            }

            ImGui::End();
        }
        if (IsGameOnTop("Roblox"))
        {
            auto displaySize = io.DisplaySize;

            // Watermark

            std::string str = deobf_UxcrPE() + std::to_string(static_cast<int>(io.Framerate)) + deobf_drJyDE();

            ImVec2 textSize = ImGui::CalcTextSize(str.c_str());

            ImVec2 pos = ImVec2(displaySize.x - textSize.x - 10.0f, 10.0f);

            ImDrawList* drawList = ImGui::GetBackgroundDrawList();
            ImU32 outlineColor = IM_COL32(0, 0, 0, 255);
            ImU32 textColor = IM_COL32(255, 255, 255, 255);

            drawList->AddText(ImVec2(pos.x - 1, pos.y - 1), outlineColor, str.c_str());
            drawList->AddText(ImVec2(pos.x + 1, pos.y - 1), outlineColor, str.c_str());
            drawList->AddText(ImVec2(pos.x - 1, pos.y + 1), outlineColor, str.c_str());
            drawList->AddText(ImVec2(pos.x + 1, pos.y + 1), outlineColor, str.c_str());

            drawList->AddText(pos, textColor, str.c_str());
        }

        ImGui::SetNextWindowSize(ImVec2(500, 440));

        if (showMenu && explorer)
        {
            ImGui::Begin("Explorer", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
            for (auto& child : Globals::Roblox::DataModel.GetChildren())
            {
                DrawNode(child);
            }
            ImGui::End();
        }

        ImGui::SetNextWindowSize(ImVec2(500, 440));

        if (playerList && showMenu)
        {
            ImGui::Begin(deobf_GmHJic(), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);

            for (auto& player : Globals::Caches::CachedPlayerObjects)
            {
                ImGui::BulletText(player.Name.c_str());
                ImGui::SameLine();

                std::string teleportID = deobf_luYdtV() + player.Name;
                if (ImGui::Button(teleportID.c_str()))
                {
                    auto localCFrame = character.FindFirstChild("HumanoidRootPart").CFrame();
                    auto playerCFrame = player.Character.FindFirstChild("HumanoidRootPart").CFrame();

                    localCFrame.x = playerCFrame.x;
                    localCFrame.y = playerCFrame.y;
                    localCFrame.z = playerCFrame.z;

                    auto primitive = Memory->read<uintptr_t>(character.FindFirstChild("HumanoidRootPart").address + offsets::Primitive);

                    std::thread([=]() {
                        for (auto i = 0; i != 100; i++)
                            Memory->write<sCFrame>(primitive + offsets::CFrame, localCFrame);
                        }).detach(); // you gotta run it in a thread or it crashes cuz it times out ImGui
                }

                ImGui::SameLine();

                std::string spectateID = deobf_kSKTma() + player.Name;
                if (ImGui::Button(spectateID.c_str()))
                {
                    if (spectatingSubject == player.Name)
                    {
                        spectatingSubject = "";
                        Memory->write<uintptr_t>(Globals::Roblox::Camera.address + offsets::CameraSubject, character.FindFirstChildWhichIsA("Humanoid").address);
                    }
                    else
                    {
                        Memory->write<uintptr_t>(Globals::Roblox::Camera.address + offsets::CameraSubject, player.Humanoid.address);
                        spectatingSubject = player.Name;
                    }
                }
            }
            ImGui::End();
        }

        if (Options::ESP::Box || Options::ESP::Skeleton || Options::ESP::Tracers || Options::ESP::Name ||
            Options::ESP::Distance || Options::ESP::Health || Options::ESP::ESP3D)
        {
            if (!showMenu && IsGameOnTop("Roblox"))
                RenderESP(ImGui::GetBackgroundDrawList());
        }



        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        HRESULT hr = g_pSwapChain->Present(0, 0);
        g_SwapChainOccluded = (hr == DXGI_STATUS_OCCLUDED);
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
}


bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 4;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;

    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED)
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
