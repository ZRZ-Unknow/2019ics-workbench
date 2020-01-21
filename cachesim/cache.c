#include "common.h"
#include <inttypes.h>
#include <string.h>
void mem_read(uintptr_t block_num, uint8_t *buf);
void mem_write(uintptr_t block_num, const uint8_t *buf);
#define offset ((1<<BLOCK_WIDTH)-1)
static uint64_t cycle_cnt = 0;
static uint64_t hit=0;
static uint64_t miss=0;
typedef struct
{
  bool valid;
  bool dirty;
  uint64_t tag;
  uint64_t mem_block_num;
  uint8_t data[BLOCK_SIZE];
}cache_line;
cache_line cache[cache_group_num][cache_line_num];

void cycle_increase(int n) { cycle_cnt += n; }

// TODO: implement the following functions

uint32_t cache_read(uintptr_t addr) {
  addr&=~0x3;
  int group_num=(addr&((1<<(cache_groupnum_bit+mem_blockaddr_bit))-1))>>mem_blockaddr_bit;
  for(int i=0;i<cache_line_num;i++){
    cycle_increase(1);
    if(cache[group_num][i].valid==1 && cache[group_num][i].tag==(addr>>(mem_blockaddr_bit+cache_groupnum_bit))){
      hit++;
      uint32_t *res=(void*)(cache[group_num][i].data+((addr %BLOCK_SIZE)));
      return *res;
    }
  }
  //未命中
  miss++;
  for(int i=0;i<cache_line_num;i++){
    cycle_increase(1);
    if(cache[group_num][i].valid==0){
      mem_read(addr>>mem_blockaddr_bit,cache[group_num][i].data); //从主存读取主存块号
      cache[group_num][i].valid=1;
      cache[group_num][i].tag=addr>>(mem_blockaddr_bit+cache_groupnum_bit);
      cache[group_num][i].mem_block_num=addr>>mem_blockaddr_bit;
      uint32_t* res=(void*)(cache[group_num][i].data+((addr%BLOCK_SIZE)));
      return *res;
    }
  }
  //没有空闲行
  int line=rand()%cache_line_num;
  cycle_increase(1);
  mem_write(cache[group_num][line].mem_block_num,cache[group_num][line].data);
  mem_read(addr>>mem_blockaddr_bit,cache[group_num][line].data);
  cache[group_num][line].valid = 1;
	cache[group_num][line].dirty = 0;
	cache[group_num][line].tag = addr >> (mem_blockaddr_bit+cache_groupnum_bit);
	cache[group_num][line].mem_block_num = addr >> mem_blockaddr_bit;
  uint32_t* res=(void*)(cache[group_num][line].data+((addr %BLOCK_SIZE)));
  return *res;
}

void cache_write(uintptr_t addr, uint32_t data, uint32_t wmask) {
  int group_num=(addr&((1<<(cache_groupnum_bit+mem_blockaddr_bit))-1))>>mem_blockaddr_bit;
  addr&=~0x3;
  for(int i=0;i<cache_line_num;i++){
    cycle_increase(1);
    if(cache[group_num][i].valid==1 && cache[group_num][i].tag==(addr>>(mem_blockaddr_bit+cache_groupnum_bit))){
      hit++;
      uint32_t *res = (void *)(cache[group_num][i].data + ((addr%BLOCK_SIZE)));
			*res = (*res & ~wmask) | (data & wmask);
      cache[group_num][i].dirty = 1;
      return;
    }
  }
  //未命中
  miss++;
  for(int i=0;i<cache_line_num;i++){
    cycle_increase(1);
    if(cache[group_num][i].valid==0){
      //先从主存中读出来，修改后再写回
      mem_read(addr>>mem_blockaddr_bit,cache[group_num][i].data);
      uint32_t *res=(void*)(cache[group_num][i].data+((addr%BLOCK_SIZE)));
      *res=(*res&~wmask)|(data&wmask);        
      cache[group_num][i].dirty=0;
      cache[group_num][i].valid=1;
      cache[group_num][i].tag=addr>>(mem_blockaddr_bit+cache_groupnum_bit);
      cache[group_num][i].mem_block_num = addr >> mem_blockaddr_bit;
      mem_write(addr>>mem_blockaddr_bit,cache[group_num][i].data);
      return;
    }
  }
  //无空闲位
  int line=rand()%cache_line_num;
  cycle_increase(1);
  if(cache[group_num][line].dirty==1){
    mem_write(cache[group_num][line].mem_block_num,cache[group_num][line].data);
  }
  mem_read(addr>>mem_blockaddr_bit,cache[group_num][line].data);
  uint32_t *res=(void*)(cache[group_num][line].data+((addr %BLOCK_SIZE)));
  *res=(*res&~wmask)|(data&wmask);
  cache[group_num][line].valid = 1;
	cache[group_num][line].dirty = 0;
	cache[group_num][line].tag = addr >> (mem_blockaddr_bit+cache_groupnum_bit);
	cache[group_num][line].mem_block_num = addr >> mem_blockaddr_bit;
  mem_write(addr>>mem_blockaddr_bit,cache[group_num][line].data);
  return;
}

void init_cache(int total_size_width, int associativity_width) {
  assert(total_size_width==totalSizeWidth);
  assert(associativity_width==assoWidth);
  for(int i=0;i<total_size_width-BLOCK_SIZE-associativity_width;i++){
    for(int j=0;j<(1<<associativity_width);j++){
      cache[i][j].valid=0;
      cache[i][j].dirty=0;
      cache[i][i].tag=0;
      cache[i][j].mem_block_num=0;
      memset(cache[i][j].data,0,sizeof(cache[i][i].data));
    }
  }
}

void display_statistic(void) {
  printf("cycle_cnt:%ld\n",cycle_cnt);
  printf("cache size width is %d\ncache associativity width is %d\ncache block width is %d\n",totalSizeWidth,assoWidth,BLOCK_WIDTH);
  //printf("hit times:%ld\n",hit);
  //printf("miss times:%ld\n",miss);
  printf("hit rate:%f\n",(double)hit/(double)(hit+miss));
}
