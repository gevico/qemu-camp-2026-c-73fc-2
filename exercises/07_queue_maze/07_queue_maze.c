#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

// 方向数组：上、下、左、右
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

typedef struct {
    int row;
    int col;
} Point;

typedef struct {
    Point data[MAX_ROW * MAX_COL];
    int head;
    int tail;
} Queue;

void initQueue(Queue *q) {
    q->head = 0;
    q->tail = 0;
}

int isEmpty(Queue *q) {
    return q->head == q->tail;
}

void enqueue(Queue *q, Point p) {
    q->data[q->tail++] = p;
}

Point dequeue(Queue *q) {
    return q->data[q->head++];
}

int main(void)
{
	// TODO: 在这里添加你的代码
	// I AM NOT DONE
    Point start = {0, 0};
    Point end   = {4, 4};

    int visited[MAX_ROW][MAX_COL] = {0};
    Point prev[MAX_ROW][MAX_COL];

    // 初始化 prev 为无效值
    for (int i = 0; i < MAX_ROW; i++)
        for (int j = 0; j < MAX_COL; j++)
            prev[i][j] = (Point){-1, -1};

    Queue q;
    initQueue(&q);

    enqueue(&q, start);
    visited[start.row][start.col] = 1;
    prev[start.row][start.col] = (Point){-1, -1};   // 起点前驱无效

    while (!isEmpty(&q)) {
        Point cur = dequeue(&q);

        if (cur.row == end.row && cur.col == end.col)
            break;

        for (int i = 0; i < 4; i++) {
            int nr = cur.row + dr[i];
            int nc = cur.col + dc[i];
            if (nr >= 0 && nr < MAX_ROW && nc >= 0 && nc < MAX_COL &&
                maze[nr][nc] == 0 && !visited[nr][nc]) {
                visited[nr][nc] = 1;
                prev[nr][nc] = cur;
                enqueue(&q, (Point){nr, nc});
            }
        }
    }

    // 回溯路径
    Point path[MAX_ROW * MAX_COL];
    int len = 0;
    Point cur = end;
    while (cur.row != -1 && cur.col != -1) {
        path[len++] = cur;
        cur = prev[cur.row][cur.col];
    }

    // 输出路径（从起点到终点）
    for (int i = len - 1; i >= 0; i--) {
        printf("(%d,%d)", path[i].row, path[i].col);
        if (i > 0) printf("->");
    }
    printf("\n");
	return 0;
}