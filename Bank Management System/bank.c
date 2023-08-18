#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define MAX_CUSTOMERS 100

struct Person {
    char name[50];
    char ID[20];
    char address[100];
    int contact;
    int cash;
};

struct Bank {
    int total;
    struct Person person[MAX_CUSTOMERS];
};

void perData(struct Bank *bank) {
    printf("Enter data of person %d\n", bank->total + 1);

    printf("Enter name: ");
    scanf("%s", bank->person[bank->total].name);

    printf("ID:\n ");
    scanf("%s", bank->person[bank->total].ID);

    printf("Address: \n");
    scanf("%s", bank->person[bank->total].address);

    printf("Contact:\n ");
    scanf("%d", &bank->person[bank->total].contact);

    printf("Total Cash:\n ");
    scanf("%d", &bank->person[bank->total].cash);

    bank->total++;
}

void show(struct Bank *bank) {
    for (int i = 0; i < bank->total; i++) {
        printf("Data of person %d\n", i + 1);
        printf("Name: %s\n", bank->person[i].name);
        printf("ID: %s\n", bank->person[i].ID);
        printf("Address: %s\n", bank->person[i].address);
        printf("Contact: %d\n", bank->person[i].contact);
        printf("Cash: %d\n", bank->person[i].cash);
    }
}

void update(struct Bank *bank) {
    char id[20];
    printf("Enter ID of the person whose data you want to update: \n");
    scanf("%s", id);

    for (int i = 0; i < bank->total; i++) {
        if (strcmp(id, bank->person[i].ID) == 0) {
            printf("Enter new data for person %d:\n", i + 1);
            printf("Enter name:\n ");
            scanf("%s", bank->person[i].name);

            printf("ID:\n ");
            scanf("%s", bank->person[i].ID);

            printf("Address:\n ");
            scanf("%s", bank->person[i].address);

            printf("Contact: \n");
            scanf("%d", &bank->person[i].contact);

            printf("Total Cash: \n");
            scanf("%d", &bank->person[i].cash);

            printf("Data updated successfully.\n");
            return;
        }
    }

    printf("No such record found.\n");
}

void search(struct Bank *bank) {
    char id[20];
    printf("Enter ID of the person whose data you want to search: \n");
    scanf("%s", id);

    for (int i = 0; i < bank->total; i++) {
        if (strcmp(id, bank->person[i].ID) == 0) {
            printf("Data for person %d:\n", i + 1);
            printf("Name: %s\n", bank->person[i].name);
            printf("ID: %s\n", bank->person[i].ID);
            printf("Address: %s\n", bank->person[i].address);
            printf("Contact: %d\n", bank->person[i].contact);
            printf("Cash: %d\n", bank->person[i].cash);
            return;
        }
    }

    printf("No such record found.\n");
}

void transactions(struct Bank *bank) {
    char id[20];
    int cash;
    char ch;

    printf("Enter ID of the person for transactions:\n ");
    scanf("%s", id);

    for (int i = 0; i < bank->total; i++) {
        if (strcmp(id, bank->person[i].ID) == 0) {
            printf("Name: %s\n", bank->person[i].name);
            printf("Address: %s\n", bank->person[i].address);
            printf("Contact: %d\n", bank->person[i].contact);
            printf("Existing Cash: %d\n", bank->person[i].cash);
            printf("Press 1 to deposit:\n");
			printf("Press 2 to withdraw: \n");
            ch = getch();

            switch (ch) {
                case '1':
                    printf("How much cash you want to deposit?\n ");
                    scanf("%d", &cash);
                    bank->person[i].cash += cash;
                    printf("Your new cash balance: %d\n", bank->person[i].cash);
                    return;
                case '2':
                    printf("How much cash you want to withdraw?\n ");
                    scanf("%d", &cash);
                    if (cash <= bank->person[i].cash) {
                        bank->person[i].cash -= cash;
                        printf("Your new cash balance: %d\n", bank->person[i].cash);
                    } else {
                        printf("Insufficient funds.\n");
                    }
                    return;
                default:
                    printf("Invalid input.\n");
                    return;
            }
        }
    }

    printf("No such record found.\n");
}

void del(struct Bank *bank) {
    char ch;

    printf("Press 1 to remove a specific record\n");
    printf("Press 2 to remove all records\n");
    ch = getch();

    switch (ch) {
        case '1': {
            char id[20];
            printf("Enter ID of the person whose data you want to remove:\n ");
            scanf("%s", id);

            for (int i = 0; i < bank->total; i++) {
                if (strcmp(id, bank->person[i].ID) == 0) {
                    for (int j = i; j < bank->total - 1; j++) {
                        strcpy(bank->person[j].name, bank->person[j + 1].name);
                        strcpy(bank->person[j].ID, bank->person[j + 1].ID);
                        strcpy(bank->person[j].address, bank->person[j + 1].address);
                        bank->person[j].contact = bank->person[j + 1].contact;
                        bank->person[j].cash = bank->person[j + 1].cash;
                    }
                    bank->total--;
                    printf("Record removed successfully.\n");
                    return;
                }
            }

            printf("No such record found.\n");
            break;
        }
        case '2':
            bank->total = 0;
            printf("All records removed.\n");
            break;
        default:
            printf("Invalid input.\n");
            break;
    }
}

int main() {
    struct Bank b;
    b.total = 0;

    char ch;

    while (1) {
        printf("\n\nPRESS..!!\n");
        printf("1. Create new account\n");
        printf("2. View customers list\n");
        printf("3. Update information of existing account\n");
        printf("4. Check the details of an existing account\n");
        printf("5. For transactions\n");
        printf("6. Remove existing account\n");
        printf("7. Exit\n");

        ch = getch();
        system("CLS");

        switch (ch) {
            case '1':
                perData(&b);
                break;
            case '2':
                if (b.total == 0) {
                    printf("No data is entered\n");
                } else {
                    show(&b);
                }
                break;
            case '3':
                update(&b);
                break;
            case '4':
                search(&b);
                break;
            case '5':
                transactions(&b);
                break;
            case '6':
                del(&b);
                break;
            case '7':
                exit(0);
                break;
            default:
                printf("Invalid input\n");
                break;
        }
    }

    return 0;
}

