#include <assert.h>
#include <inttypes.h>
#include <stdarg.h>
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
    fprintf(stderr, "\x1B[0m");
}

int main(void) {
    int8_t n;  // 2 <= n <= 100
    char   str[101];

    int8_t counter[26][26];

    assert(scanf("%hhd", &n) == 1);
    assert(2 <= n && n <= 100);
    debug("n=%hhd\n", n);

    assert(scanf("%s",str) == 1);
    assert(strlen(str) == n);
    debug("str=[%s]\n", str);

    memset(counter, 0, sizeof(counter));
    for (int8_t i = 0; i < n - 1; i++) {
        counter[(int)(str[i] - 'A')]
               [(int)(str[i + 1] - 'A')]++;
    }

    int8_t max = 0;
    char   twogram[3];
    twogram[0] = '-';
    twogram[1] = '-';
    twogram[2] = '\0';
    for (int8_t x = 0; x < 26; x++) {
        for (int8_t y = 0; y < 26; y++) {
            if (counter[x][y] > max) {
                max = counter[x][y];
                twogram[0] = 'A' + x;
                twogram[1] = 'A' + y;
            }
        }
    }
    debug("max=%hhd\n", max);
    printf("%s\n", twogram);

    return EXIT_SUCCESS;
}
