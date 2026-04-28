#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

#define DEBUG

#ifdef DEBUG

#define DEBUG_PRINT(fmt, ...) \
    do { \
        printf("DEBUG: func=%s, line=%d, " fmt "\n", __func__, __LINE__, ##__VA_ARGS__); \
    } while (0)

#else

#define DEBUG_PRINT(fmt, ...) do {} while (0)

#endif

// Line 19

// Line 21

// Line 23

// Line 25

// Line 27

// Line 29

// Line 31

// Line 33

// Line 35

// Line 37

// Line 39

// Line 41

// Line 43

void test() {
    int x = 42;
    DEBUG_PRINT("x=%d", x);
}

int main() {
    test();
    return 0;
}