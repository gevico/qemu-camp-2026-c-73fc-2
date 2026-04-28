#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int score;
} Student;

Student students[MAX_STUDENTS];
Student temp[MAX_STUDENTS];

void merge_sort(int left, int right) {
    // TODO: 在这里添加你的代码
    if(left == right) {
        return ;
    }
    int mid = (left + right) >> 1;
    merge_sort(left, mid);
    merge_sort(mid + 1, right);
    for(int i = left; i <= mid; ++i) {
        temp[i] = students[i];
    }
    int k = left;
    for(int i = left, j = mid + 1; i <= mid; ) {
        if(right < j || students[j].score <= temp[i].score ) {
            students[k++] = temp[i++]; 
        }
        if(i <=  mid && temp[i].score < students[j].score ) {
            students[k++] = students[j++];
        }
    }

}

int main(void) {
    FILE *file = fopen("02_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 02_students.txt\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("学生人数无效：%d\n", n);
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d", students[i].name, &students[i].score);
    }
    fclose(file);

    merge_sort(0, n - 1);

    printf("\n归并排序后按成绩从高到低排序的学生名单：\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }

    return 0;
}