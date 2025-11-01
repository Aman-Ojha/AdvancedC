#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void printstr(char* s){
  while(*s){
    putchar(*s++);
  }

}

void print(char *form, ...){

  va_list list;
  va_start (list, form);

  char c = *form++;
  char digs[10], *p;

  while(c){
    switch (c) {
      case 's':
        printstr(va_arg(list, char *));
        break;
      case 'c':
        putchar(va_arg(list, int));
        break;
      case 'd':
        p = digs;
        int i = va_arg (list, int);

        do {
         *p++ = (i %10) + '0';
          i /=10;

        }while (i);

        while(p>digs){
          putchar(*--p);
        }
        break;
    }
    c = *form++;
  }
  va_end(list);
}

int main(int argc, char *argv[])
{
  print("sdscs", "My neighbour had", 21, "savage and", "1", "drake\n");
  return 0;
}
