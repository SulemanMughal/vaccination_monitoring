#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include "structures.h"

typedef struct BloomFilter {
    char virus[MAX_VIRUS];
    uint8_t* bitArray;
    struct BloomFilter* next;
} BloomFilter;

BloomFilter* createBloomFilter(const char* virus);
// BloomFilter* createBloomFilter(int size); // Accepts size instead

void insertBloomFilter(BloomFilter* bf, int citizenID);
int queryBloomFilter(BloomFilter* bf, int citizenID);
unsigned int hash_i(int key, int i);
int checkBloomFilter(BloomFilter* bloom, int id);


#endif