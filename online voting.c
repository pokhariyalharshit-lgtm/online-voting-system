#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_VOTES 100

// Structure to store voter details
struct Voter {
    char voterID[20];
    char password[20];
    int hasVoted;        
    char votedFor[50];   
};

// Global array to store all registered voters
struct Voter voters[MAX_USERS];
int voterCount = 0;

// Function to check if voter ID already exists (duplicate check)
int voterIDExists(char id[]) {
    for (int i = 0; i < voterCount; i++) {
        if (strcmp(voters[i].voterID, id) == 0)
            return 1; // found duplicate
    }
    return 0;
}

// Function to register a new voter
void registerVoter() {
    char id[20], pass[20];

    printf("\n---- VOTER REGISTRATION ----\n");
    printf("Enter Voter ID Number: ");
    scanf("%s", id);

    // Check for duplicate voter ID
    if (voterIDExists(id)) {
        printf("This Voter ID already exists. Registration failed.\n");
        return;
    }

    printf("Enter Password: ");
    scanf("%s", pass);

    // Save details
    strcpy(voters[voterCount].voterID, id);
    strcpy(voters[voterCount].password, pass);
    voters[voterCount].hasVoted = 0; 
    strcpy(voters[voterCount].votedFor, ""); 

    voterCount++;

    printf(" Registration Successful!\n");
}

// Function for login
int login() {
    char id[20], pass[20];

    printf("\n---- LOGIN ----\n");
    printf("Enter Voter ID: ");
    scanf("%s", id);
    printf("Enter Password: ");
    scanf("%s", pass);

    for (int i = 0; i < voterCount; i++) {
        if (strcmp(voters[i].voterID, id) == 0 &&
            strcmp(voters[i].password, pass) == 0) {
            printf(" Login Successful!\n");
            return i; 
        }
    }

    printf(" Wrong Voter ID or Password.\n");
    return -1;
}

// Function to show party list + vote
void castVote(int userIndex) {
    int choice;

    if (voters[userIndex].hasVoted) {
        printf(" You have already voted! You voted for: %s\n", voters[userIndex].votedFor);
        return;
    }

    printf("\n---- CAST YOUR VOTE ----\n");
    printf("1. BJP\n");
    printf("2. Congress\n");
    printf("3. AAP\n");
    printf("4. CPI\n");
    printf("5. Independent Candidate\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: strcpy(voters[userIndex].votedFor, "BJP"); break;
        case 2: strcpy(voters[userIndex].votedFor, "Congress"); break;
        case 3: strcpy(voters[userIndex].votedFor, "AAP"); break;
        case 4: strcpy(voters[userIndex].votedFor, "CPI"); break;
        case 5: strcpy(voters[userIndex].votedFor, "Independent"); break;
        default:
            printf("Invalid choice.\n");
            return;
    }

    voters[userIndex].hasVoted = 1;
    printf("You have successfully voted \n");
}

// Function to check whom user voted for
void checkYourVote(int userIndex) {
    if (userIndex == -1) {
        printf(" You must login first.\n");
        return;
    }

    if (voters[userIndex].hasVoted)
        printf(" You voted for: %s\n", voters[userIndex].votedFor);
    else
        printf(" You have not voted yet.\n");
}

int main() {
    int age;
    int choice;
    int loggedInUser = -1;

    // Step 1: Ask AGE first
    printf("Enter your age: ");
    scanf("%d", &age);

    if (age < 18) {
        printf(" You are under 18. You cannot vote.\n");
        return 0;
    }

    // Age 18+ → Show Menu
    while (1) {
        printf("\n---- ONLINE VOTING SYSTEM ----\n");
        printf("1. Register\n");
        printf("2. Login & Cast Vote\n");
        printf("3. Check Whom You Voted For\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerVoter();
                break;

            case 2:
                loggedInUser = login();
                if (loggedInUser != -1)
                    castVote(loggedInUser);
                break;

            case 3:
                checkYourVote(loggedInUser);
                break;
          case 4:
                printf("Thank you for using the Online Voting System.\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

