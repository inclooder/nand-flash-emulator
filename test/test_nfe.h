#ifndef TEST_NFE_H
#define TEST_NFE_H

#include "unity.h"
#include "nfe.h"

void test_nfe_create_flash(void){
	NFE_FLASH * flash = nfe_create_flash(256, 1024);
	TEST_ASSERT_EQUAL(256, flash->num_of_blocks);
	TEST_ASSERT_EQUAL(1024, flash->block_size);
	TEST_ASSERT_EQUAL(262144, flash->memory_size);

	nfe_destroy_flash(flash);
}

void test_nfe_clear_flash(void){
	NFE_FLASH * flash = nfe_create_flash(256, 100);
	nfe_clear_flash(flash, 0x11);
	int i;
	for(i = 0; i < flash->memory_size; i++){
		TEST_ASSERT_EQUAL(0x11, flash->memory[i]);
	}
	nfe_destroy_flash(flash);
}

void test_nfe_write_1(void){
	NFE_FLASH * flash = nfe_create_flash(256, 100);
	char buff[2] = { 0x00, 0x00 };
	nfe_write(flash, 10, &buff, 2);
	TEST_ASSERT_EQUAL_MEMORY(&buff, flash->memory + 10, 2);
	nfe_destroy_flash(flash);
}

void test_nfe_write_2(void){
	NFE_FLASH * flash = nfe_create_flash(256, 99);
	char buff1[2] = { 0xFF, 0x00 };
	nfe_write(flash, 20, &buff1, 2);
	char buff2[2] = { 0x00, 0xFF };
	nfe_write(flash, 20, &buff2, 2);
	char expected[2] = { 0x00, 0x00 };
	TEST_ASSERT_EQUAL_MEMORY(&expected, flash->memory + 20, 2);
	nfe_destroy_flash(flash);
}

#endif /* end of include guard: TEST_NFE_H */
