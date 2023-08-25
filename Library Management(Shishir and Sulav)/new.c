#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#define AvailableBooks "AvailableBooks.txt"
#define BooksLended "lenders.txt"
#define BooksLendedWithoutNames "lendersWithoutName.txt"


// To add current time
char* times(void)
{
	struct tm* ptr;
	time_t t;
	t = time(NULL);
	ptr = localtime(&t);
	return asctime(ptr);
}


// Making files for books which are lended
int lendFileWithoutName(char tmp[100])
{
    FILE *lend;
    lend = fopen(BooksLendedWithoutNames, "a");
    if(lend == NULL)
    {
        printf("Error");
        return 0;
    }
    fprintf(lend, "%s\n", tmp);
    fflush(lend);
    fclose(lend);
}

// Making a file function for writing to lend.
int lendfiles(char tmp[100], char name[100])
{  
    FILE *fptr;
    fptr = fopen(BooksLended, "a");
    if (fptr == NULL)
    {
        printf("Error");
        return 0;
    }
    fprintf(fptr, "%s taken by %s on %s", tmp, name, times());
    fflush(fptr);
    fclose(fptr);
    return 0;

}

// Write to AvailableBooks.txt file
int writeToAvailableBooks(char bookID[10], char bookName[50])
{
    FILE *fptr;
    fptr = fopen(AvailableBooks, "a");
    if (fptr == NULL)
    {
        printf("Error!");
    }
    fprintf(fptr, "%s %s \n", bookID, bookName);
    fflush(fptr);
    fclose(fptr);
}

// Remove contents from lenders.txt files
int removeFromLenders(char bookID[10])
{
    char id[10];
    char temp[100];
    FILE *tempLenders;
    FILE *tempLendersWithoutName;
    FILE *lenders;
    FILE *lendersWN;

    lenders = fopen(BooksLended, "r");
    lendersWN = fopen(BooksLendedWithoutNames, "r");

    tempLenders = fopen("temp_lenders.txt", "a");
    tempLendersWithoutName = fopen("temp_lendersWithoutName.txt", "a");

    if (tempLenders == NULL || tempLendersWithoutName == NULL || lenders == NULL || lendersWN == NULL)
    {
        printf("Error Opening File!");
        return 0;
    }
    while (fgets(temp, sizeof(temp), lenders) != NULL)
    {
        
        sscanf(temp, "%s", id); // It is used to store a string before any whitespace to variable id.
        if (strcmp(id, bookID) != 0)
        {
            fputs(temp, tempLenders);
            fflush(tempLenders);
        }
        
    }
    for (int i = 0; temp[i] != '\0'; i++)
    {
        temp[i] = '\0';
    }
    
    while (fgets(temp, sizeof(temp), lendersWN))
    {
        sscanf(temp, "%s", id);
        if (strcmp(id, bookID) != 0)
        {
            fputs(temp, tempLendersWithoutName);
            fflush(tempLendersWithoutName);
        }
        
    }

    fclose(lenders);
    fclose(tempLenders);
    remove(BooksLended);
    rename("temp_lenders.txt", BooksLended);

    fclose(tempLendersWithoutName);
    fclose(lendersWN);
    remove(BooksLendedWithoutNames);
    rename("temp_lendersWithoutName.txt", BooksLendedWithoutNames);

    return 0;
}


// Function to write all the returned books and time to a file.
int returnfiles(char bookID[10], char bookName[50])
{
        FILE *returns;
        returns = fopen("returned.txt", "a");
        if (returns == NULL)
        {
            printf("Error returning book ");
            return 0;
        }
        fprintf(returns, "%s %s returned on %s\n", bookID, bookName, times());
        fflush(returns);
        fclose(returns);
}


// To display all the available books
int displayBooks()
{
    char list;
    FILE *fptr;
    fptr = fopen(AvailableBooks, "r");

    printf("\nID    BOOK\n");
    printf("----------------------------\n");

    if (fptr == NULL) 
    {
        printf("Empty file");
    } 
    else
    {
        char id[10];
        char bookName[50];

        while (fscanf(fptr, "%s %[^\n]", id, bookName) == 2)
        {
            printf("%-6s %-s\n", id, bookName);
        }

    }

    fclose(fptr);
    return 0;
}


// To lend Books
int lendBooks(char selectedBookID[10])
{
    char name[100];   // Name of lender
    char tmp[100];    // Temporary variable to store content of a file

    int flagBookFound = 0;
    FILE *fptr;
    FILE *tempfile;     
    fptr = fopen(AvailableBooks, "r");
    tempfile = fopen("temp.txt", "w");
    if (fptr == NULL || tempfile == NULL)
    {
        printf("Empty file");
    }

    else
    {
        while (fgets(tmp, 100, fptr) != NULL)   // tmp contains id and book name until \n
        {
            char id[10];
            sscanf(tmp, "%s", id);
            if(strlen(tmp) <= 1)
            {
                for (int i = 0; id[i] != '\0'; i++)
                {
                    id[i] = '\0';
                }
                
            }

            if (strcmp(id, selectedBookID) != 0)
            {
                fputs(tmp, tempfile);
                fflush(tempfile);
            }
            else
            {
                printf("Enter your name: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0';
                tmp[strcspn(tmp, "\n")] = '\0';

                lendfiles(tmp, name);
                lendFileWithoutName(tmp);
                flagBookFound = 1;
                printf("\nLended successfully");
            }
            
        }
        fclose(fptr);
        fclose(tempfile);
    }
    remove(AvailableBooks);
    rename("temp.txt", AvailableBooks);
    if (!flagBookFound)
    {
        printf("\n\t\tThis ID doesn't match\n");
    }
    
    return 0;
}


// To return books
int returnBooks(char bookID[10], char bookName[50])
{

    char bookinlend[50];    // Which have data from fgerts
    char tempid[10];    // ID from lendersWithoutName.txt
    char bookFromLendersWNTxt[50];
    FILE *fptr;
    FILE *lend;
    FILE *lendWithoutName;

    fptr = fopen(AvailableBooks, "a");
    lend = fopen(BooksLended, "a");
    lendWithoutName = fopen(BooksLendedWithoutNames, "a+");

    while (fgets(bookinlend, sizeof(bookinlend), lendWithoutName) != NULL)
    {
        // Check if bookinlend is empty or not. If empty then continue.
        int is_empty = 1;
        for (int i = 0; bookinlend[i] != '\0'; i++)
        {
            if (!isspace((unsigned char) bookinlend[i]))
            {
                is_empty = 0;
                break;
            }
            
        }

        if (is_empty)
        {
            continue;
        }
        
        // To store numeric value i.e ID from the file
        int i=0;
        while (bookinlend[i] != ' ' && bookinlend[i] != '\0')
        {
            tempid[i] = bookinlend[i];
            i++;
        }
        tempid[i] = '\0';

        // Skipping the first whitespace after ID
        while (bookinlend[i] == ' ')
        {
            i++;
        }

        // Adding all the characters excluding ID in bookFromLendersWNTxt
        int j = 0;
        while (bookinlend[i] != '\0' && bookinlend[i] != '\n')
        {
            bookFromLendersWNTxt[j] = bookinlend[i];
            i++;
            j++;
        }
        bookFromLendersWNTxt[j] = '\0';


        // Now actual process to start returning books. 

        // Remove newline character from bookName
        bookName[strcspn(bookName, "\n")] = '\0';

        // Remove newline character from bookFromLendersWNTxt
        bookFromLendersWNTxt[strcspn(bookFromLendersWNTxt, "\n")] = '\0';

        if (strcmp(tempid, bookID) == 0)
        {

            if (strcmp(bookName, bookFromLendersWNTxt) == 0)
            {
                printf("Retuned Successfully \n");
                fclose(fptr);
                fclose(lend);
                fclose(lendWithoutName);

                returnfiles(bookID, bookName);
                writeToAvailableBooks(bookID, bookName);
                removeFromLenders(bookID);
                return 0;
            }

            else
            {
                printf("This book was not lended.");
                return 0;
            }

        }

        for (int i = 0; tempid[i] != '\0'; i++)
        {
            tempid[i] = '\0';
        }
    }
    printf("No book with this id was lended\n");
        
}

    
// To add new books to AvailableBooks.txt file
int addBooks(char bookID[10], char bookName[50], int addRunCount)
{
    char temp[100];
    char id[10];
    int existStatus = 0;  // Flag to check if ID already exists
    FILE *fptr;
    fptr = fopen(AvailableBooks, "r");
    while (fgets(temp, sizeof(temp), fptr))
    {
        sscanf(temp, "%s", id);
        if (strcmp(id, bookID) == 0)
        {
            existStatus = 1;
            break;
        }
    }

    fclose(fptr);
    
    // If the ID exists, display a message and return
    if (existStatus)
    {
        printf("\n\t\tID already exists.\n");
        return 0;
    }

    fptr = fopen(AvailableBooks, "a");
    if (addRunCount == 0)
    {
        fprintf(fptr, "\n%s %s", bookID, bookName);
        fflush(fptr);
    }
    else
    {
        fprintf(fptr, "%s %s", bookID, bookName);
        fflush(fptr);
    }
    fclose(fptr);

    printf("\n\t\tAdded Successfully\n");
    return 0;

}


// Main function
int main()
{
    printf("\t\t Welcome to Library Management System By Shishir and Sulav \n");
    printf("----------------------------------------------------------------------------------- \n\n");

    char choice;
    char availableBooks[100][50];
    int count=0;

    // Open file for appending
    FILE *fptr;
    fptr = fopen(AvailableBooks, "a");
    if(fptr == NULL)
    {
        printf("Error!");
        exit(0);
    }
    else
    {
        fseek(fptr, 0, SEEK_END);
        long fileSize = ftell(fptr);
        if (fileSize == 0) {
            // If the file is empty, write the default books
            fprintf(fptr, "1 C Programming\n31 Engineering Physics\n09 Mathematics");
            fflush(fptr);
        }
        fclose(fptr);
    }

    while (fgets(availableBooks[count], sizeof(availableBooks[count]), fptr) != NULL)
    {
        availableBooks[count][strcspn(availableBooks[count], "\n")] = '\0';
        count++;
    }

    char bookID[10];
    char bookName[50];

    int addRunCount = 0;
    while(1)
    {
        // Emptying bookID and bookName
        for (int i = 0; bookID[i] != '\0'; i++)
        {
            bookID[i] = '\0';
        }
        for (int i = 0; bookName[i] != '\0'; i++)
        {
            bookName[i] = '\0';
        }
        

        // Taking choice of user
        printf("\nWhat would you like to do?\n");
        printf(" - 'D' to display available books.\n");
        printf(" - 'L' to lend a book.\n");
        printf(" - 'A' to add new books.\n");
        printf(" - 'R' to return a book.\n");
        printf(" - 'S' to see the list of lended books.\n");
        printf(" - 'E' to exit\n");
        printf("Your choice: ");
        scanf(" %c", &choice);
        getchar();
        choice = toupper(choice);

        switch (choice)
        {
        case 'D':
            displayBooks();
            break;

        case 'L':
            printf("----------------------Lend books ----------------------\n");
            displayBooks();
            char selectedBookID[10];
            printf("\n\nPlease select the id of book you want to lend \n");
            printf("Which book you want to lend: ");
            scanf("%s", selectedBookID);
            getchar();
            lendBooks(selectedBookID);
            break;

        case 'A':
            
            printf("---------------------Add books------------------\n\n");
            printf("Enter id of the book: ");
            scanf("%s", bookID);
            getchar();
            printf("Enter name of book: ");
            fgets(bookName, sizeof(bookName), stdin);
            addBooks(bookID, bookName, addRunCount);
            addRunCount ++;
            break;

        case 'R':
            printf("----------------------Return books-----------------\n\n");
            printf("Please Enter the exact Id of the book you lended \n");
            printf("Enter id of book you want to return: ");
            scanf("%s", bookID);
            getchar();
            printf("\nPlease Enter Exact name of the book. Also consider upper and lower case characters\n");
            printf("Enter name of book:");
            fgets(bookName, 50, stdin);
            returnBooks(bookID, bookName);
            break;

        case 'S':
            printf("\n--------------------- Here are the books which are lended:------------------- \n\n");
            FILE *lend;
            char temp[100];
            lend = fopen(BooksLended, "r");
            while (fgets(temp, sizeof(temp), lend))
            {
                printf("%s", temp);
            }
            fclose(lend);
            break;

        case 'E':
            printf("\nExited Library Management System");
            exit(0);
            break;

        default:
            printf("Invalid input");
            break;
        }
    }
    return 0;    
}