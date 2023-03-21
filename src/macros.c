#include <stdint.h>

uint8_t Parity(uint8_t x)
{
    uint8_t count = 0;
    for (int i = 0; i < 8; i++) {
        count += (x >> i) & 1;
    }
    return count % 2 == 0;
}