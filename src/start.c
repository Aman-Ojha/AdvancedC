#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

int sum (int n, ...){

  va_list list;

  va_start(list, n);
  int tot=0;

  while(n--){
    tot+=va_arg(list, int);

  }
  va_end(list);
  return tot;
}
int main(int argc, char *argv[])
{
  printf("%d\n", sum(0));
  printf("%d\n", sum(3,1,2,3));
  return EXIT_SUCCESS;
}
