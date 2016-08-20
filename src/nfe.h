#ifndef NFE_H
#define NFE_H

typedef struct {
	unsigned char * memory;
	unsigned int num_of_blocks;
	unsigned int block_size;
	unsigned int memory_size;
} NFE_FLASH;

NFE_FLASH * nfe_create_flash(unsigned short num_of_blocks, unsigned short block_size);
void nfe_destroy_flash(NFE_FLASH * flash);
void nfe_clear_flash(NFE_FLASH * flash, unsigned char clear_byte);
void nfe_write(NFE_FLASH * flash, unsigned int destination, void * source, unsigned int size);
void nfe_read(NFE_FLASH * flash, unsigned int source, void * destination, unsigned int size);
void nfe_erase_block(NFE_FLASH * flash, unsigned short block_number);

#endif /* end of include guard: NFE_H */
