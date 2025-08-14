#ifndef TORTIMER_PAK_ROM_H
#define TORTIMER_PAK_ROM_H

#include <stddef.h>

/**
 * Writes the ROM data to the Controller Pak.
 * @param data Pointer to the ROM data.
 * @param size Size of the ROM data in bytes.
 * @param name Filename of the ROM.
 * @param compress If non-zero, compress the ROM data using Yay0.
 * @return 0 on success, negative error code on failure.
 */
int pak_write_rom(unsigned char *data, size_t size, const char *name,
  int compress);

#endif
