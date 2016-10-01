#ifndef NFE_H
#define NFE_H

#include "nfe_types.h"

NFE_FLASH * nfe_create_flash(NFE_UINT16 num_of_blocks, NFE_UINT16 block_size);
void nfe_destroy_flash(NFE_FLASH * flash);
void nfe_clear_flash(NFE_FLASH * flash, NFE_UINT8 clear_byte);
NFE_ERROR nfe_write(NFE_FLASH * flash, NFE_UINT32 destination, void * source, NFE_UINT32 size);
NFE_ERROR nfe_read(NFE_FLASH * flash, void * destination, NFE_UINT32 source, NFE_UINT32 size);
NFE_ERROR nfe_erase_block(NFE_FLASH * flash, NFE_UINT16 block_number);
NFE_ERROR nfe_dump_to_file(NFE_FLASH * flash, const char * file_path);

void nfe_test_clear_counters(NFE_FLASH * flash);
NFE_UINT32 nfe_test_get_write_count(NFE_FLASH * flash);
NFE_UINT32 nfe_test_get_read_count(NFE_FLASH * flash);
NFE_UINT32 nfe_test_get_erase_block_count(NFE_FLASH * flash);

#endif /* end of include guard: NFE_H */
