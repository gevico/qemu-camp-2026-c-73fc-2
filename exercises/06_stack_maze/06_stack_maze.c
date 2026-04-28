#include <stdio.h>
#include <stdlib.h>

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

Position stack[100];
int top = -1;

int visited[MAX_ROW][MAX_COL] = {0};

void push(int row, int col) {
    stack[++top].row = row;
    stack[top].col = col;
}

void pop(void) {
    top--;
}

int is_empty(void) {
    return top == -1;
}

Position get_top(void) {
    return stack[top];
}

int dfs(int row, int col) {
    if (row < 0 || row >= MAX_ROW || col < 0 || col >= MAX_COL || maze[row][col] == 1 || visited[row][col]) {
        return 0;
    }

    push(row, col);
    visited[row][col] = 1;

    if (row == MAX_ROW - 1 && col == MAX_COL - 1) {
        return 1;
    }

    if (dfs(row - 1, col) || dfs(row, col + 1) || dfs(row + 1, col) || dfs(row, col - 1)) {
        return 1;
    }

    pop();
    return 0;
}

int main(void)
{
    if (!dfs(0, 0)) {
        printf("No path!\n");
    }

    while (!is_empty()) {
        Position pos = get_top();
        printf("(%d, %d)\n", pos.row, pos.col);
        pop();
    }

	return 0;
}