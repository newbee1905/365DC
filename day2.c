#include <stdio.h>

void collatz(int *num) {
  while (*num != 1 && *num != -1) {
    printf("%d, ", *num);
    if ((*num & 1) == 0)
      *num >>= 1;
    else
      *num = (3 * *num) + 1;
  }
  printf("%d", *num);
}

signed main() {
  int n;
  scanf("%d", &n);
  collatz(&n);
}
