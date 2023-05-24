#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_SIZE 100

int main() {
    int n, i;
    int arr[MAX_SIZE];
    int min_val, max_val, sum_val;
    float avg_val;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    min_val = arr[0];
    max_val = arr[0];
    sum_val = 0;

    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val) reduction(+:sum_val)
    for (i = 0; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }

        if (arr[i] > max_val) {
            max_val = arr[i];
        }

        sum_val += arr[i];
    }

    avg_val = (float)sum_val / n;

    printf("Minimum value: %d\n", min_val);
    printf("Maximum value: %d\n", max_val);
    printf("Sum: %d\n", sum_val);
    printf("Average: %.2f\n", avg_val);

    return 0;
}

