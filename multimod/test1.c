#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int64_t multimod_p1(int64_t a, int64_t b, int64_t m) {
  int64_t r=0;
  for(int i=0;i<b;i++){
    r+=a;
    if(r>m) r%=m;
  }
  return r;
}
int64_t multimod_p2(int64_t a, int64_t b, int64_t m) {
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
int64_t multimod_p3(int64_t a, int64_t b, int64_t m) {
  int64_t t = (a * b - (int64_t)((double)a * b / m) * m) % m;
  return t < 0 ? t + m : t;
}
int64_t myatoi(char *p){
  int64_t res=0;
  while(*p!='\0'){
    res=res*10+(*p++-'0');
    if(*p=='\r') break;
  }
  return res;
}
int main(){
  
  FILE *fp=fopen("./data2.txt","r");
  //FILE *fp=fopen("./data.txt","r");
  char buf[100];
  int begin,end;
  double t1=0,t2=0,t3=0;
  while(fgets(buf,sizeof(buf),fp)){
    char *p=strtok(buf," ");
    int64_t a=myatoi(p);
    p=strtok(NULL," ");
    int64_t b=myatoi(p);
    p=strtok(NULL," ");
    int64_t m=myatoi(p);
    p=strtok(NULL,"\n");
    int64_t res=myatoi(p);
    //printf("%ld,%ld,%ld,%ld\n",a,b,m,res);
    //测试p1
    begin=clock();
    int64_t res1=multimod_p1(a,b,m);
    end=clock();
    t1+=end-begin;
    //测试p2
    begin=clock();
    int64_t res2=multimod_p2(a,b,m);
    end=clock();
    t2+=end-begin;
    //测试p3
    
    begin=clock();
    int64_t res3=multimod_p3(a,b,m);
    end=clock();
    t3+=end-begin;
    //int64_t res1=res2;
    //int64_t res3=res2; 
    if(res1!=res || res2 !=res || res3!=res){
      printf("res1 is %ld,res2 is %ld,res3 is %ld\n,res is %ld.\n",res1,res2,res3,res);
      assert(0);
    }
  }
  fclose(fp);
  t1/=CLOCKS_PER_SEC;
  t2/=CLOCKS_PER_SEC;
  t3/=CLOCKS_PER_SEC;
  printf("time1 is %f seconds,time2 is %f seconds,time3 is %f seconds\n",t1,t2,t3);
  return 0;
}