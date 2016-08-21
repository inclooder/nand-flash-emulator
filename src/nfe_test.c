#include "nfe.h"

void nfe_test_clear_counters(NFE_FLASH * flash){
	flash->counters.reads = 0;
	flash->counters.writes = 0;
	flash->counters.block_erases = 0;
}

NFE_UINT32 nfe_test_get_write_count(NFE_FLASH * flash){
	return flash->counters.writes;
}
