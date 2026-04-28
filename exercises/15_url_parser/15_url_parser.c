#include <stdio.h>
#include <string.h>

int parse_url(const char* url) {
    const char *qmark = strchr(url, '?');
    if (!qmark) return 0;

    const char *p = qmark + 1;
    const char *end = url + strlen(url);

    while (p < end && *p) {
        // 跳过前导 '&'
        while (p < end && *p == '&') p++;
        if (p >= end || *p == '#') break;

        // 提取 key
        const char *key_start = p;
        while (p < end && *p != '=' && *p != '&') p++;
        const char *key_end = p;

        // 提取 value
        const char *value_start = p;
        const char *value_end = p;
        if (p < end && *p == '=') {
            p++;
            value_start = p;
            while (p < end && *p != '&') p++;
            value_end = p;
        }

        // 输出格式：key = xxx, value = yyy
        printf("key = %.*s, value = %.*s\n",
               (int)(key_end - key_start), key_start,
               (int)(value_end - value_start), value_start);

        // 如果当前字符是 '&'，跳过继续
        if (p < end && *p == '&') p++;
    }
    return 0;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";
    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");
    parse_url(test_url);
    return 0;
}