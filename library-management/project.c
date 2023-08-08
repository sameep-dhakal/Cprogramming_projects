#include <stdio.h>
#include <string.h>

#define max 100

struct Book {
    char title[30];
    char author[30];
    char publisher[30];
    int year;
    int quantity;
};

void add_book(struct Book book[max]) {
    int n;
    printf("How many books you want to add: ");
    scanf("%d", &n);
    getchar();
    FILE *fptr;
    fptr = fopen("File.txt", "a");
    if (fptr == NULL) {
        printf("Error opening the file!\n");
    }

    printf("Enter book details:\n");
    for (int i = 0; i < n; i++) {
        printf("Title : ");
        fgets(book[i].title,30,stdin);
        printf("Author : ");
        fgets(book[i].author,30,stdin);
        printf("Publisher : ");
        fgets(book[i].publisher,30,stdin);
        printf("Year : ");
        scanf("%d", &book[i].year);
        printf("Quantity : ");
        scanf("%d", &book[i].quantity);
        getchar();
        fprintf(fptr, "%s%s%s%d\n%d", book[i].title, book[i].author, book[i].publisher, book[i].year, book[i].quantity);
    }

    fclose(fptr);
}

void display_books() {
    FILE *fptr;
    struct Book book;

    fptr = fopen("File.txt", "r");
    if (fptr == NULL) {
        printf("Error opening the file!\n");
        return;
    }

    printf("\nBook Details:\n");
    printf("Title\tAuthor\tPublisher\tYear\tQuantity\n");
    while ((fscanf(fptr, "%s%s%s%d\n%d", book.title, book.author, book.publisher, &book.year, &book.quantity)) != EOF) {
        printf("%s\t%s\t%s\t\t%d\t\t%d\n", book.title, book.author, book.publisher, book.year, book.quantity);
    }
    fclose(fptr);
}

void search_book() {
    char title[30];
    int a=0;
    printf("Enter title of the book to search: ");
    scanf("%s", title);

    FILE *fptr;
    fptr = fopen("File.txt", "r");
    if (fptr == NULL) {
        printf("Error opening the file!\n");
        return;
    }
    struct Book book;
    while ((fscanf(fptr, "%s%s%s%d%d", book.title, book.author, book.publisher, &book.year, &book.quantity)) != EOF) {
        if (strcmp(book.title, title) == 0) {
            printf("\nBook found!\n");
            printf("Title: %s\nAuthor: %s\nPublisher: %s\nYear: %d\nQuantity: %d\n", book.title, book.author, book.publisher, book.year, book.quantity);
           a=1;
            break;
        }
        }
    if (a==0)
    {
       printf("\nBook not found!\n");
    }
    
 fclose(fptr);
}

int main() {
    struct Book book[max]; 
    printf("Welcome to the Book Collection Management System!\n");
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Add a book\n");
        printf("2. Display all books\n");
        printf("3. Search for a book by title\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add_book(book);
                break;
            case 2:
                display_books();
                break;
            case 3:
                search_book();
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
