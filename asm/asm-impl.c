#include "asm.h"
#include <string.h>
#include <stdio.h>
int64_t asm_add(int64_t a, int64_t b) {
  // TODO: implement
  asm("add %1,%0;":"+r"(a):"r"(b));
  return a;
}

int asm_popcnt(uint64_t n) {
  // TODO: implement
  int x=0;
  asm("xor %%rax,%%rax\n"
      "mov %%rsp,%%rbp\n" 
      "movl $0x0,-0x4(%%rbp)\n"
      "mov %1,-0x18(%%rbp)\n"
      "jmp L1\n"
      "L0:mov -0x18(%%rbp),%%rax\n"
      "and $0x1,%%eax\n"
      "mov %%eax,%%edx\n"
      "mov -0x4(%%rbp),%%eax\n"
      "add %%edx,%%eax\n"
      "mov %%eax,-0x4(%%rbp)\n"
      "shrq -0x18(%%rbp)\n"
      "L1:cmpq $0x0,-0x18(%%rbp)\n"
      "jne L0\n"
      "mov -0x4(%%rbp),%0\n"
      :"=r"(x)  
      :"r"(n)  
      :"%eax","%edx","rax","cc","memory"
  );
  return x;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
  // TODO: implement
  int a, b, c;  
  asm volatile(  
  "rep ; movsl\n"
  "test $0x2,%4\n"
  "je L2\n"
  "movsw\n"
  "L2:test $0x1,%4\n"
  "je L3\n"
  "movsb\n"
  "L3:\n"
  :"=&c"(a),"=&D"(b),"=&S"(c)
  :"0"(n/4),"q"(n),"1"((long)dest),"2"((long)src)
  : "memory"
  );
  return dest;
}

int asm_setjmp(asm_jmp_buf env) {
  // TODO: implement
  return 0;
}

void asm_longjmp(asm_jmp_buf env, int val) {
  // TODO: implement
}
