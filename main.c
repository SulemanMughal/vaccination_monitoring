#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "records.h"
#include "bloom_filter.h" // Include the header for bloom filter functions


void printMenu() {
    printf("\nCommands:\n");
    printf("/vaccineStatus <citizenID> <virusName>\n");
    printf("/insertRecord <citizenID> <firstName> <lastName> <country> <age> <virusName> <YES/NO> [date] - Insert a new record\n");
    printf("/listVaccinated <virusName>\n");
    printf("/exit\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s inputRecords.txt\n", argv[0]);
        return 1;
    }

    loadRecords(argv[1]);

    char command[100], virusName[50];
    int id;

    printMenu();
    while (1) {
        printf("> ");
        fgets(command, sizeof(command), stdin);

        if (strncmp(command, "/vaccineStatus", 14) == 0) {
            if (sscanf(command + 14, "%d %s", &id, virusName) == 2) {
                checkVaccinationStatus(id, virusName);
            } else {
                printf("Invalid usage. Format: /vaccineStatus <citizenID> <virusName>\n");
            }
        } else if (strncmp(command, "/listVaccinated", 15) == 0) {
            if (sscanf(command + 15, "%s", virusName) == 1) {
                listVirusVaccinated(virusName);
            } else {
                printf("Invalid usage. Format: /listVaccinated <virusName>\n");
            }

        
        } 
        
        else if (strncmp(command, "/insertRecord", 13) == 0) {
            int id;
            char firstName[50], lastName[50], virusName[50], vaccinationStatus[5], vaccinationDate[20];
            if (sscanf(command + 13, "%d %s %s %s %s %s", &id, firstName, lastName, virusName, vaccinationStatus, vaccinationDate) == 6) {
                insertVaccinationRecord(id, firstName, lastName, virusName, vaccinationStatus, vaccinationDate);
                printf("Vaccination record inserted for %s %s\n", firstName, lastName);
            } else {
                printf("Invalid usage. Format: /insertRecord <citizenID> <firstName> <lastName> <virusName> <vaccinationStatus> [vaccinationDate]\n");
            }
        }
        else if (strncmp(command, "/exit", 5) == 0) {
            printf("Exiting program.\n");
            break;
        } else {
            printf("Unknown command.\n");
            printMenu();
        }
    }

    return 0;
}
