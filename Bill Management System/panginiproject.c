#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define MAX_ITEMS 100

struct Item {
    char name[50];
    int quantity;
    float price;
};

struct Bill {
    struct Item items[MAX_ITEMS];
    int itemCount;
    float totalAmount;
};

int main() {
    struct Bill bill;
    bill.itemCount = 0;
    bill.totalAmount = 0.0;

    int n;
    printf("Billing System\n");
    printf("1. Create Bill\n2. Display Bill\n3. Exit\n");

    do {
        printf("Enter choice: ");
        scanf("%d", &n);

        switch (n) {
            case 1: {
                char choice = 'y';
                while (choice != 'n' && choice != 'N') {
                    if (bill.itemCount >= MAX_ITEMS) {
                        printf("Maximum number of items reached.\n");
                        break;
                    }

                    printf("\nEnter item name: ");
                    scanf("%s", bill.items[bill.itemCount].name);

                    printf("Enter quantity: ");
                    scanf("%d", &bill.items[bill.itemCount].quantity);

                    printf("Enter price: ");
                    scanf("%f", &bill.items[bill.itemCount].price);

                    bill.totalAmount += bill.items[bill.itemCount].quantity * bill.items[bill.itemCount].price;

                    (bill.itemCount)++;

                    printf("\nDo you want to add more items? (y/n): ");
                    choice = getch();
                    printf("\n");
                }
                break;
            }
            case 2: {
                if (bill.itemCount == 0) {
                    printf("No items in the bill.\n");
                    break;
                }

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Set text color to yellow

                printf("\n======= BILL =======\n");
                printf("%-20s %10s %10s %10s\n", "Item", "Quantity", "Price", "Total");
                printf("--------------------------------------------\n");

                int i = 0; // Declare the loop variable outside the loop
                while (i < bill.itemCount) {
                    printf("%-20s %10d %10.2f %10.2f\n", bill.items[i].name, bill.items[i].quantity, bill.items[i].price, bill.items[i].quantity * bill.items[i].price);
                    i++;
                }

                printf("--------------------------------------------\n");
                printf("%-20s %10s %10s %10.2f\n", "Total Amount:", "", "", bill.totalAmount);

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Reset text color to white
                break;
            }
            case 3:
                printf("Thank you.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (n != 3);

    return 0;
}