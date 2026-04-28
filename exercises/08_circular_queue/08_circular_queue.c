#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;
    int tail;
    int count;
} Queue;

int main() {
    Queue q;
    int total_people=50;
    int report_interval=5;

    // TODO: 在这里添加你的代码
    q.head = 0;
    q.tail = 0;
    q.count = 0;

    for (int i = 1; i <= total_people; i++) {
        People p = {i};
        q.data[q.tail] = p;
        q.tail = (q.tail + 1) % MAX_PEOPLE;
        q.count++;
    }

    while (q.count > 1) {
        for (int i = 1; i < report_interval; i++) {
            People p = q.data[q.head];
            q.head = (q.head + 1) % MAX_PEOPLE;
            q.data[q.tail] = p;
            q.tail = (q.tail + 1) % MAX_PEOPLE;
        }
        People eliminated = q.data[q.head];
        printf("淘汰: %d\n", eliminated.id);
        q.head = (q.head + 1) % MAX_PEOPLE;
        q.count--;
    }

    printf("最后剩下的人是: %d\n", q.data[q.head].id);

    return 0;
}