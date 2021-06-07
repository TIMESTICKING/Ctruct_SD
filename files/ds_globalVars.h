#ifndef __DS_GLOBALVARS_H__
#define __DS_GLOBALVARS_H__

#include <stdlib.h>

#define SD_MALLOC(size)	(malloc(size))
#define	SD_FREE(point) 	(free(point))
#define SD_PRINT(...)\
			printf(__VA_ARGS__);\
			printf("\n");
#define SD_PRINT_HEAD(bigtype,subname)	 SD_PRINT("======%s:%s======",bigtype,subname)
#define SD_PRINT_END	SD_PRINT("=======================")
#define LOG_sta(status)		SD_PRINT("### status is %d ###",status)

#define c8 		signed char
#define u8_ds 	unsigned char
#define u16_ds	unsigned short
#define u32_ds	unsigned int

#ifndef NULL_void
#define NULL_void	((void*)0)

#endif	//null
#define	NULL_node	(Tree_node*)0


#define	ARR_OK			1
#define ARR_UN_INIT		-5
#define ARR_WRONG_INDEX	-1
#define ARR_MALLOC_FAIL	3
#define ARR_MOVE_FAIL	2
#define ARR_INPUT_SAME	-2
#define ARR_FALSE		0
#define ARR_EMPTY_CLIST	-3

int index_format(int totalLength,int ind);
int* INT_new(int number);

#endif

