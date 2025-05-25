#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "skip_list.h"

static float randomFloat() {
    return (float)rand() / RAND_MAX;
}

static int randomLevel() {
    int level = 1;
    while (randomFloat() < PROBABILITY && level < MAX_LEVEL)
        level++;
    return level;
}

SkipList* createSkipList(const char* virus) {
    SkipList* list = malloc(sizeof(SkipList));
    strncpy(list->virus, virus, MAX_VIRUS);
    list->level = 1;
    list->header = malloc(sizeof(SkipListNode));
    list->header->record = NULL;
    list->header->forward = malloc(MAX_LEVEL * sizeof(SkipListNode*));
    for (int i = 0; i < MAX_LEVEL; i++)
        list->header->forward[i] = NULL;
    list->next = NULL;
    return list;
}

void insertSkipList(SkipList* list, Record* record) {
    SkipListNode* update[MAX_LEVEL];
    SkipListNode* x = list->header;

    for (int i = list->level - 1; i >= 0; i--) {
        while (x->forward[i] && x->forward[i]->record->citizen.id < record->citizen.id) {
            x = x->forward[i];
        }
        update[i] = x;
    }

    x = x->forward[0];
    if (x && x->record->citizen.id == record->citizen.id) {
        // Already exists, do not insert duplicate
        return;
    }

    int newLevel = randomLevel();
    if (newLevel > list->level) {
        for (int i = list->level; i < newLevel; i++) {
            update[i] = list->header;
        }
        list->level = newLevel;
    }

    SkipListNode* newNode = malloc(sizeof(SkipListNode));
    newNode->record = record;
    newNode->level = newLevel;
    newNode->forward = malloc(newLevel * sizeof(SkipListNode*));

    for (int i = 0; i < newLevel; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
}

Record* searchSkipList(SkipList* list, int id) {
    SkipListNode* x = list->header;
    for (int i = list->level - 1; i >= 0; i--) {
        while (x->forward[i] && x->forward[i]->record->citizen.id < id) {
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    if (x && x->record->citizen.id == id) {
        return x->record;
    }
    return NULL;
}

void listVaccinated(SkipList* list) {
    SkipListNode* current = list->header->forward[0];
    while (current) {
        printf("%d %s %s %s %d %s %s %s\n",
               current->record->citizen.id,
               current->record->citizen.firstName,
               current->record->citizen.lastName,
               current->record->citizen.country,
               current->record->citizen.age,
               current->record->virusName,
               current->record->vaccinated ? "YES" : "NO",
               current->record->vaccinated ? current->record->date : "");
        current = current->forward[0];
    }
}
