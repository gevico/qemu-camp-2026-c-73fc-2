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
} dir[4] =  {{0, 1},{1, 0},{0, -1},{-1, 0} };
struct Position {
	int x, y;
	int direct;
}  stack[MAX_COL * MAX_ROW];

int main(void)
{
	// TODO: 在这里添加你的代码
    // I AM NOT DONE
	int idx = 0;
	int find = 0;
	stack[idx].x = 0;
	stack[idx].y = 0;
	stack[idx].direct = 0;
	
	while(-1 < idx  && ! find) {
		maze[stack[idx].x][stack[idx].y] = 1;
		find = 0;
		for(int i = stack[idx].direct; i < 4; ++i) {
			stack[idx + 1].x = stack[idx].x + dir[i].x;
			stack[idx + 1].y = stack[idx].y + dir[i].y;
			stack[idx].direct = i + 1;
			if(maze[stack[idx + 1].x][stack[idx + 1].y] == 0) {
				find = 1;
				break;
			}
		}
		if(find == 1) {
			idx++;
		} else {
			idx--;
		}
		
	}
	return 0;
}