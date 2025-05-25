#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include "structures.h"

typedef struct SkipListNode {
    Record* record;
    struct SkipListNode** forward;
    int level;
} SkipListNode;

typedef struct SkipList {
    char virus[MAX_VIRUS];
    SkipListNode* header;
    int level;
    struct SkipList* next;
} SkipList;

SkipList* createSkipList(const char* virus);
void insertSkipList(SkipList* list, Record* record);
Record* searchSkipList(SkipList* list, int id);
void listVaccinated(SkipList* list);

#endif