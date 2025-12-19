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

  /* Name of Controller Pak note, in Controller Pak note encoding */
  NESINFO_TAG_CONTROLLER_PAK_NAME,

  NESINFO_TAG_OFFSET,
  NESINFO_TAG_HIGH_SCORES,
  NESINFO_TAG_GAME_NUMBER,
  NESINFO_TAG_BATTERY_BACKUP,
  NESINFO_TAG_QUICK_DISK_SAVE,
  NESINFO_TAG_SPECIAL,
  NESINFO_TAG_TAGS_CHECKSUM,
  NESINFO_TAG_IMAGE_CHECKSUM,

  /* Size of Yay0 file once decompressed */
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

  { NESINFO_TAG_END,                  1, 0, 0xFF, "END" },
  { NESINFO_TAG_VERSION_EQUALS,       0, 1, 1, "VEQ" },
  { NESINFO_TAG_VERSION_NOT_EQUAL,    0, 1, 1, "VNE" },
  { NESINFO_TAG_GAME_ID,              0, 1, 0xFF, "GID" },
  { NESINFO_TAG_GAME_NAME,            0, 1, 0xFF, "GNM" },
  { NESINFO_TAG_CONTROLLER_PAK_NAME,  1, 16, 16, "CPN" },
  { NESINFO_TAG_OFFSET,               0, 2, 2, "OFS" },
  { NESINFO_TAG_HIGH_SCORES,          0, 3, 0xFF, "HSC" },
  { NESINFO_TAG_GAME_NUMBER,          0, 1, 1, "GNO" },
  { NESINFO_TAG_BATTERY_BACKUP,       0, 4, 4, "BBR" },
  { NESINFO_TAG_QUICK_DISK_SAVE,      0, 5, 5, "QDS" },
  { NESINFO_TAG_SPECIAL,              0, 0, 0, "SPE" },
  { NESINFO_TAG_TAGS_CHECKSUM,        0, 2, 2, "TCS" },
  { NESINFO_TAG_IMAGE_CHECKSUM,       0, 2, 2, "ICS" },
  { NESINFO_TAG_EXPANDED_SIZE,        1, 2, 2, "ESZ" },
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
 * @param cmp_size Size of the compressed ROM data, or 0 if not compressed.
 * @param raw_size Size of the decompressed ROM data.
 */
static nesinfo_t nesinfo_generate(const char *name, unsigned cmp_size,
  unsigned raw_size)
{
  nesinfo_t info;
  nesinfo_cpn_t cpn = nesinfo_cpn(name);
  nesinfo_tag_t *tag = &info.tags[0];
  unsigned i;

  memset(&info, 0, sizeof(info));
  memcpy(info.header.magic1, "NESINFO", sizeof(info.header.magic1));
  info.header.magic2 = 0x1A; /* Arbitrary magic byte? */
  info.header.rom_size = cmp_size ? cmp_size : raw_size;
  info.tag_count = 0;

  /* CPN tag */
  memcpy(tag->id, nesinfo_tags[NESINFO_TAG_CONTROLLER_PAK_NAME].name, 3);
  tag->size = sizeof(nesinfo_cpn_t);
  memcpy(tag->data, &cpn, sizeof(cpn));
  tag++; info.tag_count++;

  /* ESZ tag */
  if (cmp_size && cmp_size < raw_size)
  {
    unsigned short value = raw_size >> 4;

    memcpy(tag->id, nesinfo_tags[NESINFO_TAG_EXPANDED_SIZE].name, 3);
    tag->size = nesinfo_tags[NESINFO_TAG_EXPANDED_SIZE].minimum_length;
    memcpy(tag->data, &value, sizeof(value));
    tag++; info.tag_count++;
  }

  /* END tag */
  memcpy(tag->id, nesinfo_tags[NESINFO_TAG_END].name, 3);
  tag->size = 2; /** @todo: is this used to align? */
  memset(tag->data, 0, tag->size);
  tag++; info.tag_count++;

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

int pak_write_rom(unsigned char *data, size_t size, const char *name,
  int compress)
{
  nesinfo_t nesinfo;
  unsigned char nesinfo_data[64];
  size_t nesinfo_size;
  unsigned char *write_data = data;
  size_t write_size = size;

  if (size == 0 || !data)
    return -1;

  printf("Writing ROM data to Controller Pak: %s (%u bytes)\n", name, size);

  if (cpakfs_format(JOYPAD_PORT_1, true))
  {
    printf("Failed to format Controller Pak: %s\n", strerror(errno));
    return -1;
  }
  else
    printf("Controller Pak formatted.\n");

  /* Compress the ROM if requested */
  if (compress)
  {
    int result;

    printf("Compressing ROM data to Yay0...\n");
    write_data = (unsigned char*)malloc(size);
    if (!write_data)
      return -2;
    result = yay0_compress(data, size, &write_data, &write_size);
    if (result != YAY0_OK)
    {
      printf("Failed to compress ROM data: %d\n", result);
      free(write_data);
      return result;
    }
    else
      printf("ROM data compressed. (%u -> %u)\n", size, write_size);
  }

  /* Generate NESINFO */
  nesinfo = nesinfo_generate(name, write_size, size);
  nesinfo_encode(&nesinfo, nesinfo_data, &nesinfo_size);

  if (!cpakfs_mount(JOYPAD_PORT_1, "cpak1:/"))
  {
    FILE *file;
    char filename[64], formatted_name[32];
    size_t bytes_written = 0;
    cpakfs_stats_t stats;

    /* Open Controller Pak file */
    cpn_format(formatted_name, name, strlen(name));
    snprintf(filename, sizeof(filename), "cpak1:/NAFJ.01-%s", formatted_name);
    file = fopen(filename, "wb");
    if (!file)
    {
      cpakfs_unmount(JOYPAD_PORT_1);
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
      cpakfs_unmount(JOYPAD_PORT_1);
      if (compress)
        free(write_data);
      return -5;
    }
    fclose(file);

    cpakfs_get_stats(JOYPAD_PORT_1, &stats);
    printf("ROM successfully saved to Controller Pak.\n");
    printf("Bytes written: %u\n", bytes_written);
    printf("Pages used: %i\n", stats.pages.used);
    printf("Notes used: %i\n", stats.notes.used);
    cpakfs_unmount(JOYPAD_PORT_1);
    if (compress)
      free(write_data);

    return 0;
  }

  return -1;
}
