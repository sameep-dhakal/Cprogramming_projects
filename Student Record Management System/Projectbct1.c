#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 50

struct Student {
    int rollNumber;
    char name[50];
    int age;
    float marks;
};

struct Student students[MAX_STUDENTS];
int totalStudents = 0;

void addStudent();
void displayAllStudents();
void searchStudent();

void addStudent() {
    if (totalStudents < MAX_STUDENTS) {
        printf("Enter roll number: ");
        scanf("%d", &students[totalStudents].rollNumber);
        printf("Enter name: ");
        scanf("%s", students[totalStudents].name);
        printf("Enter age: ");
        scanf("%d", &students[totalStudents].age);
        printf("Enter marks: ");
        scanf("%f", &students[totalStudents].marks);

        totalStudents++;
        printf("Student record added successfully.\n");
    } else {
        printf("Maximum number of students reached.\n");
    }
}

void displayAllStudents() {
    if (totalStudents > 0) {
        printf("Student Records:\n");
        int i;
        for (i = 0; i < totalStudents; ++i) {
            printf("Roll Number: %d, Name: %s, Age: %d, Marks: %.2f\n",
                students[i].rollNumber, students[i].name,
                students[i].age, students[i].marks);
        }
    } else {
        printf("No student records available.\n");
    }
}

void searchStudent() {
    int rollNumber;
    printf("Enter roll number to search: ");
    scanf("%d", &rollNumber);

    int i;
    for (i = 0; i < totalStudents; ++i) {
        if (students[i].rollNumber == rollNumber) {
            printf("Student Found:\n");
            printf("Roll Number: %d, Name: %s, Age: %d, Marks: %.2f\n",
                students[i].rollNumber, students[i].name,
                students[i].age, students[i].marks);
            return;
        }
    }

    printf("Student not found with roll number %d.\n", rollNumber);
}

int main() {
    int choice;

    do {
        printf("Student Record Management System\n");
        printf("1. Add Student Record\n");
        printf("2. Display All Records\n");
        printf("3. Search Student Record\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}
