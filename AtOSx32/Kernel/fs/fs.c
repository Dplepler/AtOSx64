#include "fs.h"


uint8_t fat_buffer[SECTORS_IN_FAT * SECTOR_SIZE];

void init_fat() {  
  if (fat_extract_value(0) != 0xFFF8) { fat_setup_table(); }
}

void fat_setup_table() {
 
  memsetw(fat_buffer, EOC, SECTORS_IN_FAT * SECTOR_SIZE);
  ata_write(HIDDEN_SECTORS + 1, SECTORS_IN_FAT, fat_buffer);
}


uint16_t fat_extract_value(uint16_t index) {
  
  ata_read(HIDDEN_SECTORS + 1, SECTORS_IN_FAT, fat_buffer);
  return (uint16_t)(((uint16_t*)fat_buffer)[index]);
}


