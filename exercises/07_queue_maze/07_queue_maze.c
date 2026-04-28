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

typedef struct {
    int row;
    int col;
} Position;

Position queue[100];
int front = 0, rear = 0;

int visited[MAX_ROW][MAX_COL] = {0};
Position parent[MAX_ROW][MAX_COL];

void enqueue(int row, int col) {
    queue[rear].row = row;
    queue[rear].col = col;
    rear++;
}

void dequeue(void) {
    front++;
}

int is_empty(void) {
    return front == rear;
}

Position get_front(void) {
    return queue[front];
}

int bfs(int start_row, int start_col, int end_row, int end_col) {
    enqueue(start_row, start_col);
    visited[start_row][start_col] = 1;
    parent[start_row][start_col].row = -1;
    parent[start_row][start_col].col = -1;

    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while (!is_empty()) {
        Position curr = get_front();
        dequeue();

        if (curr.row == end_row && curr.col == end_col) {
            return 1;
        }

        for (int i = 0; i < 4; i++) {
            int new_row = curr.row + directions[i][0];
            int new_col = curr.col + directions[i][1];

            if (new_row >= 0 && new_row < MAX_ROW && new_col >= 0 && new_col < MAX_COL &&
                maze[new_row][new_col] == 0 && !visited[new_row][new_col]) {
                enqueue(new_row, new_col);
                visited[new_row][new_col] = 1;
                parent[new_row][new_col].row = curr.row;
                parent[new_row][new_col].col = curr.col;

                if (new_row == end_row && new_col == end_col) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

void print_path(int end_row, int end_col) {
    int row = end_row;
    int col = end_col;

    while (row != -1 && col != -1) {
        printf("(%d, %d)\n", row, col);
        Position p = parent[row][col];
        row = p.row;
        col = p.col;
    }
}

int main(void)
{
    if (!bfs(0, 0, MAX_ROW - 1, MAX_COL - 1)) {
        printf("No path!\n");
    } else {
        print_path(MAX_ROW - 1, MAX_COL - 1);
    }

	return 0;
}