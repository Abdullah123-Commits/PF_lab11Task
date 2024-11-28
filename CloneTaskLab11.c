#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NoOfBowlers 3
#define NoOfBatters 2
#define MaxPlayers 5

// Structures
typedef struct player {
    char name[20];
    char team[20];
} Player;

typedef struct bowl {
    char type[10];      // seamer, pacer, spinner or N/A
    char arm[5];        // left or right
    Player ply;
} Bowl;

typedef struct bat {
    char type[10];      // top order, middle order, lower order
    char handed[8];     // lefty or righty
    Bowl ply2;          // Batter who can also bowl
} Bat;

// CRUD Functions
void AddBowlerToFile(Bowl *bowlers, int *bowlersCount) {
    if (*bowlersCount >= NoOfBowlers) {
        printf("Maximum number of bowlers reached.\n");
        return;
    }
    FILE *fptr = fopen("bowler.txt", "a");
    if (fptr == NULL) {
        printf("Error in opening the bowler's data file!\n");
        return;
    }
    printf("Enter the type of bowler (seamer, pacer, spinner, N/A): ");
    scanf(" %[^\n]", bowlers[*bowlersCount].type);
    fprintf(fptr, "%s ", bowlers[*bowlersCount].type);

    printf("Enter the bowling arm of the bowler (left or right): ");
    scanf(" %[^\n]", bowlers[*bowlersCount].arm);
    fprintf(fptr, "%s ", bowlers[*bowlersCount].arm);

    printf("Enter the name of the player (bowler): ");
    scanf(" %[^\n]", bowlers[*bowlersCount].ply.name);
    fprintf(fptr, "%s ", bowlers[*bowlersCount].ply.name);

    printf("Enter the team of the bowler: ");
    scanf(" %[^\n]", bowlers[*bowlersCount].ply.team);
    fprintf(fptr, "%s\n", bowlers[*bowlersCount].ply.team);

    (*bowlersCount)++;
    fclose(fptr);
    printf("Bowler added successfully.\n");
}

void AddBatterToFile(Bat *batters, int *battersCount) {
    if (*battersCount >= NoOfBatters) {
        printf("Maximum number of batters reached.\n");
        return;
    }
    FILE *fptr = fopen("batter.txt", "a");
    if (fptr == NULL) {
        printf("Error in opening the batter's data file!\n");
        return;
    }
    printf("Enter the type of the batter (top order, middle order, lower order): ");
    scanf(" %[^\n]", batters[*battersCount].type);
    fprintf(fptr, "%s ", batters[*battersCount].type);

    printf("Enter the batting hand of the batter (lefty or righty): ");
    scanf(" %[^\n]", batters[*battersCount].handed);
    fprintf(fptr, "%s ", batters[*battersCount].handed);

    printf("Enter the type of batter who can also be used as a bowler (seamer, pacer, spinner, N/A): ");
    scanf(" %[^\n]", batters[*battersCount].ply2.type);
    fprintf(fptr, "%s ", batters[*battersCount].ply2.type);

    printf("Enter the bowling arm of the batter who can also be used as a bowler: ");
    scanf(" %[^\n]", batters[*battersCount].ply2.arm);
    fprintf(fptr, "%s ", batters[*battersCount].ply2.arm);

    printf("Enter the name of the batter (also a bowler): ");
    scanf(" %[^\n]", batters[*battersCount].ply2.ply.name);
    fprintf(fptr, "%s ", batters[*battersCount].ply2.ply.name);

    printf("Enter the team of the batter (also a bowler): ");
    scanf(" %[^\n]", batters[*battersCount].ply2.ply.team);
    fprintf(fptr, "%s\n", batters[*battersCount].ply2.ply.team);

    (*battersCount)++;
    fclose(fptr);
    printf("Batter added successfully.\n");
}

void ReadBowlersFromFile() {
    FILE *fptr = fopen("bowler.txt", "r");
    if (fptr == NULL) {
        printf("Error in opening the bowler's data file!\n");
        return;
    }
    char buffer[100];
    printf("\n--- Bowlers ---\n");
    while (fgets(buffer, sizeof(buffer), fptr)) {
        printf("%s", buffer);
    }
    fclose(fptr);
}

void ReadBattersFromFile() {
    FILE *fptr = fopen("batter.txt", "r");
    if (fptr == NULL) {
        printf("Error in opening the batter's data file!\n");
        return;
    }
    char buffer[100];
    printf("\n--- Batters ---\n");
    while (fgets(buffer, sizeof(buffer), fptr)) {
        printf("%s", buffer);
    }
    fclose(fptr);
}

void UpdateBowlerInFile(Bowl *bowlers, int *bowlersCount) {
    char nameToUpdate[20];
    printf("Enter the name of the bowler to update: ");
    scanf(" %[^\n]", nameToUpdate);

    int found = 0; // Flag to check if the bowler exists
    for (int i = 0; i < *bowlersCount; i++) {
        if (strcmp(nameToUpdate, bowlers[i].ply.name) == 0) {
            // Update bowler's details
            printf("Enter the new type of bowler (seemer, pacer, spinner): ");
            scanf(" %[^\n]", bowlers[i].type);

            printf("Enter the new bowling arm of the bowler (left or right): ");
            scanf(" %[^\n]", bowlers[i].arm);

            printf("Enter the new team of the bowler: ");
            scanf(" %[^\n]", bowlers[i].ply.team);

            found = 1; // Mark as found
            break;
        }
    }

    if (!found) {
        printf("Bowler not found in the list.\n");
        return;
    }

    // Rewrite the entire file with updated data
    FILE *fptr = fopen("bowler.txt", "w");
    if (fptr == NULL) {
        printf("Error opening the bowler's data file for updating!\n");
        return;
    }

    for (int i = 0; i < *bowlersCount; i++) {
        fprintf(fptr, "%s %s %s %s\n",
                bowlers[i].type,
                bowlers[i].arm,
                bowlers[i].ply.name,
                bowlers[i].ply.team);
    }

    fclose(fptr);
    printf("Bowler updated successfully in the file.\n");
}


void DeleteBowlerFromFile(Bowl *bowlers, int *bowlersCount) {
    char nameToDelete[20];
    printf("Enter the name of the bowler to delete: ");
    scanf(" %[^\n]", nameToDelete);

    int found = 0;
    for (int i = 0; i < *bowlersCount; i++) {
        if (strcmp(nameToDelete, bowlers[i].ply.name) == 0) {
            // Shift elements to the left to delete the record
            for (int j = i; j < *bowlersCount - 1; j++) {
                bowlers[j] = bowlers[j + 1];
            }
            (*bowlersCount)--;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Bowler not found.\n");
        return;
    }

    // Rewrite the file with remaining records
    FILE *fptr = fopen("bowler.txt", "w");
    if (fptr == NULL) {
        printf("Error in opening the bowler's data file for deletion!\n");
        return;
    }

    for (int i = 0; i < *bowlersCount; i++) {
        fprintf(fptr, "%s %s %s %s\n",
                bowlers[i].type,
                bowlers[i].arm,
                bowlers[i].ply.name,
                bowlers[i].ply.team);
    }

    fclose(fptr);
    printf("Bowler deleted successfully.\n");
}


int main() {
    Bowl bowlers[NoOfBowlers];
    Bat batters[NoOfBatters];
    int bowlersCount = 0;
    int battersCount = 0;

    int choice;
    do {
        printf("\n1. Add Bowler\n2. Add Batter\n3. Read Bowlers\n4. Read Batters\n");
        printf("5. Update Bowler\n6. Delete Bowler\n7. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                AddBowlerToFile(bowlers, &bowlersCount);
                break;
            case 2:
                AddBatterToFile(batters, &battersCount);
                break;
            case 3:
                ReadBowlersFromFile();
                break;
            case 4:
                ReadBattersFromFile();
                break;
            case 5:
                UpdateBowlerInFile(bowlers, &bowlersCount);
                break;
            case 6:
                DeleteBowlerFromFile(bowlers, &bowlersCount);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 7);

    return 0;
}
