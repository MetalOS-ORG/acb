/* -------------------------------------------

    Copyright Mahrouss Logic

------------------------------------------- */

#ifndef __PARTITION_MAP_H__
#define __PARTITION_MAP_H__

#include <lib/types.h>

/// @brief EPM GUID block.
typedef struct boot_guid {
  unsigned data1;
  unsigned short data2;
  unsigned short data3;
  unsigned char data4[8];
} boot_guid_t;

/* The first 0 > 128 addresses of a disk contains these headers. */

/**
 * @brief The EPM boot block.
 * Stores information about the disk.
 */
struct __attribute__((packed)) boot_block {
  ascii_char_t magic[4];
  char name[32];
  boot_guid_t uuid;
  int version;
  long long int num_blocks;
  long long int sector_sz;
  long long int lba_start;
};

/**
 * @brief The EPM partition block.
 * used to explain a partition inside a media.
 */
struct __attribute__((packed)) part_block {
  char name[32];
  int version;
  long long int lba_end;
  long long int sector_sz;
  long long int lba_start;
  short type;
  int fs_version;
  char fs[16]; /* ffs_2 */
};

typedef struct part_block part_block_t;
typedef struct boot_block boot_block_t;

/* @brief AMD64 magic for EPM */
#define EPM_MAGIC_X86 "EPMAM"

/* @brief RISC-V magic for EPM */
#define EPM_MAGIC_RV "EPMRV"

/* @brief ARM magic for EPM */
#define EPM_MAGIC_ARM "EPMAR"

/* @brief 64x0 magic for EPM */
#define EPM_MAGIC_64x0 "EPM64"

/* @brief 32x0 magic for EPM */
#define EPM_MAGIC_32x0 "EPM32"

/* @brief PowerPC magic for EPM */
#define EPM_MAGIC_PPC "EPMPC"

#define EPM_MAX_BLKS 128

#define EPM_BOOT_BLK_SZ sizeof(struct boot_block)
#define EPM_PART_BLK_SZ sizeof(struct part_block)

//! version types.
//! use in boot block version field.

enum {
  EPM_MPUX = 0xcf,
  EPM_LINUX = 0x8f,
  EPM_BSD = 0x9f,
  EPM_NEWOS = 0x1f,
};

/// @brief Start of EPM headers.
/// @note There could be anything before this LBA.
/// Such as PC specific structures.
#define EPM_PART_BLK_START 0

/// @brief EPM revision (2)
#define EPM_REVISION 2

/// END SPECS

boolean mp_filesystem_exists(caddr_t fs);

#endif  // ifndef __PARTITION_MAP_H__