#include <stdio.h>
#include <stdlib.h>
#include "inversion-counter.h"


void
print_arr (int *arr, int arrlen)
{
    printf("%d", arr[0]);
    for (int i = 1; i < arrlen; i++)
        printf(", %d", arr[i]);
    printf("\n");
}

void
merge_and_count (int *subarr1, int subarr1_len, int *subarr2, int subarr2_len,
                 int *arr, long int *inversions)
{
    for (int i = 0, i1 = 0, i2 = 0; i1 < subarr1_len || i2 < subarr2_len; i++) {
        if (i1 < subarr1_len && i2 < subarr2_len) {
            if (subarr1[i1] <= subarr2[i2]) {
                arr[i] = subarr1[i1++];
            }
            else {
                arr[i] = subarr2[i2++];
                *inversions = *inversions + (subarr1_len - i1);
            }
        }
        else if (i1 < subarr1_len) {
            arr[i] = subarr1[i1++];
        }
        else if (i2 < subarr2_len)
            arr[i] = subarr2[i2++];
    }
}

int *
inversion_counter (int *arr, int arrlen, long int *inversions)
{
    if (arrlen <= 1)
        return arr;

    int middle = arrlen / 2;
    int *left = arr;
    int *right = arr + middle;

    left = inversion_counter(left, middle, inversions);
    right = inversion_counter(right, arrlen - middle, inversions);

    /* copy subarrays into local arrays for merge */
    int l[middle];
    int r[arrlen - middle];
    for (int i = 0; i < middle; i++, left++)
        l[i] = *left;
    for (int i = 0; i < arrlen - middle; i++, right++)
        r[i] = *right;

    merge_and_count(l, middle, r, arrlen - middle, arr, inversions);
    return arr;
}
