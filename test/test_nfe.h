#ifndef TEST_NFE_H
#define TEST_NFE_H

#include "unity.h"
#include "nfe.h"
#include <stdlib.h>

void test_nfe_create_flash(void){
	NFE_FLASH * flash = nfe_create_flash(256, 1024);
	TEST_ASSERT_EQUAL(256, flash->num_of_blocks);
	TEST_ASSERT_EQUAL(1024, flash->block_size);
	TEST_ASSERT_EQUAL(262144, flash->memory_size);
	TEST_ASSERT_EQUAL(0, flash->counters.reads);
	TEST_ASSERT_EQUAL(0, flash->counters.writes);
	TEST_ASSERT_EQUAL(0, flash->counters.block_erases);

	nfe_destroy_flash(flash);
}

void test_nfe_clear_flash(void){
	NFE_FLASH * flash = nfe_create_flash(256, 100);
	nfe_clear_flash(flash, 0x11);
	NFE_INT32 i;
	for(i = 0; i < flash->memory_size; i++){
		TEST_ASSERT_EQUAL(0x11, flash->memory[i]);
	}
	nfe_destroy_flash(flash);
}

void test_nfe_write_1(void){
	NFE_FLASH * flash = nfe_create_flash(256, 100);
	NFE_UINT8 buff[2] = { 0x00, 0x00 };
	nfe_write(flash, 10, &buff, 2);
	TEST_ASSERT_EQUAL_MEMORY(&buff, flash->memory + 10, 2);
	nfe_destroy_flash(flash);
}

void test_nfe_write_2(void){
	NFE_FLASH * flash = nfe_create_flash(256, 99);
	NFE_UINT8 buff1[2] = { 0xFF, 0x00 };
	nfe_write(flash, 20, &buff1, 2);
	NFE_UINT8 buff2[2] = { 0x00, 0xFF };
	nfe_write(flash, 20, &buff2, 2);
	NFE_UINT8 expected[2] = { 0x00, 0x00 };
	TEST_ASSERT_EQUAL_MEMORY(&expected, flash->memory + 20, 2);
	nfe_destroy_flash(flash);
}

void test_nfe_write_3(void){
	NFE_FLASH * flash = nfe_create_flash(10, 10);
	NFE_UINT8 buff[50] = { 0x00 };
	NFE_ERROR error = nfe_write(flash, 90, &buff, 50);
	TEST_ASSERT_EQUAL(NFE_ERROR_OUT_OF_BOUND, error);
	nfe_destroy_flash(flash);
}

void test_nfe_erase_block_1(void){
	NFE_FLASH * flash = nfe_create_flash(13, 201);
	NFE_UINT8 buff[2] = { 0xAB, 0xCD };
	nfe_write(flash, 333, &buff, 2); //Second block
	TEST_ASSERT_EQUAL_MEMORY(&buff, flash->memory + 333, 2);
	nfe_erase_block(flash, 1); //Erase second block (count from 0)

	NFE_UINT8 * expected = malloc(201);
	NFE_UINT32 i;
	for(i = 0; i < 201; i++){
		expected[i] = 0xFF;
	}

	TEST_ASSERT_EQUAL_MEMORY(expected, flash->memory + 333, 201);
	nfe_destroy_flash(flash);
}

void test_nfe_erase_block_2(void){
	NFE_FLASH * flash = nfe_create_flash(13, 50);
	NFE_ERROR error = nfe_erase_block(flash, 13);
	TEST_ASSERT_EQUAL(NFE_ERROR_INVALID_BLOCK_NUMBER, error);
	nfe_destroy_flash(flash);
}

void test_nfe_read_1(void){
	NFE_FLASH * flash = nfe_create_flash(20, 150);
	NFE_UINT8 buff[10] = {
		0x01, 0x02, 0x03, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0x11, 0x55
	};
	nfe_write(flash, 1000, &buff, 10);
	NFE_UINT8 read_buff[10];
	nfe_read(flash, &read_buff, 1000, 10);
	TEST_ASSERT_EQUAL_MEMORY(read_buff, buff, 10);

	nfe_destroy_flash(flash);
}

void test_nfe_read_2(void){
	NFE_FLASH * flash = nfe_create_flash(10, 100);
	NFE_UINT8 read_buff[10];
	NFE_ERROR error = nfe_read(flash, &read_buff, 999, 1);
	TEST_ASSERT_EQUAL(NFE_ERROR_OUT_OF_BOUND, error);
	nfe_destroy_flash(flash);
}

void test_nfe_test_clear_counters(void){
	NFE_FLASH * flash = nfe_create_flash(10, 100);
	flash->counters.reads = 1;
	flash->counters.writes = 1;
	flash->counters.block_erases = 1;
	nfe_test_clear_counters(flash);

	TEST_ASSERT_EQUAL(0, flash->counters.reads);
	TEST_ASSERT_EQUAL(0, flash->counters.writes);
	TEST_ASSERT_EQUAL(0, flash->counters.block_erases);

	nfe_destroy_flash(flash);
}

void test_nfe_test_get_write_count(void){
	NFE_FLASH * flash = nfe_create_flash(10, 100);
	NFE_UINT8 buff[50] = { 0x00 };
	NFE_ERROR error = nfe_write(flash, 90, &buff, 50);
	NFE_UINT32 write_count = nfe_test_get_write_count(flash);
	TEST_ASSERT_EQUAL(1, write_count);
	nfe_destroy_flash(flash);
}

void test_nfe_test_get_erase_block_count(void){
	NFE_FLASH * flash = nfe_create_flash(10, 100);
	nfe_erase_block(flash, 0);
	nfe_erase_block(flash, 1);
	nfe_erase_block(flash, 1);
	NFE_UINT32 erase_count = nfe_test_get_erase_block_count(flash);
	TEST_ASSERT_EQUAL(3, erase_count);
	nfe_destroy_flash(flash);
}


#endif /* end of include guard: TEST_NFE_H */
