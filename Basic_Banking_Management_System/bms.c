#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BORDER_WIDTH 15
#define MAX_ACCOUNTS 50

// Function prototypes
void clearInputBuffer();
void clearScreen();
void printWelcomeMessage();
void printHorizontalLine();
void printSideBorders(const char *text);
int generateRandomAccountNumber();
void balanceEnquiry(float balance);
void depositAmount(float *balance);
void withdrawAmount(float *balance);
void transferAmount(float *balance);

int main() {
    // Initialization
    clearScreen();
    float balance = 0;
    char name[50];
    int hasAccount = 0;
    int transaction = 1;
    int accountNumber = 0;
    int numAccounts = 0;
    int accounts[MAX_ACCOUNTS];
    char names[MAX_ACCOUNTS][50];
    float balances[MAX_ACCOUNTS];

// Welcome message and account check
    printWelcomeMessage();
    printSideBorders("WELCOME TO Himal BANK");
    printf("\nDo you have an account with Himal Bank?\n");
    printf("1. Yes\n2. No\n");
    printHorizontalLine();
    int answer;
    scanf("%d", &answer);
    clearInputBuffer();

    if (answer == 1) {
        // Existing account handling
        printHorizontalLine();
        printf("Please enter your account no.: ");
        scanf("%d", &accountNumber);
        printHorizontalLine();

        if (accountNumber <= 0) {
            printf("Invalid input. Please enter a valid account number.\n");
            return 0;
        }

        FILE *accountFile = fopen("accounts.txt", "r");
        int accountFound = 0;
        for (int i = 0; i < numAccounts; i++) {
            if (accountNumber == accounts[i]) {
                hasAccount = 1;
                balance = balances[i];
                accountFound = 1;

                printf("Account found!\n");
                printf("Account Number: %d\n", accounts[i]);
                printf("Name: %s\n", names[i]);
                printf("Balance: %.2f Rs\n", balance);
                break;
            }
        }
        fclose(accountFile);

        if (!accountFound) {
            printHorizontalLine();
            printf("Account details not found in this bank.\n");
            int openAccountChoice;
            do {
                printHorizontalLine();
                printf("Do you want to open an account in this bank?\n");
                printf("1. Yes\n2. No\n");
                printHorizontalLine();

                scanf("%d", &openAccountChoice);
                clearInputBuffer();

                if (openAccountChoice == 1) {
                    printHorizontalLine();
                    printf("Enter your full name: ");
                    scanf(" %49[^\n]", name);
                    printHorizontalLine();
                    clearInputBuffer();

                    do {
                        printHorizontalLine();
                        printf("Enter initial deposit amount: ");
                        if (scanf("%f", &balance) != 1) {
                            printf("Invalid input. Please enter a valid amount.\n");
                            clearInputBuffer();
                            continue;
                        }
                        if (balance < 0) {
                            printf("Invalid initial deposit amount. Please enter a non-negative amount.\n");
                            continue;
                        }
                        break;
                    } while (1);

                    hasAccount = 1;
                    accountNumber = generateRandomAccountNumber();
                    printHorizontalLine();
                    printf("Your account number is: %d\n", accountNumber);
                    FILE *newAccountFile = fopen("accounts.txt", "a");
                    if (newAccountFile != NULL) {
                        fprintf(newAccountFile, "%d %s %.2f\n", accountNumber, name, balance);
                        fclose(newAccountFile);
                    } else {
                        printf("Error: Account database not found.\n");
                        return 0;
                    }
                    break;
                } else if (openAccountChoice == 2) {
                    printHorizontalLine();
                    printf("Thank you for considering Himal BANKING SYSTEM. If you change your mind, you are welcome to open an account anytime.\n");
                    printf("Press any key to continue...");
                    getchar();
                    return 0;
                } else {
                    printf("Invalid choice. Please select 1 or 2.\n");
                }
            } while (1);
        }
    } else if (answer == 2) {
        // New account handling
        printHorizontalLine();
        printf("Do you want to open an account in this bank?\n");
        printf("1. Yes\n2. No\n");
        printHorizontalLine();
        scanf("%d", &answer);
        clearInputBuffer();

        if (answer == 1) {
            printHorizontalLine();
            printf("Enter your full name: ");
            scanf(" %49[^\n]", name);
            printHorizontalLine();
            clearInputBuffer();

            do {
                printf("Enter initial deposit amount: ");
                if (scanf("%f", &balance) != 1) {
                    printf("Invalid input. Please enter a valid amount.\n");
                    clearInputBuffer();
                    continue;
                }
                if (balance < 0) {
                    printf("Invalid initial deposit amount. Please enter a non-negative amount.\n");
                    continue;
                }
                break;
            } while (1);

            hasAccount = 1;
            accountNumber = generateRandomAccountNumber();
            printf("Your account number is: %d\n", accountNumber);
            FILE *newAccountFile = fopen("accounts.txt", "a");
            if (newAccountFile != NULL) {
                fprintf(newAccountFile, "%d %s %.2f\n", accountNumber, name, balance);
                fclose(newAccountFile);
            } else {
                printf("Error: Account database not found.\n");
                return 0;
            }
        } else if (answer == 2) {
            printf("Thank you for considering Himal BANKING SYSTEM. If you change your mind, you are welcome to open an account anytime.\n");
            printf("Press any key to continue...");
            getchar();
            return 0;
        } else {
            printf("Invalid choice.\n");
            return 0;
        }
    } else {
        printf("Invalid choice.\n");
        return 0;
    }

    // Transaction loop
    while (transaction == 1) {
        int option;

        // Menu and user choice
        printHorizontalLine();
        printf("\nChoose what you want to do:\n");
        printf("1 - Balance Enquiry\n");
        printf("2 - Deposit\n");
        printf("3 - Withdraw\n");
        printf("4 - Transfer\n");
        printHorizontalLine();
        scanf("%d", &option);
        clearInputBuffer();

        switch (option) {
            case 1:
                // Balance Enquiry
                if (hasAccount) {
                    balanceEnquiry(balance);
                } else {
                    printf("Account not found.\n");
                }
                break;
            case 2:
                // Deposit
                if (hasAccount) {
                    depositAmount(&balance);
                } else {
                    printf("Account not found.\n");
                }
                break;
            case 3:
                // Withdraw
                if (hasAccount) {
                    withdrawAmount(&balance);
                } else {
                    printf("Account not found.\n");
                }
                break;
            case 4:
                // Transfer
                if (hasAccount) {
                    transferAmount(&balance);
                } else {
                    printf("Account not found.\n");
                }
                break;
            default:
                // Invalid option handling
                printf("Invalid option\n");
                break;
        }

        int choice;
        do {
            // Perform another action choice
            printHorizontalLine();
            printf("Do you want to perform another action?\n");
            printf("1. Yes 2. No\n");
            printHorizontalLine();
            scanf("%d", &choice);
            clearInputBuffer();
            if (choice != 1 && choice != 2) {
                printf("Invalid choice. Choose between 1 and 2 only.\n");
            }
        } while (choice != 1 && choice != 2);
        if (choice == 2) {
            transaction = 0;
        }
    }

    // Print final details
    printf("\n\t\t\t    -----------------------");
    printf("\n\t\t\t\tHimal BANK LIMITED\n");
    printf("\t\t\t    -----------------------\n\n");
    printf("\t\t\t Date: %s\t   Time: %s\n", __DATE__, __TIME__);
    printf("\n\t\t\t Your name: %s\n\n", name);

    if (accountNumber > 0) {
        printf("\t\t\t Your account number: %d\n\n", accountNumber);
    } else if (hasAccount) {
        printf("\t\t\t You have an account\n\n");
    }

    printSideBorders("Thank you for using Himal BANKING SYSTEM.");
    printHorizontalLine();

    getch();
    return 0;
}


// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


// Function to clear the console screen
void clearScreen() {
    system("cls");
}


// Function to print the welcome message
void printWelcomeMessage() {
    // Welcome message formatting
    printf("\n");
    printf("*****************************************************\n");
    printf("*                                                   *\n");
    printf("*               HIMAL BANKING SYSTEM                *\n");
    printf("*                                                   *\n");
    printf("*                   ACEM Branch                     *\n");
    printf("*                 Kathmandu, Nepal                  *\n");
    printf("*                                                   *\n");
    printf("*****************************************************\n");
    printf("\n");
}


// Function to print a horizontal line
void printHorizontalLine() {
    printf("-----------------------------------------------------\n");
}


// Function to print side borders with text
void printSideBorders(const char *text) {
    // Side borders formatting
    int length = strlen(text);
    int totalWidth = BORDER_WIDTH + length + BORDER_WIDTH;

    for (int i = 0; i < totalWidth; i++) {
        if (i < BORDER_WIDTH || i >= totalWidth - BORDER_WIDTH) {
            printf("*");
        } else if (i == BORDER_WIDTH) {
            printf(" %s ", text);
        }
    }
    printf("\n");
}


// Function to generate a random account number
int generateRandomAccountNumber() {
    srand(time(NULL));
    return rand() % 9000 + 1000;
}


// Function to perform a balance enquiry
void balanceEnquiry(float balance) {
    // Balance enquiry output
    printf("\t\t\t*BALANCE ENQUIRY*\n\n");
    printf("Your current balance is: %.2f Rs\n", balance);
}


// Function to perform a deposit
void depositAmount(float *balance) {
    // Deposit input and processing
    printf("\n\t\t\t*DEPOSIT AMOUNT*\n\n");
    float dep;
    printf("How much money do you want to deposit: ");
    scanf("%f", &dep);
    if (dep > 0 && dep <= 20000) {
        printf("\n%.2f Rs has been deposited into your account.\n\n", dep);
        *balance += dep;
    } else if (dep > 20000) {
        printf("\nYou can't deposit that much amount at once.\n\n");
    } else {
        printf("\nInvalid deposit amount\n");
    }
}


// Function to perform a withdrawal
void withdrawAmount(float *balance) {
    // Withdrawal input and processing
    printf("\n\t\t*WITHDRAW AMOUNT*\n\n");
    float draw;
    printf("How much money do you want to withdraw: ");
    scanf("%f", &draw);

    float maxWithdrawal = 20000;

    if (draw <= *balance && draw <= maxWithdrawal) {
        printf("\nYou have withdrawn %.2f Rs.\n\n", draw);
        *balance -= draw;
    } else if (draw > maxWithdrawal) {
        printf("\nYou can only withdraw up to %.2f Rs at once.\n\n", maxWithdrawal);
    } else {
        printf("\nInsufficient funds\n\n");
    }
}


// Function to perform a fund transfer
void transferAmount(float *balance) {
    // Transfer input and processing
    printf("\t\t\tTRANSFER AMOUNT\n\n");
    int account2;
    float transfer;
    printf("Enter the account number you want to transfer to: ");
    scanf("%d", &account2);
    printf("Enter the amount you want to transfer: ");
    scanf("%f", &transfer);
    if (*balance >= transfer) {
        printf("\n%.2f Rs has been successfully transferred to account %d.\n\n", transfer, account2);
        *balance -= transfer;
    } else {
        printf("\nInsufficient balance for the transfer.\n\n");
    }
}
