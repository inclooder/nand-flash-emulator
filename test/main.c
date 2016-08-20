#include "unity.h"
#include "test_nfe.h"

int main(){
	UNITY_BEGIN();
	RUN_TEST(test_nfe_create_flash);
	RUN_TEST(test_nfe_clear_flash);
	return UNITY_END();
}
