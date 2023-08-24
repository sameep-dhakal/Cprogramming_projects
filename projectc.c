#include <stdio.h>
#include <string.h>

// Structure to represent a student
struct Student {
    char name[50];
    int rollNumber;
    float marks;
};

// Function to add a new student record
void addStudent(struct Student students[], int *numStudents) {
    if (*numStudents >= 100) {
        printf("Database is full. Cannot add more students.\n");
        return;
    }

    struct Student newStudent;
    printf("Enter student name: ");
    scanf("%s", newStudent.name);
    printf("Enter roll number: ");
    scanf("%d", &newStudent.rollNumber);
    printf("Enter marks: ");
    scanf("%f", &newStudent.marks);

    students[*numStudents] = newStudent;
    (*numStudents)++;

    printf("Student record added successfully.\n");
}

// Function to view all student records
void viewStudents(struct Student students[], int numStudents) {
    if (numStudents == 0) {
        printf("Database is empty.\n");
        return;
    }

    printf("Student Records:\n");
    for (int i = 0; i < numStudents; i++) {
        printf("Name: %s\n", students[i].name);
        printf("Roll Number: %d\n", students[i].rollNumber);
        printf("Marks: %.2f\n", students[i].marks);
        printf("-------------------------\n");
    }
}

// Function to search for a student by roll number
void searchStudent(struct Student students[], int numStudents) {
    if (numStudents == 0) {
        printf("Database is empty.\n");
        return;
    }

    int rollToSearch;
    printf("Enter roll number to search: ");
    scanf("%d", &rollToSearch);

    for (int i = 0; i < numStudents; i++) {
        if (students[i].rollNumber == rollToSearch) {
            printf("Student Found:\n");
            printf("Name: %s\n", students[i].name);
            printf("Roll Number: %d\n", students[i].rollNumber);
            printf("Marks: %.2f\n", students[i].marks);
            return;
        }
    }

    printf("Student not found.\n");
}

int main() {
    struct Student students[100]; // Array to store student records
    int numStudents = 0; // Current number of student records

    int choice;
    do {
        printf("\nStudent Database Menu:\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &numStudents);
                break;
            case 2:
                viewStudents(students, numStudents);
                break;
            case 3:
                searchStudent(students, numStudents);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

