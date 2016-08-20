#include "nfe.h"
#include <string.h>
#include <stdlib.h>

NFE_FLASH * nfe_create_flash(unsigned short num_of_blocks, unsigned short block_size){
	unsigned int memory_size = num_of_blocks * block_size;

	NFE_FLASH * flash = malloc(sizeof(NFE_FLASH));
	flash->memory_size = memory_size;
	flash->num_of_blocks = num_of_blocks;
	flash->block_size = block_size;
	flash->memory = malloc(memory_size);
	
	nfe_clear_flash(flash, 0xFF);

	return flash;
}

void nfe_clear_flash(NFE_FLASH * flash, unsigned char clear_byte){
	int i;
	for(i = 0; i < flash->memory_size; i++){
		flash->memory[i] = clear_byte;
	}
}

void nfe_destroy_flash(NFE_FLASH * flash){
	free(flash->memory);
	free(flash);
}

void nfe_write(NFE_FLASH * flash, unsigned int destination, void * source, unsigned int size){
	if(destination + size > flash->memory_size) return;
	int i;
	unsigned int current;
	for(i = 0; i < size; i++){
		current = destination + i;
		unsigned char old_val = flash->memory[current];
		unsigned char new_val = ((unsigned char *)source)[i];
		flash->memory[current] = old_val & new_val;
	}
}
void nfe_read(NFE_FLASH * flash, unsigned int source, void * destination, unsigned int size){
	memcpy(destination, flash->memory + source, size);
}
void nfe_erase_block(NFE_FLASH * flash, unsigned short block_number){
}
