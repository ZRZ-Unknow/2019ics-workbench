#include "perf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdint.h>

#define DECL(fn) void fn();
#define gen_rand a=rand();\
    b=rand();\
    m=rand();\
    FILE *fp=fopen("./multimod_num.txt","a");\
    fprintf(fp,"%ld %ld %ld\n",a,b,m);\
    fclose(fp);

PROGRAMS(DECL)
extern int64_t a;
extern int64_t b;
extern int64_t m;

static void run(void (*func)(), int rounds);
static double gettime();
static void (*lookup(const char *fn))();
static char fn[15];
int main(int argc, char **argv) {
  // TODO: parse arguments: set @func and @rounds
  /*printf("%d\n",argc);
  for(int i=0;i<argc;i++){
    printf("%s\n",argv[i]);
  }*/
  int rounds=1;
  for(int i=0;i<argc;i++){
    if(strcmp(argv[i],"perf")==0){
      i++;
      if(strcmp(argv[i],"-r")==0){
        i+=1;
        rounds=atoi(argv[i]);
        i+=1;
        strcpy(fn,argv[i]);
        break;
      }
      else{
        strcpy(fn,argv[i]);
        break;
      }
    }
  } 
  void (*func)() = lookup(fn);
  run(func, rounds);
  return 0;
}

static double gettime() {
  // TODO: implement me!
  uint64_t t=clock();
  return ((double)t)/CLOCKS_PER_SEC;
}

static void (*lookup(const char *fn))() {
  #define PAIR(fn) { #fn, fn },
;
  struct pair {
    const char *name;
    void *ptr;
  };
  struct pair lut[] = {
    PROGRAMS(PAIR)
  };

  for (int i = 0; i < LENGTH(lut); i++) {
    struct pair *p = &lut[i];
    if (strcmp(fn, p->name) == 0) return p->ptr;
  }
  return print_error;
}

static void run(void (*func)(), int rounds) {
  double *elapsed = malloc(sizeof(uint64_t) * rounds);
  if (!elapsed) {
    perror("elapsed");
    return;
  }
  for (int round = 0; round < rounds; round++) {
    if(strcmp(fn,"multimod_p1")==0||strcmp(fn,"multimod_p2")==0 || strcmp(fn,"multimod_p3")==0){
      gen_rand;
    }
    double st = gettime();
    func();
    double ed = gettime();
    elapsed[round] = ed - st;
  }
  
  // TODO: display runtime statistics
  //将数据写入data.txt文件
  FILE *fp=fopen("./data.txt","w+");
  fprintf(fp,"%s\n",fn);
  for(int i=0;i<rounds;i++){
    fprintf(fp,"%f ",elapsed[i]);
  }
  fclose(fp);
  //使用shell运行test.py文件来
  const char cmdstr[20]="python3 test.py";
  system(cmdstr);
  free(elapsed);
}
