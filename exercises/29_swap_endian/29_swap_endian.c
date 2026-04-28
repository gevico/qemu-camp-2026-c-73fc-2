#include <stdint.h>
#include <stdio.h>

uint32_t swap_endian(uint32_t num) {
    uint32_t result = 0;
    result |= (num >> 24) & 0x000000FF;
    result |= (num >> 8) & 0x0000FF00;
    result |= (num << 8) & 0x00FF0000;
    result |= (num << 24) & 0xFF000000;
    return result;
}

int main(int argc, char* argv[]) {
    uint32_t num = 0x78563412;
    uint32_t swapped = swap_endian(num);
    printf("0x%08x -> 0x%08x\n", num, swapped);
    return 0;
}