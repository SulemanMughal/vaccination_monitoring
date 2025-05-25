#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "records.h"

#define DATE_LEN 11 // Assuming date format "YYYY-MM-DD" + null terminator
#include "bloom_filter.h"
#include "skip_list.h"

#define BLOOM_FILTER_SIZE 1024 // Define an appropriate size for the bloom filter
#include "structures.h"

#define BUFFER_SIZE 256

VirusData* viruses = NULL;

static VirusData* getOrCreateVirus(const char* name) {
    VirusData* curr = viruses;
    while (curr) {
        if (strcmp(curr->name, name) == 0)
            return curr;
        curr = curr->next;
    }

    VirusData* newVirus = malloc(sizeof(VirusData));
    strncpy(newVirus->name, name, MAX_VIRUS);
    // newVirus->bloom = createBloomFilter(BLOOM_FILTER_SIZE); // Pass the required argument(s)
    newVirus->bloom = createBloomFilter(newVirus->name);

    newVirus->list = createSkipList(name);
    newVirus->next = viruses;
    viruses = newVirus;
    return newVirus;
}

VirusData* loadRecords(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, file)) {
        Record* r = malloc(sizeof(Record));
        char vaccinatedStr[4], dateBuffer[DATE_LEN] = "";

        sscanf(buffer, "%d %s %s %s %d %s %s %[0-9-/]",
               &r->citizen.id,
               r->citizen.firstName,
               r->citizen.lastName,
               r->citizen.country,
               &r->citizen.age,
               r->virusName,
               vaccinatedStr,
               dateBuffer);

        r->vaccinated = strcmp(vaccinatedStr, "YES") == 0;
        if (r->vaccinated) {
            strncpy(r->date, dateBuffer, DATE_LEN);
        } else {
            strcpy(r->date, "");
        }

        VirusData* virus = getOrCreateVirus(r->virusName);
        if (r->vaccinated) {
            insertBloomFilter(virus->bloom, r->citizen.id);
            insertSkipList(virus->list, r);
        }
    }

    fclose(file);

    return NULL; // Return NULL or an appropriate default value

}

void checkVaccinationStatus(int id, const char* virusName) {
    VirusData* v = viruses;
    while (v) {
        if (strcmp(v->name, virusName) == 0)
            break;
        v = v->next;
    }
    if (!v) {
        printf("Virus not found.\n");
        return;
    }

    // if (!checkBloomFilter(v->bloom, id)) {
    //     printf("%d NOT VACCINATED\n", id);
    //     return;
    // }

    Record* record = searchSkipList(v->list, id);
    if (record && record->vaccinated) {
        printf("%d VACCINATED ON %s\n", id, record->date);
    } else {
        printf("%d NOT VACCINATED\n", id);
    }
}

void listVirusVaccinated(const char* virusName) {
    VirusData* v = viruses;
    while (v) {
        if (strcmp(v->name, virusName) == 0) {
            listVaccinated(v->list);
            return;
        }
        v = v->next;
    }
    printf("Virus not found.\n");
}




void insertVaccinationRecord(int citizenID, const char* firstName, const char* lastName, const char* virusName, const char* vaccinationStatus, const char* vaccinationDate) {
    if (strcmp(vaccinationStatus, "YES") == 0) {
        // Retrieve the VirusData for the given virus name
        VirusData* virus = getOrCreateVirus(virusName);

        // Create a new Record for the citizen
        Record* record = malloc(sizeof(Record));
        record->citizen.id = citizenID;
        strncpy(record->citizen.firstName, firstName, sizeof(record->citizen.firstName) - 1);
        strncpy(record->citizen.lastName, lastName, sizeof(record->citizen.lastName) - 1);
        strncpy(record->date, vaccinationDate, DATE_LEN - 1);
        record->vaccinated = 1;

        // Insert into the Skip List
        insertSkipList(virus->list, record);

        // Insert into the Bloom Filter
        insertBloomFilter(virus->bloom, citizenID);
    }
}