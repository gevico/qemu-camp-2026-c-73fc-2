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



struct Direct {
	int x, y;
} dir[4] =  {{1, 0},{0, 1},{-1, 0},{0, -1} };
struct Position {
	int x, y;
	int direct;
}  stack[MAX_COL * MAX_ROW];
int visited[MAX_ROW][MAX_COL] = {0};
int main(void)
{
	// TODO: 在这里添加你的代码
	// I AM NOT DONE
    int top = 0;                     // 栈顶索引
    int found = 0;                   // 是否找到终点
    int goal_x = MAX_ROW - 1, goal_y = MAX_COL - 1;  // 终点 (4,4)

    // 起点入栈
    stack[top].x = 0;
    stack[top].y = 0;
    stack[top].direct = 0;
    visited[0][0] = 1;

    while (top >= 0 && !found) {
        int cur_x = stack[top].x;
        int cur_y = stack[top].y;

        if (cur_x == goal_x && cur_y == goal_y) {
            found = 1;
            break;
        }

        int next_dir = -1;
        for (int i = stack[top].direct; i < 4; ++i) {
            int nx = cur_x + dir[i].x;
            int ny = cur_y + dir[i].y;
            if (nx >= 0 && nx < MAX_ROW && ny >= 0 && ny < MAX_COL &&
                maze[nx][ny] == 0 && !visited[nx][ny]) {
                next_dir = i;
                break;
            }
        }

        if (next_dir != -1) {
            stack[top].direct = next_dir + 1;
            top++;
            stack[top].x = cur_x + dir[next_dir].x;
            stack[top].y = cur_y + dir[next_dir].y;
            stack[top].direct = 0;
            visited[stack[top].x][stack[top].y] = 1;
        } else {
            top--;
        }
    }

    if (found) {
        for (int i = top; i >= 0; i--) {
            printf("(%d, %d)", stack[i].x, stack[i].y);
			if (i > 0) printf("->");
        }
		printf("%d\n",top);
    } else {
        printf("no path！\n");
    }
	return 0;
}