#include "pak_rom.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <libdragon.h>

#include "yay0tool/yay0.h"

typedef enum
{
  NESINFO_TAG_INVALID = 0,

  NESINFO_TAG_END,
  NESINFO_TAG_VERSION_EQUALS,
  NESINFO_TAG_VERSION_NOT_EQUAL,
  NESINFO_TAG_GAME_ID,
  NESINFO_TAG_GAME_NAME,
  NESINFO_TAG_CONTROLLER_PAK_NAME,
  NESINFO_TAG_OFFSET,
  NESINFO_TAG_HIGH_SCORES,
  NESINFO_TAG_GAME_NUMBER,
  NESINFO_TAG_BATTERY_BACKUP,
  NESINFO_TAG_QUICK_DISK_SAVE,
  NESINFO_TAG_SPECIAL,
  NESINFO_TAG_TAGS_CHECKSUM,
  NESINFO_TAG_IMAGE_CHECKSUM,
  NESINFO_TAG_EXPANDED_SIZE,
  NESINFO_TAG_ROM_DATA_REFERENCE,
  NESINFO_TAG_MOVE_DATA,
  NESINFO_TAG_NES_HEADER_DATA,
  NESINFO_TAG_DIFFERENCE,
  NESINFO_TAG_PATCH,
  NESINFO_TAG_PADDING,
  NESINFO_TAG_FILL_WRAM_INIT,
  NESINFO_TAG_IMAGE_SIZE,
  NESINFO_TAG_IMAGE_FORMAT,
  NESINFO_TAG_REMARKS,
  NESINFO_TAG_APPLICATION_INFO,
  NESINFO_TAG_FULL_GAME_NAME,

  NESINFO_TAG_SIZE
} nesinfo_tag_id;

typedef struct
{
  const nesinfo_tag_id id;
  const int supported;
  const unsigned minimum_length;
  const unsigned maximum_length;
  const char name[4];
} nesinfo_tag_format_t;

const nesinfo_tag_format_t nesinfo_tags[NESINFO_TAG_SIZE] =
{
  { NESINFO_TAG_INVALID, 0, 0, 0, "" },

  { NESINFO_TAG_END,                  1, 2, 2, "END" },
  { NESINFO_TAG_VERSION_EQUALS,       0, 1, 1, "VEQ" },
  { NESINFO_TAG_VERSION_NOT_EQUAL,    0, 1, 1, "VNE" },
  { NESINFO_TAG_GAME_ID,              0, 1, 0xFF, "GID" },  // char[]
  { NESINFO_TAG_GAME_NAME,            0, 1, 0xFF, "GNM" },  // char[]
  { NESINFO_TAG_CONTROLLER_PAK_NAME,  1, 16, 16, "CPN" }, /* Name of Controller Pak note, in cpak encoding */
  { NESINFO_TAG_OFFSET,               0, 2, 2, "OFS" },
  { NESINFO_TAG_HIGH_SCORES,          0, 3, 0xFF, "HSC" },  // ushort + char[]
  { NESINFO_TAG_GAME_NUMBER,          0, 1, 1, "GNO" },
  { NESINFO_TAG_BATTERY_BACKUP,       0, 4, 4, "BBR" },  // ushort + ushort
  { NESINFO_TAG_QUICK_DISK_SAVE,      0, 5, 5, "QDS" },  // byte + ushort + ushort
  { NESINFO_TAG_SPECIAL,              0, 0, 0, "SPE" },  // special patch, no args listed
  { NESINFO_TAG_TAGS_CHECKSUM,        0, 2, 2, "TCS" },
  { NESINFO_TAG_IMAGE_CHECKSUM,       0, 2, 2, "ICS" },
  { NESINFO_TAG_EXPANDED_SIZE,        0, 2, 2, "ESZ" },
  { NESINFO_TAG_ROM_DATA_REFERENCE,   0, 1, 1, "ROM" },
  { NESINFO_TAG_MOVE_DATA,            0, 6, 6, "MOV" },
  { NESINFO_TAG_NES_HEADER_DATA,      0, 1, 0x10, "NHD" },
  { NESINFO_TAG_DIFFERENCE,           0, 9, 0xFF, "DIF" },
  { NESINFO_TAG_PATCH,                0, 4, 0xFF, "PAT" },
  { NESINFO_TAG_PADDING,              0, 0, 0xFF, "PAD" },

  /* Unused Tags */
  { NESINFO_TAG_FILL_WRAM_INIT,       0, 1, 0xFF, "FIL" },
  { NESINFO_TAG_IMAGE_SIZE,           0, 2, 2, "ISZ" },
  { NESINFO_TAG_IMAGE_FORMAT,         0, 1, 1, "IFM" },
  { NESINFO_TAG_REMARKS,              0, 1, 0xFF, "REM" },
  { NESINFO_TAG_APPLICATION_INFO,     0, 1, 0xFF, "APL" },
  { NESINFO_TAG_FULL_GAME_NAME,       0, 1, 0xFF, "FGN" }
};

/* Arbitrary limit for size of tag data */
#define NESINFO_MAX_DATA_LEN 32

/* Arbitrary limit for number of tags */
#define NESINFO_MAX_TAGS 8

typedef struct
{
  unsigned char data[16];
} nesinfo_cpn_t;

typedef struct
{
  char magic1[7]; /* NESINFO */
  unsigned char magic2; /* 0x1A ? */
  unsigned int info_size; /* size of the rest of the header */
  unsigned int rom_size; /* size of the decompressed rom */
} nesinfo_header_t;

typedef struct
{
  char id[3];
  unsigned char size;
  unsigned char data[NESINFO_MAX_DATA_LEN];
} nesinfo_tag_t;

typedef struct
{
  nesinfo_header_t header;
  nesinfo_tag_t tags[NESINFO_MAX_TAGS];
  unsigned tag_count;
} nesinfo_t;

static void nesinfo_encode(const nesinfo_t *info, unsigned char *output,
  unsigned *out_size)
{
  unsigned offset = 0;
  unsigned i;

  if (!info || !output || !out_size)
    return;

  /* Write header */
  memcpy(output + offset, &info->header, sizeof(info->header));
  offset += sizeof(info->header);

  /* Write tags */
  for (i = 0; i < info->tag_count && i < NESINFO_MAX_TAGS; i++)
  {
    memcpy(output + offset, info->tags[i].id, 3);
    offset += 3;
    output[offset++] = info->tags[i].size;
    memcpy(output + offset, info->tags[i].data, info->tags[i].size);
    offset += info->tags[i].size;
  }

  if (out_size)
    *out_size = offset;
}

/**
 * Convert an ASCII character to its equivalent used in Controller Pak notes.
 * @param c ASCII character.
 * @return Corresponding character in Controller Pak note format.
 */
static unsigned char ascii2cpn(char c)
{
  if (c >= 'A' && c <= 'Z')
    return c - 'A' + 0x1A;
  else if (c >= 'a' && c <= 'z')
    return c - 'a' + 0x1A;
  else if (c >= '0' && c <= '9')
    return c - '0' + 0x10;
  else if (c == ' ')
    return 0x0F;
  else
    return 0x00; /* Invalid character, return 0 */
}

/**
 * Format a string to Controller Pak format: 16 characters, uppercase
 * letters and spaces only. Trim any tags like (USA).
 * @param dst Destination ASCII buffer (must be at least 16 bytes).
 * @param src Source ASCII string.
 * @param len Length of the source string.
 */
static void cpn_format(char *dst, const char *src, size_t len)
{
  unsigned char temp_path[16] = { 0 };
  int last_char_was_space = 0;
  unsigned i, j;

  for (i = 0, j = 0; i < len && src[i] != '\0' && j < 16 && src[i] != '(' && src[i] != '.'; i++)
  {
    char c = src[i];

    /* Convert lowercase letters to uppercase */
    if (c >= 'a' && c <= 'z')
      c -= 0x20;

    /* Acceptable characters: A-Z, 0-9, space, hyphen */
    if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '-' || c == ' ')
    {
      /* Collapse multiple spaces */
      if (c == ' ')
      {
        if (last_char_was_space)
          continue;
        last_char_was_space = 1;
      }
      else
        last_char_was_space = 0;

      temp_path[j++] = c;
    }
    else
    {
      /* Replace other characters with space, but avoid multiple spaces */
      if (!last_char_was_space)
      {
        temp_path[j++] = ' ';
        last_char_was_space = 1;
      }
    }
  }

  /* Remove trailing space if present */
  if (j > 0 && temp_path[j - 1] == ' ')
    temp_path[j - 1] = '\0';
  
  /* Copy to destination */
  memcpy(dst, temp_path, 16);
}

/**
 * Convert a ROM name to a CPN (Controller Pak Name) format.
 * @param name Name of the ROM.
 */
static nesinfo_cpn_t nesinfo_cpn(const char *name)
{
  nesinfo_cpn_t cpn;
  unsigned i;
  
  cpn_format((char*)cpn.data, name, strlen(name));

  /* Convert to CPN format */
  for (i = 0; i < 16; i++)
    cpn.data[i] = ascii2cpn((char)cpn.data[i]);

  return cpn;
}

/**
 * Generate NESINFO for the ROM data.
 * @param name Name of the ROM.
 * @param size Size of the uncompressed ROM data.
 */
static nesinfo_t nesinfo_generate(const char *name, unsigned size)
{
  nesinfo_t info;
  nesinfo_cpn_t cpn = nesinfo_cpn(name);
  unsigned i;

  memset(&info, 0, sizeof(info));
  memcpy(info.header.magic1, "NESINFO", sizeof(info.header.magic1));
  info.header.magic2 = 0x1A; /* Arbitrary magic byte? */
  info.header.info_size = sizeof(nesinfo_header_t) + sizeof(nesinfo_tag_t);
  info.header.rom_size = size;

  /* CPN tag */
  memcpy(info.tags[0].id, nesinfo_tags[NESINFO_TAG_CONTROLLER_PAK_NAME].name, 3);
  info.tags[0].size = sizeof(nesinfo_cpn_t);
  memcpy(info.tags[0].data, &cpn, sizeof(cpn));

  /* END tag */
  memcpy(info.tags[1].id, nesinfo_tags[NESINFO_TAG_END].name, 3);
  info.tags[1].size = nesinfo_tags[NESINFO_TAG_END].maximum_length;
  memset(info.tags[1].data, 0, nesinfo_tags[NESINFO_TAG_END].maximum_length);

  info.tag_count = 2;

  /* Calculate NESINFO size */
  info.header.info_size = 0;
  for (i = 0; i < info.tag_count; i++)
  {
    info.header.info_size += sizeof(info.tags[i].id);
    info.header.info_size += sizeof(info.tags[i].size);
    info.header.info_size += info.tags[i].size;
  }

  return info;
}

int pak_write_rom(unsigned char *data, unsigned size, const char *name,
  int compress)
{
  nesinfo_t nesinfo;
  unsigned char nesinfo_data[64];
  unsigned nesinfo_size;
  unsigned char *write_data = data;
  unsigned write_size = size;

  if (size == 0 || !data)
    return -1;

  /* Compress the ROM if requested */
  if (compress)
  {
    write_data = (unsigned char*)malloc(size);
    if (!write_data)
      return -2;
    if (yay0_compress(data, size, &write_data, &write_size) != YAY0_OK)
    {
      free(write_data);
      return -3;
    }
  }

  /* Generate NESINFO */
  nesinfo = nesinfo_generate(name, size);
  nesinfo_encode(&nesinfo, nesinfo_data, &nesinfo_size);

  if (!cpak_mount(JOYPAD_PORT_1, "cpak1:/"))
  {
    FILE *file;
    cpak_stats_t stats;
    char filename[64], formatted_name[32];
    size_t bytes_written = 0;

    /* Open Controller Pak file */
    cpn_format(formatted_name, name, strlen(name));
    snprintf(filename, sizeof(filename), "cpak1:/NAFJ.01/%s.", formatted_name);
    file = fopen(filename, "wb");
    if (!file)
    {
      cpak_unmount(JOYPAD_PORT_1);
      if (compress)
        free(write_data);
      return -4;
    }

    /* Write ROM data to Controller Pak */
    bytes_written += fwrite(nesinfo_data, 1, nesinfo_size, file);
    bytes_written += fwrite(write_data, 1, write_size, file);
    if (bytes_written != nesinfo_size + write_size)
    {
      printf("Wrote %u, expected %u: %s\n", bytes_written,
        nesinfo_size + write_size, strerror(errno));
      fclose(file);
      cpak_unmount(JOYPAD_PORT_1);
      if (compress)
        free(write_data);
      return -5;
    }
    fclose(file);

    cpak_get_stats(JOYPAD_PORT_1, &stats);
    printf("ROM successfully saved to Controller Pak.\n");
    printf("Bytes written: %u\n", bytes_written);
    printf("Pages used: %i\n", stats.pages.used);
    printf("Notes used: %i\n", stats.notes.used);
    cpak_unmount(JOYPAD_PORT_1);
    if (compress)
      free(write_data);

    return 0;
  }

  return -1;
}
