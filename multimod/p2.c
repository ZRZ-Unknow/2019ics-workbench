#include "multimod.h"


int64_t multimod_p2(int64_t a, int64_t b, int64_t m) {
  // TODO: implement
  int64_t r=0;
  uint64_t byte=0x1;
  uint64_t temp[63];
  for(int i=0;i<63;i++){
    if(i==0){
      temp[i]=b%m;
      continue;
    }
    temp[i]=(((uint64_t)temp[i-1])<<1)%m;
  }
  for(int i=0;i<63;i++){
    if(byte&a) r=(r+temp[i])%m;
    byte<<=1;
  }
  return r;
}
