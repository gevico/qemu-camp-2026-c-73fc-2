#include <stdint.h>
#include <stdio.h>
#include <string.h>

#pragma pack(push, 1)

typedef struct {
    uint8_t ver_major;
    uint8_t ver_minor;
    uint16_t length_be;
    uint8_t flags_raw;
} proto_header_raw_t;

typedef struct {
    uint8_t ver_major:4;
    uint8_t ver_minor:4;
    uint16_t length;
    uint8_t reserved:3;
    uint8_t flags:5;
} proto_header_bits_t;

#pragma pack(pop)

static uint16_t be16_to_cpu(uint16_t be) {
    uint16_t le = ((be >> 8) & 0x00FF) | ((be << 8) & 0xFF00);
    return le;
}

int main(void) {
    const uint8_t stream[5] = {0x00, 0x03, 0x00, 0x20, 0x00};

    proto_header_raw_t raw = {0};
    memcpy(&raw, stream, sizeof(raw));

    proto_header_bits_t view;
    view.ver_major = raw.ver_major;
    view.ver_minor = raw.ver_minor;
    view.length = be16_to_cpu(raw.length_be);
    view.reserved = (raw.flags_raw >> 5) & 0x07;
    view.flags = raw.flags_raw & 0x1F;

    printf("version:%u.%u, length:%u, flags:0x%02X\n", view.ver_major, view.ver_minor, view.length, view.flags & 0xFFu);

    return 0;
}