#include "nfe.h"

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
	for(int i = 0; i < flash->memory_size; i++){
		flash->memory[i] = clear_byte;
	}
}

void nfe_destroy_flash(NFE_FLASH * flash){
	free(flash->memory);
	free(flash);
}
