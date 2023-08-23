Project Details:
-----------------
Project: Student Record Management System
Course: C Programming (1st Semester)
Authors: Utsav Dhugnana, Sulav Karki
Institution: Advanced College of Engineering and Management

Description:
This program is a student record management system implemented in C as a final project for the C Programming course during the first semester.
It allows users to perform various operations such as adding students, displaying student information, searching for students by roll number, and saving/loading records to/from a file.

Submitted to:
Department of Electronics and Computer Engineering,
Advanced College of Engineering and Management.

Date:2023/08/17

Breakdown of code:
1. Struct Definition (struct Student):
   - Defines a struct named Student that holds various attributes of a student such as name, roll number, stream, address, and email.

2. Input Buffer Handling (clearInputBuffer):
   - Provides a function to clear the input buffer, ensuring there are no remaining characters in the buffer after user input.

3. Adding a Student (addStudent):
   - Prompts the user to input various attributes of a new student and adds the student to the students array.

4. Displaying Students (displayStudents):
   - Displays the information of all students in the students array.

5. Searching for a Student (searchStudent):
   - Prompts the user to input a roll number and searches the students array for a student with a matching roll number. If found, the student's information is displayed.

6. Saving Records to File (saveToFile):
   - Writes the student records stored in the students array to a text file named "students.txt".

7. Loading Records from File (loadFromFile):
   - Reads student records from the "students.txt" file and populates the students array. Returns a status indicating whether the loading was successful.

8. Main Function (main):
   - Initializes an array of Student structs and a counter to keep track of the number of students.
   - Tries to load existing student records from the file "students.txt" and displays appropriate messages based on whether records were loaded successfully.
   - Enters a loop to display a menu of options and prompt the user for their choice.
   - Based on the user's choice, performs various operations like adding a student, displaying records, saving records, searching for a student, and exiting the program.
   - The loop continues until the user chooses to exit (option 5).

For any questions and inquiry contact:
Utsav Dhungana: utsavdhungana838@gmail.com
Sulav Karki: sulavkarki488@gmail.com