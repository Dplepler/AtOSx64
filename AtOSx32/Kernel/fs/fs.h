#ifndef FS_H
#define FS_H

#include <stdint.h>
#include "Drivers/ata.h"
#include "Memory/vmm.h"
#include "Drivers/kernel_screen.h"
#include "System/clock.h"
#include "System/errors.h"


#define HIDDEN_SECTORS 0x2
#define SECTOR_SIZE    0x200
#define CLUSTER_SIZE SECTOR_SIZE
#define CLUSTERS_IN_SECTOR (CLUSTER_SIZE / SECTOR_SIZE)
#define SYSTEM_SECTORS 0xFFFF
#define ROOT_ENTRIES 0X200
#define DIR_ENTRY_SIZE sizeof(inode_t)

#define SECTORS_IN_FAT ((SYSTEM_SECTORS * 2) / SECTOR_SIZE)
#define SECTORS_IN_ROOT ROOT_ENTRIES


#define KERNEL_SECTORS 100
#define KERNEL_CLUSTERS KERNEL_SECTORS
#define DATA_START (HIDDEN_SECTORS + SECTORS_IN_FAT + SECTORS_IN_ROOT + KERNEL_SECTORS)  /* Sector index indicating the beginning of data */

#define FAT_SIZE (SECTORS_IN_FAT * SECTOR_SIZE)
#define ROOT_SIZE (ROOT_ENTRIES * DIR_ENTRY_SIZE)

#define FAT_SECTOR_OFFSET HIDDEN_SECTORS 
#define ROOT_SECTOR_OFFSET (HIDDEN_SECTORS + SECTORS_IN_FAT)

#define FAT_OFFSET (FAT_SECTOR_OFFSET * SECTOR_SIZE)
#define ROOT_OFFSET (ROOT_SECTOR_OFFSET * SECTOR_SIZE)

#define EOC         0xFFF8     /* End of cluster */
#define BAD_CLUSTER 0xFFF7

#define FAT_SIGNATURE 0xA00A

#define FILENAME_SIZE  0x8
#define EXTENTION_SIZE 0x3

#define get_next_cluster fat_extract_value

#define READ_FAT(buffer)  (ata_read(FAT_SECTOR_OFFSET, SECTORS_IN_FAT, buffer))
#define WRITE_FAT(buffer) (ata_write(FAT_SECTOR_OFFSET, SECTORS_IN_FAT, buffer))

#define READ_ROOT(buffer) (ata_read(ROOT_SECTOR_OFFSET, ROOT_SIZE / SECTOR_SIZE, buffer))
#define WRITE_ROOT(buffer) (ata_write(ROOT_SECTOR_OFFSET, ROOT_SIZE / SECTOR_SIZE, buffer))

#define VALID_CLUSTER(cluster) (cluster != BAD_CLUSTER && cluster > 0x2)

typedef enum ATTRIBUTES_ENUM {

  ATTRIBUTE_READ = 0x0,
  ATTRIBUTE_HIDDEN,
  ATTRIBUTE_SYSTEM,
  ATTRIBUTE_VOLUME_LABEL,
  ATTRIBUTE_DIRECTORY,
  ATTRIBUTE_ACHIEVE

  };


typedef struct _INODE_ENTRY_STRUCT {

  char filename[FILENAME_SIZE];
  char ext[EXTENTION_SIZE];

  uint8_t attributes;

  uint8_t reserved1;

  uint8_t creation;
  
  uint16_t creation_time;
  uint16_t creation_date;
  uint16_t last_access_date;

  uint16_t reserved2;

  uint16_t last_write_time;
  uint16_t last_write_date;

  uint16_t cluster;

  uint32_t size;

} __attribute__((packed)) inode_t;


void init_fat();
void fat_setup_table();
uint16_t fat_extract_value(uint16_t index);

void fat_create_filename(inode_t* inode, char* name);
uint16_t fat_create_time(cmos_time date);
uint16_t fat_create_date(cmos_time date);

inode_t* create_file(char* filename,  uint8_t attributes);
inode_t* create_directory(char* dirname, uint8_t attributes);

uint16_t fat_find_free_cluster(void* buffer, int* err);

void write_file(inode_t* inode, void* buffer, size_t size);
void* read_file(inode_t* inode);

#endif
