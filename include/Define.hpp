#ifndef __DEFINES_HPP__
#define __DEFINES_HPP__

#ifdef DEBUG
#define DEBUG_PRINT(str) do { std::cout << "[DEBUG] : " << str << std::endl; } while( false )
#else
#define DEBUG_PRINT(str) do { } while ( false )
#endif

void HexDump(uint8_t*, uint16_t, uint16_t);

#endif

