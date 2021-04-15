#include <stdio.h>

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

int main(void) {
  char i1[4] = {0,0,0,64};
  char i2[4] = {64,0,0,0};
  char i3[4] = {0,0,0,0};
  printf("%f\n", ptr2float(i1));
  printf("%f\n", ptr2float(i2));
  printf("%f\n", ptr2float(i3));
}
