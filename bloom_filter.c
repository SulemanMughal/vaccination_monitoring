#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "bloom_filter.h"

unsigned int hash_i(int key, int i) {
    return (key * (i + 1) + i * i) % BLOOM_SIZE;
}

BloomFilter* createBloomFilter(const char* virus) {
    BloomFilter* bf = malloc(sizeof(BloomFilter));
    if (!bf) {
        perror("malloc");
        exit(1);
    }

    strncpy(bf->virus, virus, MAX_VIRUS - 1);
    bf->virus[MAX_VIRUS - 1] = '\0'; // Ensure null-termination

    bf->bitArray = calloc(BLOOM_SIZE, sizeof(uint8_t));
    if (!bf->bitArray) {
        perror("calloc");
        free(bf);
        exit(1);
    }

    bf->next = NULL;
    return bf;
}


void insertBloomFilter(BloomFilter* bf, int citizenID) {
    for (int i = 0; i < HASH_FUNCTIONS; i++) {
        unsigned int index = hash_i(citizenID, i);
        bf->bitArray[index] = 1;
    }
}

int queryBloomFilter(BloomFilter* bf, int citizenID) {
    for (int i = 0; i < HASH_FUNCTIONS; i++) {
        unsigned int index = hash_i(citizenID, i);
        if (bf->bitArray[index] == 0)
            return 0; // definitely not in set
    }
    return 1; // possibly in set
}



// Function to check if the ID exists in the Bloom Filter
int checkBloomFilter(BloomFilter* bloom, int id) {
    if (!bloom) {
        return 0; // Return false if the Bloom filter is null
    }

    // Hash the ID and calculate the corresponding bit positions (you can use a hashing method)
    unsigned int hash1 = id % BLOOM_SIZE;
    unsigned int hash2 = (id / BLOOM_SIZE) % BLOOM_SIZE;

    // Check if the bits at both positions are set to 1
    if (bloom->bitArray[hash1] && bloom->bitArray[hash2]) {
        return 1;  // ID might exist in the filter (false positive is possible)
    }

    return 0;  // ID does not exist in the filter
}