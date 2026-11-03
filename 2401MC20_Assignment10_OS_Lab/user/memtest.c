#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
  char *p;

  printf("\n===== INITIAL MEMORY STATISTICS =====\n");
  memstats();

  printf("\nAllocating 3 pages using sbrk()...\n");
  p = sbrk(3 * 4096);

  if(p == (char*)-1){
    printf("Memory allocation failed\n");
    exit(1);
  }

  p[0] = 'A';
  p[4096] = 'B';
  p[8192] = 'C';

  printf("\n===== AFTER ALLOCATION =====\n");
  memstats();

  printf("\nReleasing 3 pages using sbrk()...\n");
  sbrk(-3 * 4096);

  printf("\n===== AFTER DEALLOCATION =====\n");
  memstats();

  exit(0);
}
