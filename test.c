#include <string.h>
#include <stdio.h>
#include <unistd.h>

char happy[] = { 0xe2, 0x98, 0xba };  /* U+263A */

int main()
{
   write(1, happy, 4);
   return 0;
}
