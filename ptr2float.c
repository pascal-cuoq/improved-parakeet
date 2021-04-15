#include <stdio.h>

#ifdef OLD_VERSION
float ptr2float(const char* p) {
  float r;
  char* rp=(char*)&r;

  const char data[]={0,0,0,64};
  if(2.0f==*(float*)data) {
    for(int i=0;i<sizeof r;i++) rp[i]=p[i];
  }else{
    for(int i=0;i<sizeof r;i++) rp[sizeof(r)-i-1]=p[i];
  }

  return r;
}
#else
float ptr2float(const char* p) {
  _Static_assert(sizeof (float) == 4, "float must be represented with 4 chars");
  union { char repr[4]; float f; } u = {0,0,0,64};

  if(2.0f == u.f) {
    for(int i=0;i<sizeof u;i++) u.repr[i]=p[i];
  }else{
    for(int i=0;i<sizeof u;i++) u.repr[sizeof(u)-i-1]=p[i];
  }

  return u.f;
}
#endif

int main(void) {
  char i1[4] = {0,0,0,64};
  char i2[4] = {64,0,0,0};
  char i3[4] = {0,0,0,0};
  printf("%.16e\n", ptr2float(i1));
  printf("%.16e\n", ptr2float(i2));
  printf("%.16e\n", ptr2float(i3));
}
