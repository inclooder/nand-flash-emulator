#include "nfe.h"
#include <string.h>
#include <stdlib.h>

NFE_FLASH * nfe_create_flash(NFE_UINT16 num_of_blocks, NFE_UINT16 block_size){
	NFE_UINT32 memory_size = num_of_blocks * block_size;

	NFE_FLASH * flash = malloc(sizeof(NFE_FLASH));
	flash->memory_size = memory_size;
	flash->num_of_blocks = num_of_blocks;
	flash->block_size = block_size;
	flash->memory = malloc(memory_size);
	
	nfe_clear_flash(flash, 0xFF);
	nfe_test_clear_counters(flash);

	return flash;
}

void nfe_clear_flash(NFE_FLASH * flash, NFE_UINT8 clear_byte){
	NFE_INT32 i;
	for(i = 0; i < flash->memory_size; i++){
		flash->memory[i] = clear_byte;
	}
}

void nfe_destroy_flash(NFE_FLASH * flash){
	free(flash->memory);
	free(flash);
}

NFE_ERROR nfe_write(NFE_FLASH * flash, NFE_UINT32 destination, void * source, NFE_UINT32 size){
	if(destination + size > flash->memory_size) {
		return NFE_ERROR_OUT_OF_BOUND;
	}
	NFE_INT32 i;
	NFE_UINT32 current;
	for(i = 0; i < size; i++){
		current = destination + i;
		NFE_UINT8 old_val = flash->memory[current];
		NFE_UINT8 new_val = ((NFE_UINT8 *)source)[i];
		flash->memory[current] = old_val & new_val;
	}
	flash->counters.writes++;
	return NFE_ERROR_NO_ERROR;
}

NFE_ERROR nfe_read(NFE_FLASH * flash, void * destination, NFE_UINT32 source, NFE_UINT32 size){
	if(source + size > flash->memory_size) {
		return NFE_ERROR_OUT_OF_BOUND;
	}
	memcpy(destination, flash->memory + source, size);
	return NFE_ERROR_NO_ERROR;
}

NFE_ERROR nfe_erase_block(NFE_FLASH * flash, NFE_UINT16 block_number){
	if(block_number >= flash->num_of_blocks) {
		return NFE_ERROR_INVALID_BLOCK_NUMBER;
	} 	
	memset(flash->memory + (block_number * flash->block_size), 0xFF, flash->block_size);
	flash->counters.block_erases++;
	return NFE_ERROR_NO_ERROR;
}

