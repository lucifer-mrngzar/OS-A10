#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
  char *p;
  int pid;

  printf("\n===== PAGE TABLE INSPECTION TEST =====\n");

  p = sbrk(4096);
  if(p == (char*)-1){
    printf("Memory allocation failed\n");
    exit(1);
  }

  p[0] = 'A';

  printf("\nBefore removing write permission:\n");
  pageinfo((uint64)p);

  printf("\nSetting page to read-only...\n");
  if(setreadonly((uint64)p) < 0){
    printf("setreadonly failed\n");
    exit(1);
  }

  printf("\nAfter removing write permission:\n");
  pageinfo((uint64)p);

  printf("\n===== WRITE PROTECTION TEST =====\n");

  pid = fork();
  if(pid < 0){
    printf("Fork failed\n");
    exit(1);
  }

  if(pid == 0){
    printf("Child attempting to write to read-only page...\n");
    p[0] = 'B';
    printf("ERROR: Write unexpectedly succeeded!\n");
    exit(1);
  }

  wait(0);
  printf("Parent survived the child's expected page fault.\n");

  exit(0);
}
