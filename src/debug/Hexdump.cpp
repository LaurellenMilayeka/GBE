#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

void HexDump(uint8_t *data, uint16_t start, uint16_t end)
{
  int i;
  uint16_t address = start;
  
  i = 0;
  while (address < end) {
    if ((i % 16) == 0 && i != 0) {
      dprintf(1, "\n");
      dprintf(1, "[DEBUG] : ");
      dprintf(1, "%04X : ", address);
      dprintf(1, "%02X", data[address]);
    } else if (i == 0) {
      dprintf(1, "[DEBUG] : ");
      dprintf(1, "%04X : ", address);
      dprintf(1, "%02X", data[address]);
    } else {
      if ((i % 2) == 0)
	dprintf(1, " ");
      dprintf(1, "%02X", data[address]);
    }
    i++;
    address++;
  }
  dprintf(1, "\n");
}
