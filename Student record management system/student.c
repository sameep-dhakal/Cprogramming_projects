#include <stdio.h>
#include <string.h>

// Define a struct to hold student information
struct Student {
    char name[50];
    char rollNumber[15];
    char stream[50];
    char address[100];
    char email[50];
};

// Function to clear the input buffer
void clearInputBuffer() {
    int c;
    // Read characters until a newline or EOF is encountered
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to add a new student to the array
void addStudent(struct Student students[], int *count) {
    struct Student newStudent;

    // Prompt and input student details
    printf("Enter student name: ");
    fgets(newStudent.name, sizeof(newStudent.name), stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0';

    printf("Enter roll number: ");
    fgets(newStudent.rollNumber, sizeof(newStudent.rollNumber), stdin);
    newStudent.rollNumber[strcspn(newStudent.rollNumber, "\n")] = '\0';

    printf("Enter stream: ");
    fgets(newStudent.stream, sizeof(newStudent.stream), stdin);
    newStudent.stream[strcspn(newStudent.stream, "\n")] = '\0';

    printf("Enter address: ");
    fgets(newStudent.address, sizeof(newStudent.address), stdin);
    newStudent.address[strcspn(newStudent.address, "\n")] = '\0';

    printf("Enter email: ");
    fgets(newStudent.email, sizeof(newStudent.email), stdin);
    newStudent.email[strcspn(newStudent.email, "\n")] = '\0';

    // Add the new student to the array and increment count
    students[*count] = newStudent;
    (*count)++;
}

// Function to display all students' information
void displayStudents(struct Student students[], int count) {
    int i;
    printf("\nStudent Records:\n");
    for (i = 0; i < count; i++) {
        // Print student details
        printf("Name: %s\n", students[i].name);
        printf("Roll Number: %s\n", students[i].rollNumber);
        printf("Stream: %s\n", students[i].stream);
        printf("Address: %s\n", students[i].address);
        printf("Email: %s\n\n", students[i].email);
    }
}

// Function to search for a student by roll number
void searchStudent(struct Student students[], int count) {
    int i;
    char searchRollNumber[15];
    // Prompt for roll number to search
    printf("Enter roll number to search: ");
    fgets(searchRollNumber, sizeof(searchRollNumber), stdin);
    searchRollNumber[strcspn(searchRollNumber, "\n")] = '\0';

    for (i = 0; i < count; i++) {
        // Compare roll numbers to find a matching student
        if (strcmp(students[i].rollNumber, searchRollNumber) == 0) {
            // Display found student details and return
            printf("\nStudent Details:\n");
            printf("Name: %s\n", students[i].name);
            printf("Roll Number: %s\n", students[i].rollNumber);
            printf("Stream: %s\n", students[i].stream);
            printf("Address: %s\n", students[i].address);
            printf("Email: %s\n\n", students[i].email);
            return;
        }
    }
    // If no student is found, print a message
    printf("Student with roll number %s not found.\n", searchRollNumber);
}

// Function to save student records to a file
void saveToFile(struct Student students[], int count, const char *filename) {
    int i;
    // Open the file for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (i = 0; i < count; i++) {
        // Write student details to the file
        fprintf(file, "%s %s %s %s %s\n", students[i].name, students[i].rollNumber, students[i].stream, students[i].address, students[i].email);
    }

    // Close the file
    fclose(file);
}

// Function to load student records from a file
int loadFromFile(struct Student students[], int *count, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return 0;
    }

    *count = 0;
    // Read student details from the file
    while (fscanf(file, "%s %s %s %s %s", students[*count].name, students[*count].rollNumber, students[*count].stream, students[*count].address, students[*count].email) != EOF) {
        (*count)++;
    }

    // Close the file and return success
    fclose(file);
    return 1;
}

int main() {
    struct Student students[100];
    int studentCount = 0;

    // Load existing student records or display message
    if (loadFromFile(students, &studentCount, "students.txt")) {
        printf("Student records loaded successfully.\n");
    } else {
        printf("No existing records found.\n");
    }

    int choice;
    int i;
    do {
        // Display menu options
        printf("\nMenu:\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Save Records\n");
        printf("4. Search Student by Roll Number\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Clear input buffer after reading integer
        clearInputBuffer();

        // Perform operations based on user's choice
        switch (choice) {
            case 1:
                addStudent(students, &studentCount);
                break;
            case 2:
                displayStudents(students, studentCount);
                break;
            case 3:
                saveToFile(students, studentCount, "students.txt");
                printf("Student records saved successfully.\n");
                break;
            case 4:
                searchStudent(students, studentCount);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5); // Continue loop until user chooses to exit

    return 0;
}