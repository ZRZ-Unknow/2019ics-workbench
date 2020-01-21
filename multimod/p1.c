#include "multimod.h"


int64_t multimod_p1(int64_t a, int64_t b, int64_t m) {
  // TODO: implement
  int64_t r=0;
  for(int i=0;i<b;i++){
    r+=a;
    if(r>m) r%=m;
  }
  return r;
}
