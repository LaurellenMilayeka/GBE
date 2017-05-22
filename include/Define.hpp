#pragma once

#include <iostream>

#ifdef DEBUG
#define DEBUG_PRINT(str) do { std::cout << "[DEBUG] : " << str << std::endl; } while( false )
#else
#define DEBUG_PRINT(str) do { } while ( false )
#endif

void HexDump(uint8_t*, uint16_t, uint16_t);
