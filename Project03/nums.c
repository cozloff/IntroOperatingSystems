#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
  int i, ret;

  printf("Random Numbers:");
  for(i = 0; i < 100; i++) {
    if (i % 10 == 0) {
      printf("\n");
    }
    ret = (int) srand() % 100;  // Calling the srand system call
    printf("%d  ", ret);
  }

  printf("\n$ ");
  exit(0);
}
