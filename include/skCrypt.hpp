#pragma once
#include "obfuscator.hpp"

// Make obfuscated strings compatible with skCrypt syntax
#define skCrypt(str) OBF(str)