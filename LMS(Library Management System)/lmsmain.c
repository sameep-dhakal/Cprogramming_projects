#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<math.h>
#include<time.h>

void addBook();
void bookList();
void removeBook();
void rentalBook();
void removeRentalRecord();
void viewRental();


FILE *fptr; //defining a file pointer globally

/*
# this structure defines a book with its details
*/

struct book
{
	int bookId;
    char bookName[50];
    char authName[20];
    char dateAdded[20];
}b;

/*
# this structure defines students with details
*/

struct student
{
    int bookID;
    char studName[50];
    char studClass[20];
    int studRoll;
    char bookName[50];
    char date[20];

};



/*
a function to show loading animation
*/


void loadingAnimation(int seconds) {
    int animationDelay = 100; // Milliseconds (0.1 second)
    int numFrames = (seconds * 1000) / animationDelay;

    for (int i = 0; i <= numFrames; i++) {
        printf("\rLoading %d%%", (i * 100) / numFrames);
        fflush(stdout);
        Sleep(animationDelay);
    }
    printf("\n");
}


/*---MAIN FUNCTION---*/

int main() {
    loadingAnimation(2); //runs the loading animation
    system("cls"); 
    printf("=============================================\n");
    printf("       Welcome to Library Management System       \n");
    printf("=============================================\n\n");
    
    while (1) {  // Infinite loop to run the program multiple times

        printf("\n1. Add Book to Library\n");
        printf("2. Display Book List of Library\n");
        printf("3. Remove Book from Library\n");
        printf("4. Register rental of new book for student\n");
        printf("5. Remove rental of book\n");
        printf("6. View the rental list\n");
        printf("7. Exit\n\n");
        
        int ch;
        printf("Enter your choice: ");
        scanf("%d", &ch);
/*
Switch case to call functions by getting the choice from the user
*/
        switch (ch) {
            case 1:
                addBook();
                break;

            case 2:
                bookList();
                break;

            case 3:
                removeBook();
                break;

            case 4:
                rentalBook();
                break;

            case 5:
                removeRentalRecord();
                break;

            case 6:
                viewRental();
                break;

            case 7:
                exit(0);

            default:
                printf("Invalid choice. Please select a valid option.\n");
                break;

        }
    }

    return 0;
}

/*---CUSTOM FUNCTIONS---*/


void addBook(){
    char temp_date[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(temp_date, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(b.dateAdded, temp_date);
/*
    # time(NULL) indicates that the current time should be returned. The return value, which is of type 
    time_t, is assigned to the variable t.
    # localtime breaks down the returned time to day,month and year structure
    # which is arranged in dd/mm/yyyy format by sprintf function
    # then it is copied to our structure member b.dateAdded whith the help of strcpy function  
*/

    fptr = fopen("books.txt", "ab");
    
    if (fptr == NULL) {
        printf("Error opening files for reading or writing.\n");
        return;
    }

/*
# reading the datails of book from the user
*/

    printf("Enter the unique id of the book: ");
    scanf("%d", &b.bookId);

    printf("Enter the book name: ");
    fflush(stdin);
    gets(b.bookName);

    printf("Enter authors name: ");
    fflush(stdin);
    gets(b.authName);

    fflush(stdin);

    printf("Book Added Successfully");
    fflush(stdin);
    fwrite(&b, sizeof(b), 1, fptr);
    fclose(fptr);
}



/*a function for dislaying the books availabe in library*/
void bookList(){
    system("cls");
    printf("---------Available Books---------\n\n");
    printf("%-30s %-30s %-30s %s\n\n", "Book id", "Book Name", "Author", "Date Added");

/*
    # here,multiple format specifiers are used to arrange the data in tabular form
    # for example, %-10s indicates left indentation with empty character field of 10
*/

    fptr = fopen("books.txt", "rb");
    
    if (fptr == NULL) {
        printf("Error opening files for reading or writing.\n");
        return;
    }
    while(fread(&b, sizeof(b), 1, fptr) == 1){
        printf("%-30d %-30s %-30s %s\n", b.bookId, b.bookName, b.authName, b.dateAdded);
    }

    fclose(fptr);
}


/*
    Function to remove the added books from the library.
*/

/*
    Removes a book record from a file containing book data.
    Working:It opens the original file for reading and a
            temporary file for writing. It reads each book record from the original file, and if the book with the 
            specified ID is found, it skips writing that record to the temporary file. 
            Once all records have been processed, it closes both files.
*/

void removeBookFromFile(int bookIdToRemove) {
    FILE *inputFile = fopen("books.txt", "rb");
    FILE *tempFile = fopen("temp.txt", "wb");

    if (inputFile == NULL || tempFile == NULL) {
        printf("Error opening files for reading or writing.\n");
        return;
    }

    struct book b;
    int bookFound = 0;  //defining a bookfound status

    while (fread(&b, sizeof(b), 1, inputFile) == 1) {
        if (b.bookId == bookIdToRemove) {
            bookFound = 1;
            continue; // Skip writing this record to the temp file (effectively deleting it)
        }
        fwrite(&b, sizeof(b), 1, tempFile);
    }

    fclose(inputFile);
    fclose(tempFile);

    if (!bookFound) {
        printf("Book with ID %d not found.\n", bookIdToRemove);
        remove("temp.txt"); // Delete the temp file
    } else {
        remove("books.txt"); // Delete the original file
        rename("temp.txt", "books.txt"); // Rename the temp file to the original name
        printf("Book with ID %d has been removed.\n", bookIdToRemove);
    }
}



void removeBook() {
    int bookIdToRemove;

    printf("Enter the book id to remove: ");
    scanf("%d", &bookIdToRemove);

    removeBookFromFile(bookIdToRemove);//calling the function and passing the book id to remove
}


/*
    A function to issue books for students and keep the books issued and their dates in the database
*/

void rentalBook() {
    struct student s;

    printf("Enter student's name: ");
    fflush(stdin);
    gets(s.studName);

    printf("Enter student's class: ");
    fflush(stdin);
    gets(s.studClass);

    printf("Enter student's roll number: ");
    scanf("%d", &s.studRoll);
    fflush(stdin);

    printf("Enter the book ID to be issued: ");
    scanf("%d", &s.bookID);

    fptr = fopen("students.txt", "ab");

    if (fptr == NULL) {
        printf("Error opening students file.\n");
        return;
    }

/*
    It searches for the book id and its name in the file where all the books available in library are added.
    If the record matches then it issues the book to the student by storing the data in a file with time.
*/  

    FILE *booksFile = fopen("books.txt", "rb");
    if (booksFile == NULL) {
        printf("Error opening books file.\n");
        fclose(fptr);
        return;
    }

    int bookFound = 0;
    while (fread(&b, sizeof(b), 1, booksFile) == 1) {
        if (b.bookId == s.bookID) {
            bookFound = 1;
            strcpy(s.bookName, b.bookName);
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            sprintf(s.date, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
            break;
        }
    }

    fclose(booksFile);

    if (bookFound) {
        fwrite(&s, sizeof(s), 1, fptr);
        printf("Book issued successfully to %s.\n", s.studName);
    } else {
        printf("Book with ID %d not found.\n", s.bookID);
    }

    fclose(fptr);
}


/*
    This is a function to remove rental/issuing of the book by a student.
    If the student returns the book then this function come in handy.
    It just checks for the data and removes the book.
    Its logic is just like removeBookFromFile() function from above.
*/

void removeRentalRecord() {
    char studentName[50];
    int bookId;

    printf("Enter student's name: ");
    fflush(stdin);
    gets(studentName);

    printf("Enter the book ID to return: ");
    scanf("%d", &bookId);

    FILE *inputFile = fopen("students.txt", "rb");
    FILE *tempFile = fopen("temp.txt", "wb");

    if (inputFile == NULL || tempFile == NULL) {
        printf("Error opening files for reading or writing.\n");
        return;
    }

    struct student s;
    int rentalFound = 0;

    while (fread(&s, sizeof(s), 1, inputFile) == 1) {
        if (strcmp(s.studName, studentName) == 0 && s.bookID == bookId) {
            rentalFound = 1;
            continue; // Skip writing this record to the temp file (effectively removing it)
        }
        fwrite(&s, sizeof(s), 1, tempFile);
    }

    fclose(inputFile);
    fclose(tempFile);

    if (!rentalFound) {
        printf("Rental record not found.\n");
        remove("temp.txt"); // Delete the temp file
    } else {
        remove("students.txt"); // Delete the original file
        rename("temp.txt", "students.txt"); // Rename the temp file to the original name
        printf("Rental record removed for student %s with book ID %d.\n", studentName, bookId);
    }
}


/*
    It displays the rented book list in a tabular form.
*/

void viewRental(){
    struct student s;
    system("cls");
    printf("---------Book Issue List---------\n\n");

    printf("%-10s %-30s %-20s %-10s %-30s %s\n\n", "Book.id", "Name", "Class", "Roll", "Book Name", "Date");

/*
    # here,multiple format specifiers are used to arrange the data in tabular form
    # for example, %-10s indicates left indentation with empty character field of 10
*/

    fptr = fopen("students.txt", "rb");

    if (fptr == NULL) {
        printf("Error opening files for reading or writing.\n");
        return;
    }


    while(fread(&s, sizeof(s), 1, fptr) == 1){
        printf("%-10d %-30s %-20s %-10d %-30s %s\n", s.bookID, s.studName, s.studClass, s.studRoll, s.bookName, s.date);
    }

    fclose(fptr);
}












