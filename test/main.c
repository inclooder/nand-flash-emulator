#include "unity.h"
#include "test_nfe.h"

int main(){
	UNITY_BEGIN();
	RUN_TEST(test_nfe_create_flash);
	RUN_TEST(test_nfe_clear_flash);
	RUN_TEST(test_nfe_write_1);
	RUN_TEST(test_nfe_write_2);
	RUN_TEST(test_nfe_erase_block);
	return UNITY_END();
}
