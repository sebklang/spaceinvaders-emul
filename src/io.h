#ifndef IO_H
#define IO_H

#include <stdint.h>

typedef uint8_t  (*InputHandler) (uint8_t device);
typedef    void (*OutputHandler) (uint8_t device, uint8_t val);

#endif
