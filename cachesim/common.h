#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define exp2(x) (1 << (x))
#define mask_with_len(x) (exp2(x) - 1)

#define MEM_SIZE (1 << 25) // 1MB
#define BLOCK_WIDTH  6  // 64B
#define BLOCK_SIZE exp2(BLOCK_WIDTH)//64B

//测试不同cache性能时，在更改main函数init_cache参数的同时这里也需要同步更改
#define totalSizeWidth 14
#define assoWidth 2


#define CACHE_SIZE (1<<totalSizeWidth)
#define CACHE_ASSO (1<<assoWidth)
#define cache_groupnum_bit (totalSizeWidth-assoWidth-BLOCK_WIDTH)
#define cache_group_num exp2(cache_groupnum_bit)
#define cache_line_num CACHE_ASSO

#define mem_blockaddr_bit BLOCK_WIDTH

typedef uint8_t bool;
#define true 1
#define false 0

void cycle_increase(int n);

#endif
