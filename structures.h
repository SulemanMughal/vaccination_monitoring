#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_NAME 50
#define MAX_VIRUS 30
#define BLOOM_SIZE 10000
#define HASH_FUNCTIONS 3
#define MAX_LEVEL 5
#define PROBABILITY 0.5

#include <stdint.h>

typedef struct Citizen {
    int id;
    char firstName[MAX_NAME];
    char lastName[MAX_NAME];
    char country[MAX_NAME];
    int age;
} Citizen;

typedef struct Record {
    Citizen citizen;
    char virusName[MAX_VIRUS];
    int vaccinated;
    char date[15];
} Record;

#endif