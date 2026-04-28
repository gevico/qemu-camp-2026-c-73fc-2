#include <stdio.h>
#include <stdlib.h>

void josephus_problem(int n, int k, int m) {
    if (n <= 0 || k <= 0 || m <= 0) {
        printf("参数错误：n, k, m 都必须大于 0\n");
        return;
    }

    int* people = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        people[i] = i + 1;
    }

    int count = n;
    int current = k - 1;

    while (count > 0) {
        current = (current + m - 1) % count;
        printf("%d ", people[current]);

        for (int i = current; i < count - 1; i++) {
            people[i] = people[i + 1];
        }
        count--;
    }

    free(people);
    printf("\n");
}

int main(void) {
    josephus_problem(5, 1, 2);
    josephus_problem(7, 3, 1);
    josephus_problem(9, 1, 8);

    return 0;
}