#include "unity.h"
#include "test_nfe.h"

int main(){
	UNITY_BEGIN();
	RUN_TEST(test_nfe_create_flash);
	RUN_TEST(test_nfe_clear_flash);
	RUN_TEST(test_nfe_write_1);
	RUN_TEST(test_nfe_write_2);
	RUN_TEST(test_nfe_write_3);
	RUN_TEST(test_nfe_erase_block_1);
	RUN_TEST(test_nfe_erase_block_2);
	RUN_TEST(test_nfe_read_1);
	RUN_TEST(test_nfe_read_2);
	RUN_TEST(test_nfe_test_clear_counters);
	RUN_TEST(test_nfe_test_get_write_count);
	RUN_TEST(test_nfe_test_get_erase_block_count);
	return UNITY_END();
}
