#ifndef NFE_TYPES_H
#define NFE_TYPES_H

// Basic types

#ifndef NFE_INIT32
#define NFE_INT32 int
#endif

#ifndef NFE_UINT32
#define NFE_UINT32 unsigned int
#endif

#ifndef NFE_INT16
#define NFE_INT16 short
#endif

#ifndef NFE_UINT16
#define NFE_UINT16 unsigned short
#endif

#ifndef NFE_INT8
#define NFE_INT8 char
#endif

#ifndef NFE_UINT8
#define NFE_UINT8 unsigned char
#endif

// Errors

#define NFE_ERROR NFE_UINT16
#define NFE_ERROR_NO_ERROR 0
#define NFE_ERROR_INVALID_PARAM 1
#define NFE_ERROR_INVALID_BLOCK_NUMBER 2
#define NFE_ERROR_OUT_OF_BOUND 3

// Data structures

typedef struct {
	NFE_UINT32 reads;
	NFE_UINT32 writes;
	NFE_UINT32 block_erases;
} NFE_FLASH_TEST_COUNTERS;

typedef struct {
	NFE_UINT8 * memory;
	NFE_UINT32 num_of_blocks;
	NFE_UINT32 block_size;
	NFE_UINT32 memory_size;
	NFE_FLASH_TEST_COUNTERS counters;
} NFE_FLASH;

#endif /* end of include guard: NFE_TYPES_H */
