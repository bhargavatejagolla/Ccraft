#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_OVERS 2
#define MAX_BOWLERS 11

struct Player {
    char name[50];
    int runs;
    int balls;
    int fours;
    int sixes;
    int isOut;
    struct Player *prev;
    struct Player *next;
};

struct Bowler {
    char name[50];
    int runs;
    int wickets;
};

struct Team {
    char name[50];
    struct Player *head;
    int playerCount;
    int totalRuns;
    int wickets;
    float overs;
};

void removeNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

void inputTeam(struct Team *team) {
    printf("Enter team name: ");
    fgets(team->name, sizeof(team->name), stdin);
    removeNewline(team->name);

    printf("Enter number of players in %s: ", team->name);
    while (scanf("%d", &team->playerCount) != 1 || team->playerCount <= 0 || team->playerCount > 11) {
        printf("Invalid input. Please enter a number between 1 and 11: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    struct Player *tail = NULL;
    team->head = NULL;

    for (int i = 0; i < team->playerCount; i++) {
        struct Player *newPlayer = (struct Player *)malloc(sizeof(struct Player));
        printf("Enter player %d name: ", i + 1);
        fgets(newPlayer->name, sizeof(newPlayer->name), stdin);
        removeNewline(newPlayer->name);
        newPlayer->runs = 0;
        newPlayer->balls = 0;
        newPlayer->fours = 0;
        newPlayer->sixes = 0;
        newPlayer->isOut = 0;
        newPlayer->next = NULL;
        newPlayer->prev = tail;

        if (tail)
            tail->next = newPlayer;
        else
            team->head = newPlayer;

        tail = newPlayer;
    }

    team->totalRuns = 0;
    team->wickets = 0;
    team->overs = 0;
}

bool isValidBowler(char bowlerNames[MAX_BOWLERS][50], int count, char *bowlerName) {
    for (int i = 0; i < count; i++) {
        if (strcmp(bowlerNames[i], bowlerName) == 0)
            return true;
    }
    return false;
}

void printScoreboard(struct Team *team) {
    printf("\n--- %s Scoreboard ---\n", team->name);
    printf("-------------------------------------------------------------\n");
    printf("| Player       | Runs | Balls | 4s | 6s | Status    |\n");
    printf("-------------------------------------------------------------\n");
    struct Player *curr = team->head;
    while (curr) {
        printf("| %-12s | %-4d | %-5d | %-2d | %-2d | %-9s |\n",
               curr->name, curr->runs, curr->balls, curr->fours, curr->sixes,
               curr->isOut ? "Out" : "Not Out");
        curr = curr->next;
    }
    printf("-------------------------------------------------------------\n");
    printf("| TOTAL: %d /%d  in %.1f overs                        |\n", team->totalRuns, team->wickets, team->overs);
    printf("-------------------------------------------------------------\n");
}

void playInnings(struct Team *batting, char bowlerNames[MAX_BOWLERS][50], int bowlerCount, int target) {
    struct Player *striker = batting->head;
    struct Player *nonStriker = striker ? striker->next : NULL;
    struct Player *nextBatsman = nonStriker ? nonStriker->next : NULL;

    for (int over = 0; over < MAX_OVERS; over++) {
        char bowlerName[50];
        printf("\n--- Over %d ---\n", over + 1);
        while (1) {
            printf("Enter bowler name: ");
            fgets(bowlerName, sizeof(bowlerName), stdin);
            removeNewline(bowlerName);
            if (isValidBowler(bowlerNames, bowlerCount, bowlerName)) break;
            printf("Invalid bowler. Try again.\n");
        }

        for (int b = 0; b < 6;) {
            printf("Ball %d: Enter runs (0-6), -1 for out, W for wide, NB for no-ball: ", b + 1);
            char input[10];
            scanf("%s", input);
            while (getchar() != '\n');

            if (strcmp(input, "W") == 0 || strcmp(input, "w") == 0) {
                batting->totalRuns++;
                continue;
            } else if (strcmp(input, "NB") == 0 || strcmp(input, "nb") == 0) {
                int nbRuns;
                printf("No ball! Enter runs scored on no ball (excluding extra): ");
                scanf("%d", &nbRuns);
                while (getchar() != '\n');
                striker->runs += nbRuns;
                striker->balls++;
                if (nbRuns == 4) striker->fours++;
                if (nbRuns == 6) striker->sixes++;
                batting->totalRuns += nbRuns + 1;
                if (nbRuns % 2 == 1) {
                    struct Player *temp = striker;
                    striker = nonStriker;
                    nonStriker = temp;
                }
                continue;
            }

            int run;
            if (sscanf(input, "%d", &run) != 1 || run < -1 || run > 6) {
                printf("Invalid input.\n");
                continue;
            }

            if (run == -1) {
                printf("%s is out!\n", striker->name);
                striker->balls++;
                striker->isOut = 1;
                batting->wickets++;
                b++;
                if (nextBatsman) {
                    striker = nextBatsman;
                    nextBatsman = nextBatsman->next;
                } else {
                    batting->overs = over + (b / 6.0);
                    return;
                }
            } else {
                striker->runs += run;
                striker->balls++;
                if (run == 4) striker->fours++;
                if (run == 6) striker->sixes++;
                batting->totalRuns += run;
                if (run % 2 == 1) {
                    struct Player *temp = striker;
                    striker = nonStriker;
                    nonStriker = temp;
                }
                b++;
                if (target > 0 && batting->totalRuns > target) {
                    batting->overs = over + (b / 6.0);
                    return;
                }
            }
        }
    }
    batting->overs = MAX_OVERS;
}

void declareResult(struct Team *team1, struct Team *team2) {
    if (team1->totalRuns > team2->totalRuns) {
        printf("\n*\\O/* %s won the match! *\\O/*\n", team1->name);
    } else if (team2->totalRuns > team1->totalRuns) {
        printf("\n*\\O/* %s won the match! *\\O/*\n", team2->name);
    } else {
        printf("\nMatch tied! Going to Super Over!\n");
    }
}

int main() {
    struct Team team1, team2;
    char bowlers1[MAX_BOWLERS][50], bowlers2[MAX_BOWLERS][50];

    printf("========= Cricket Match Simulation =========\n\n");

    inputTeam(&team1);
    printf("\n");
    inputTeam(&team2);

    // Use all players as bowlers (simplified version as requested)
    struct Player *current = team1.head;
    for (int i = 0; i < team1.playerCount && current != NULL; i++) {
        strcpy(bowlers1[i], current->name);
        current = current->next;
    }

    current = team2.head;
    for (int i = 0; i < team2.playerCount && current != NULL; i++) {
        strcpy(bowlers2[i], current->name);
        current = current->next;
    }

    printf("\n--- First Innings (%s Batting) ---\n", team1.name);
    playInnings(&team1, bowlers2, team2.playerCount, 0);
    printScoreboard(&team1);

    printf("\nTarget for %s: %d runs\n", team2.name, team1.totalRuns + 1);
    printf("\n--- Second Innings (%s Batting) ---\n", team2.name);
    playInnings(&team2, bowlers1, team1.playerCount, team1.totalRuns);
    printScoreboard(&team2);

    declareResult(&team1, &team2);

    // Free allocated memory
    struct Player *temp;
    current = team1.head;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    current = team2.head;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
