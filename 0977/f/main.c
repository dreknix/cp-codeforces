#include <assert.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void debug(char *fmt, ...) {
    va_list argptr;
    fprintf(stderr, "\x1B[35mDEBUG: ");
    va_start(argptr, fmt);
    vfprintf(stderr, fmt, argptr);
    va_end(argptr);
    fprintf(stderr, "\x1B[0m\n");
}

int32_t size = 0;
int32_t array[200000];
int32_t len[200000];
int32_t back[200000];

int lis() {
  memset(back, -1, sizeof(back));
  len[0] = 1;
  for (int32_t i = 1; i < size; i++) {
    len[i] = 1;
    for (int j = 0; j < i; j++)
      if (array[i] == array[j] + 1 && len[i] < len[j] + 1) {
        len[i] = len[j] + 1;
        back[i] = j;
      }
  }

  // Return maximum value in lis[]
  int32_t max = -1;
  int32_t index = 0;
  for (int32_t i = 0; i < size; i++) {
      if (max < len[i]) {
          max = len[i];
          index = i;
      }
  }

  return index;
}

int main(void) {
    int32_t n;  // 1 <= n <= 2*10^5

    assert(scanf("%d", &n) == 1);
    assert(1 <= n && n <= 2E5);
    debug("n=%d", n);

    for (int32_t i = 0; i < n; i++) {
        int32_t value;
        assert(scanf("%d", &value) == 1);
        assert(1 <= value && value <= 1E9);
        array[i] = value;
    }
    size = n;

    int32_t index = lis();

    int32_t result = len[index];
    printf("%d\n", result);

    int32_t sequence[result];
    int32_t i = len[index] - 1;
    while (index >= 0) {
        sequence[i--] = index + 1;
        index = back[index];
    }
    for (i = 0; i < result; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}
