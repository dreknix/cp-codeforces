#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
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

void swap(int32_t *a, int32_t *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

// from: https://www.geeksforgeeks.org/3-way-quicksort-dutch-national-flag/
// quicksort with many duplicates
void partition(int32_t a[], int l, int r, int *pi, int *pj) {
    int i = l - 1;
    int j = r;
    int p = l - 1;
    int q = r;
    int v = a[r];

    while (true) {
        // From left, find the first element greater than
        // or equal to v. This loop will definitely
        // terminate as v is last element
        while (a[++i] < v)
            ;

        // From right, find the first element smaller than
        // or equal to v
        while (v < a[--j])
            if (j == l)
                break;

        // If i and j cross, then we are done
        if (i >= j)
            break;

        // Swap, so that smaller goes on left greater goes
        // on right
        swap(&a[i], &a[j]);

        // Move all same left occurrence of pivot to
        // beginning of array and keep count using p
        if (a[i] == v) {
            p++;
            swap(&a[p], &a[i]);
        }

        // Move all same right occurrence of pivot to end of
        // array and keep count using q
        if (a[j] == v) {
            q--;
            swap(&a[j], &a[q]);
        }
    }

    // Move pivot element to its correct index
    swap(&a[i], &a[r]);

    // Move all left same occurrences from beginning
    // to adjacent to arr[i]
    j = i - 1;
    for (int k = l; k < p; k++, j--)
        swap(&a[k], &a[j]);

    // Move all right same occurrences from end
    // to adjacent to arr[i]
    i = i + 1;
    for (int k = r - 1; k > q; k--, i++)
        swap(&a[i], &a[k]);

    *pi = i;
    *pj = j;
}

// 3-way partition based quick sort
void quicksort(int a[], int l, int r) {
    if (r <= l)
        return;

    int i, j;

    partition(a, l, r, &i, &j);

    quicksort(a, l, j);
    quicksort(a, i, r);
}

#define NUMBER_OF_SORTS 100
bool issorted(int32_t a[], int n) {
    bool sorted = false;
    int step = 0;
    while (! sorted && step < NUMBER_OF_SORTS) {
        sorted = true;
        for (int i = 0; i < n - 1; i++) {
            if (a[i] > a[i+1]) {
                swap(&a[i], &a[i+1]);
                i++;
                sorted = false;
            }
        }
        step++;
    }
    return sorted;
}

// try to sort a nearly sorted array differently
// otherwise use quicksort (with possible duplicates)
void sort(int32_t a[], int n) {
    if (issorted(a, n)) {
        return;
    } else {
        quicksort(a, 0, n-1);
    }
}

int main(void) {
    int32_t n;  // 1 <= n <= 2*10^5
    int32_t k;  // 0 <= k <= n

    assert(scanf("%d %d", &n, &k) == 2);
    assert(1 <= n && n <= 2E5);
    assert(0 <= k && k <= n);
    debug("n=%d", n);
    debug("k=%d", k);

    int32_t *array = (int32_t *)malloc(n * sizeof(int32_t));

    for (int32_t i = 0; i < n; i++) {
        assert(scanf("%d", array + i) == 1);
        assert(1 <= array[i] && array[i] <= 1E9);
    }

    sort(array, n);

    int32_t result;
    if (k == 0) {
        if (array[0] == 1) {
            result = -1;
        } else {
            result = 1;
        }
    } else if (k == n) {
        result = array[n - 1];
    } else {
        if (array[k - 1] == array[k]) {
            result = -1;
        } else {
            result = array[k - 1];
        }
    }
    debug("result=%d", result);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}
