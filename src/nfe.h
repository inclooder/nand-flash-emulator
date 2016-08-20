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
void nfe_clear_flash(NFE_FLASH * flash);

#endif /* end of include guard: NFE_H */
