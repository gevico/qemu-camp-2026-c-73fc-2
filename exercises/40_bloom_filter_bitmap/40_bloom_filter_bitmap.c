#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char *bits;
    size_t m;
} Bloom;

static Bloom *bloom_create(size_t m) {
    Bloom *bf = (Bloom *)malloc(sizeof(Bloom));
    if (!bf) return NULL;
    
    size_t bytes = (m + 7) / 8;
    bf->bits = (unsigned char *)calloc(bytes, sizeof(unsigned char));
    if (!bf->bits) {
        free(bf);
        return NULL;
    }
    
    bf->m = m;
    return bf;
}

static void bloom_free(Bloom *bf) {
    if (!bf) return;
    free(bf->bits);
    free(bf);
}

static void set_bit(unsigned char *bm, size_t idx) {
    size_t byte = idx / 8;
    size_t offset = idx % 8;
    bm[byte] |= (1 << offset);
}

static int test_bit(const unsigned char *bm, size_t idx) {
    size_t byte = idx / 8;
    size_t offset = idx % 8;
    return (bm[byte] >> offset) & 1;
}

static size_t hash_k(const char *s, size_t m, int k) {
    size_t hash = 0;
    while (*s) {
        hash = hash * k + (size_t)*s;
        s++;
    }
    return hash % m;
}

static void bloom_add(Bloom *bf, const char *s) {
    set_bit(bf->bits, hash_k(s, bf->m, 11));
    set_bit(bf->bits, hash_k(s, bf->m, 17));
    set_bit(bf->bits, hash_k(s, bf->m, 23));
}

static int bloom_maybe_contains(Bloom *bf, const char *s) {
    if (!test_bit(bf->bits, hash_k(s, bf->m, 11))) return 0;
    if (!test_bit(bf->bits, hash_k(s, bf->m, 17))) return 0;
    if (!test_bit(bf->bits, hash_k(s, bf->m, 23))) return 0;
    return 1;
}

int main(void) {
    const size_t m = 100;
    Bloom *bf = bloom_create(m);
    if (!bf) {
        fprintf(stderr, "bloom create failed\n");
        return 1;
    }

    bloom_add(bf, "apple");
    bloom_add(bf, "banana");

    int apple = bloom_maybe_contains(bf, "apple");
    int grape = bloom_maybe_contains(bf, "grape");

    printf("apple exists: %d\n", apple);
    printf("grape exists: %d\n", grape);

    bloom_free(bf);
    return 0;
}