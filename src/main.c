#include "pak_letter.h"
#include "pak_rom.h"

#include <stdio.h>
#include <string.h>

#include <libdragon.h>

static size_t load_file(void *dst, unsigned size, const char *path)
{
  FILE *file = fopen(path, "rb");
  size_t bytes_read;

  if (!file)
  {
    printf("Failed to open file: %s\n", path);
    return -1;
  }

  bytes_read = fread(dst, 1, size, file);
  fclose(file);

  return bytes_read;
}

#define ROM_SIZE 256 * 1024

int main(void)
{
  unsigned char *rom_data;

  /* Initialize console */
  rdpq_init();
  console_init();
  console_set_render_mode(RENDER_AUTOMATIC);
  console_clear();

  rom_data = (unsigned char*)malloc(ROM_SIZE);
  if (!rom_data)
  {
    printf("Failed to allocate memory for ROM data.\n");
    return -1;
  }

  /* Initialize controller */
  joypad_init();

  /* Initialize assets */
  int dfs_result = dfs_init(DFS_DEFAULT_LOCATION);
  if (dfs_result < 0)
  {
    printf("Failed to initialize DFS: %d\n", dfs_result);
    return -1;
  }
  debug_init_sdfs("sd:/", -1);

  printf("Tortimer\n\n");
  printf("L: Write letter data to Pak\n");
  printf("R: Write sd:/nes/rom.nes to Pak\n");
  printf("B: Write sd:/nes/rom.nes to Pak without compression\n");
  printf("Z: Write rom:/roms/rom.nes to Pak\n\n");

  while (64)
  {
    joypad_buttons_t buttons;
    size_t size;
    int result = 0, finished = 0;

    joypad_poll();
    buttons = joypad_get_buttons_pressed(JOYPAD_PORT_1);

    if (buttons.l)
    {
      result = pak_write_letter();
      finished = 1;
    }
    else if (buttons.r)
    {
      size = load_file(rom_data, ROM_SIZE, "sd:/nes/rom.nes");
      result = pak_write_rom(rom_data, size, "rom", 1);
      finished = 1;
    }
    else if (buttons.b)
    {
      size = load_file(rom_data, ROM_SIZE, "sd:/nes/rom.nes");
      result = pak_write_rom(rom_data, size, "rom", 0);
      finished = 1;
    }
    else if (buttons.z)
    {
      size = load_file(rom_data, ROM_SIZE, "rom:/roms/rom.nes");
      result = pak_write_rom(rom_data, size, "rom", 1);
      finished = 1;
    }

    if (finished)
    {
      printf("Result: %d\n", result);
      exit(result);
    }
  }
}
