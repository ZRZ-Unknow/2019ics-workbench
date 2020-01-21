#include "perf.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t a;
int64_t b;
int64_t m;

void multimod_p1() {
  int64_t r=0;
  for(int i=0;i<b;i++){
    r+=a;
    if(r>m) r%=m;
  }
}
void multimod_p2() {
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
}
void multimod_p3(){
  int64_t t = (a * b - (int64_t)((double)a * b / m) * m) % m;
  int64_t res= t<0?(t+m):t;
  res--;
}
void dummy() {
}

void print_hello() {
  printf("hello\n");
}

void print_error() {
  printf("invalid subject!\n");
  exit(1);
}

void simple_loop() {
  for (volatile int i = 0; i < 1000000; i++) ;
}

