#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
  char *p;
  uint64 pa;
  uint64 invalid = 0x40000000;

  printf("\n===== VIRTUAL TO PHYSICAL ADDRESS TEST =====\n");

  p = sbrk(4096);
  if(p == (char*)-1){
    printf("Memory allocation failed\n");
    exit(1);
  }

  p[0] = 'A';

  printf("Allocated virtual address: %p\n", (void*)p);

  pa = vtop((uint64)p);
  if(pa != 0)
    printf("Translated physical address: %p\n", (void*)pa);
  else
    printf("Translation failed\n");

  pa = vtop((uint64)p + 100);
  printf("Address with offset 100: %p\n", (void*)pa);

  printf("\n===== INVALID ADDRESS TEST =====\n");
  pa = vtop(invalid);

  if(pa == 0)
    printf("Invalid/unmapped address correctly rejected.\n");
  else
    printf("Unexpected physical address: %p\n", (void*)pa);

  exit(0);
}
