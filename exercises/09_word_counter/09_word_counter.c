#include <stdio.h>

int main() {
    char str[]="Don't ask what your country can do for you, but ask what you can do for your country.";
    int wordCount = 0;
    // TODO: 在这里添加你的代码
    int i = 0;
    int inWord = 0;  
    while (str[i] != '\0') {
        if (str[i] != ' ') {
            if (!inWord) {
                wordCount++;
                inWord = 1;
            }
        } else {
            inWord = 0;
        }
        i++;
    }
    
    printf("单词数量: %d\n", wordCount);
    
    return 0;
}