#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

void merge(int arr[], int left[], int left_size, int right[], int right_size) {
    int i = 0, j = 0, k = 0;

    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    while (i < left_size) {
        arr[k++] = left[i++];
    }

    while (j < right_size) {
        arr[k++] = right[j++];
    }
}

void parallel_merge_sort(int arr[], int n) {
    if (n <= 1) {
        return;
    }

    int mid = n / 2;

    int* left = (int*)malloc(mid * sizeof(int));
    int* right = (int*)malloc((n - mid) * sizeof(int));

    // Copy elements to left and right arrays
    memcpy(left, arr, mid * sizeof(int));
    memcpy(right, arr + mid, (n - mid) * sizeof(int));

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            parallel_merge_sort(left, mid);
        }

        #pragma omp section
        {
            parallel_merge_sort(right, n - mid);
        }
    }

    merge(arr, left, mid, right, n - mid);

    free(left);
    free(right);
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    parallel_merge_sort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}

