#ifndef RECORDS_H
#define RECORDS_H

#include "structures.h"
#include "bloom_filter.h"
#include "skip_list.h"

typedef struct VirusData {
    char name[MAX_VIRUS];
    BloomFilter* bloom;
    SkipList* list;
    struct VirusData* next;
} VirusData;

VirusData* loadRecords(const char* filename);
VirusData* getVirusData(VirusData* head, const char* virus);
void checkVaccinationStatus(int id, const char* virus);
void listVirusVaccinated(const char* virus);
void handleCommands(VirusData* virusList);
void insertVaccinationRecord(int citizenID, const char* firstName, const char* lastName, const char* virusName, const char* vaccinationStatus, const char* vaccinationDate) ;

#endif




// void loadRecords(const char* filename);


