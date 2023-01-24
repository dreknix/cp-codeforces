#include <assert.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void debug(char *fmt, ...) {
    va_list argptr;
    fprintf(stderr, "\x1B[35mDEBUG: ");
    va_start(argptr, fmt);
    vfprintf(stderr, fmt, argptr);
    va_end(argptr);
    fprintf(stderr, "\x1B[0m\n");
}

int main(void) {
    int32_t n;  // 2 <= n <= 10^9
    int8_t  k;  // 1 <= k <= 50

    assert(scanf("%d %hhd", &n, &k) == 2);
    assert(2 <= n && n <= 1E9);
    assert(1 <= k && k <= 50);
    debug("n=%d k=%hhd", n, k);

    for (int i = 0; i < k; i++) {
        if (n % 10 != 0) {
            n--;
        } else {
            n = n / 10;
        }
    }
    printf("%d\n", n);

    return EXIT_SUCCESS;
}
