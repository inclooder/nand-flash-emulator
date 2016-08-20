#ifndef NFE_H
#define NFE_H

#include "nfe_types.h"

typedef struct {
	NFE_UINT8 * memory;
	NFE_UINT32 num_of_blocks;
	NFE_UINT32 block_size;
	NFE_UINT32 memory_size;
} NFE_FLASH;

NFE_FLASH * nfe_create_flash(NFE_UINT16 num_of_blocks, NFE_UINT16 block_size);
void nfe_destroy_flash(NFE_FLASH * flash);
void nfe_clear_flash(NFE_FLASH * flash, NFE_UINT8 clear_byte);
void nfe_write(NFE_FLASH * flash, NFE_UINT32 destination, void * source, NFE_UINT32 size);
void nfe_read(NFE_FLASH * flash, NFE_UINT32 source, void * destination, NFE_UINT32 size);
void nfe_erase_block(NFE_FLASH * flash, NFE_UINT16 block_number);

#endif /* end of include guard: NFE_H */
