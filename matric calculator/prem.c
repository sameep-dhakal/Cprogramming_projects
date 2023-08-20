#include <stdio.h>
#define mrows 10
#define mcols 10

int matrix1[mrows][mcols];
int matrix2[10][10];

void readMatrix(int rows, int cols, int matrix[10][10]) {
    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}
void printMatrix(int rows, int cols, int matrix[10][10]) {
    for (int i = 0; i < rows; i++) {
        printf("[ ");
        for (int j = 0; j < cols; j++) {
            printf("\033[1;32m");
            printf("%-7d", matrix[i][j]);
            printf("\033[0m");
        }
        printf(" ]\n");
    }
}
void printTransposedMatrix(int rows, int cols, int matrix[10][10]) {
    for (int i = 0; i < rows; i++) {
        printf("[ ");
        for (int j = 0; j < cols; j++) {
            printf("%-7d", matrix[j][i]);
        }
        printf(" ]\n");
    }
}

void addMatrices(int rows, int cols) {
    int result[10][10];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    printf("Result of addition:\n");
    printMatrix(rows, cols, result);
}

void subtractMatrices(int rows, int cols) {
    int result[10][10];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    printf("Result of subtraction:\n");
    printMatrix(rows, cols, result);
}

void scalarMultiplyMatrix(int rows, int cols, int scalar) {
    int result[10][10];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] * scalar;
        }
    }
    printf("Result of scalar multiplication:\n");
    printMatrix(rows, cols, result);
}

void scalarDivideMatrix(int rows, int cols, int scalar) {
    if (scalar == 0) {
        printf("Cannot divide by zero.\n");
        return;
    }
    int result[10][10];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] / scalar;
        }
    }
    printf("Result of scalar division:\n");
    printMatrix(rows, cols, result);
}
void multiplyMatrices(int rows, int cols) {
    int result[10][10];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = 0;
            for (int k = 0; k < cols; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    printf("Result of multiplication:\n");
    printMatrix(rows, cols, result);
}

int main()
{
    int rows, cols;
    int scalar;
    while (1) 
    {
        int choice=5;
        printf("\n");
        printf("\033[1;34m");
        printf("MATRIX OPERATIONS\n");
        printf("\033[0m");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Scalar Multiplication\n");
        printf("4. Scalar Division\n");
        printf("5. Matrix multiplication\n");
        printf("6. Transpose of a matrix\n");
        printf("\033[1;31m"); 
        printf("7. Exit\n");
        printf("\033[0m"); 
        

        printf("\033[1;33m"); 
        printf("\nChoose what you want to do: ");
        printf("\033[0m"); 
        
        scanf("%d", &choice);

        if (choice == 7) 
        {
            break; 
        }
        switch (choice) 
        {
            
            case 1:
                while (1)
                {
                    
                    char ch = 'n';
                    printf("Enter the number of rows and columns (max %d): \n", mrows);
                    printf("\033[1;32m");
                    printf("Rows: ");
                    printf("\033[0m");
                    scanf("%d", &rows);
                    printf("\033[1;32m"); 
                    printf("Columns: ");
                    printf("\033[0m");
                    scanf("%d", &cols);

                    if (rows > mrows || cols > mcols) {
                        printf("Matrix dimensions exceed maximum limits.\n");
                        continue;
                    }

                    printf("\033[1;32m");
                    printf("for first matrix:\n");
                    printf("\033[0m");
                    readMatrix(rows, cols, matrix1);
                    printf("\033[1;32m");
                    printf("for second matrix:\n");
                    printf("\033[0m");
                    readMatrix(rows, cols, matrix2);
                    addMatrices(rows, cols);
                    printf("Add more matrices? (y/n) :\nPress 'n' to go back to menu\n");
                    scanf(" %c", &ch);
                    if(ch == 'n'||ch == 'N')
                    break;
                    else{
                        continue;
                    }
                }
                break;
            case 2:
                while (1)
                {
                    
                    char ch = 'n';
                    printf("Enter the number of rows and columns (max %d): \n", mrows);
                    printf("\033[1;32m");
                    printf("Rows: ");
                    printf("\033[0m");
                    scanf("%d", &rows);
                    printf("\033[1;32m"); 
                    printf("Columns: ");
                    printf("\033[0m");
                    scanf("%d", &cols);

                    if (rows > mrows || cols > mcols) {
                        printf("Matrix dimensions exceed maximum limits.\n");
                        continue;
                    }

                    printf("\033[1;32m");
                    printf("for first matrix:\n");
                    printf("\033[0m");
                    readMatrix(rows, cols, matrix1);
                    printf("\033[1;32m");
                    printf("for second matrix:\n");
                    printf("\033[0m");
                    readMatrix(rows, cols, matrix2);
                    subtractMatrices(rows, cols);
                    printf("Subtract more matrices? (y/n) :\nPress 'n' to go back to menu\n");
                    scanf(" %c", &ch);
                    if(ch == 'n'||ch == 'N')
                    break;
                    else{
                        continue;
                    }
                }
                break;
            case 3:
                while (1)
                    {
                        
                        char ch = 'n';
                        printf("Enter the number of rows and columns (max %d): \n", mrows);
                        printf("\033[1;32m");
                        printf("Rows: ");
                        printf("\033[0m");
                        scanf("%d", &rows);
                        printf("\033[1;32m"); 
                        printf("Columns: ");
                        printf("\033[0m");
                        scanf("%d", &cols);

                        if (rows > mrows || cols > mcols) {
                            printf("Matrix dimensions exceed maximum limits.\n");
                            continue;
                        }
                        readMatrix(rows, cols, matrix1);
                        printf("\033[1;32m");
                        printf("Enter a scalar value: ");
                        printf("\033[0m");
                        scanf("%d", &scalar);
                        scalarMultiplyMatrix(rows, cols, scalar);
                        printf("Multiply more matrices? (y/n) :\nPress 'n' to go back to menu\n");
                        scanf(" %c", &ch);
                        if(ch == 'n'||ch == 'N')
                        break;
                        else{
                            continue;
                        }
                    }
                    break;
            case 4:
                while (1)
                    {
                        
                        char ch = 'n';
                        printf("Enter the number of rows and columns (max %d): \n", mrows);
                        printf("\033[1;32m");
                        printf("Rows: ");
                        printf("\033[0m");
                        scanf("%d", &rows);
                        printf("\033[1;32m"); 
                        printf("Columns: ");
                        printf("\033[0m");
                        scanf("%d", &cols);

                        if (rows > mrows || cols > mcols) {
                            printf("Matrix dimensions exceed maximum limits.\n");
                            continue;
                        }
                        readMatrix(rows, cols, matrix1);
                        printf("\033[1;32m");
                        printf("Enter a scalar value for division: ");
                        printf("\033[0m");
                        scanf("%d", &scalar);
                        scalarDivideMatrix(rows, cols, scalar);
                        printf("Divide more matrices? (y/n) :\nPress 'n' to go back to menu\n");
                        scanf(" %c", &ch);
                        if(ch == 'n'||ch == 'N')
                        break;
                        else{
                            continue;
                        }
                    }
                    break;
            case 5:
                 while (1) {
                    char ch = 'n';
                     
                    printf("Enter the number of rows and columns (max %d) for the matrices:\n", mrows);
                   
                    printf("\033[1;36m"); 
                    printf("Rows: ");
                    printf("\033[0m");
                    scanf("%d", &rows);
                    printf("\033[1;36m"); 
                    printf("Columns: ");
                    printf("\033[0m");
                    scanf("%d", &cols);
                    
                    if (rows > mrows || cols > mcols) {
                        printf("Matrix dimensions exceed maximum limits.\n");
                        continue;
                    }
                    
                    printf("For the first matrix:\n");
                    readMatrix(rows, cols, matrix1);
                    printf("For the second matrix:\n");
                    readMatrix(rows, cols, matrix2);
                    multiplyMatrices(rows, cols);
                    printf("Multiply more matrices? (y/n):\nPress 'n' to go back to menu\n ");
                    scanf(" %c", &ch);
                    if (ch == 'n' || ch == 'N') {
                        break;
                    } else {
                        continue;
                    }
                }
                break;           
            case 6:
                while (1)
                    {
                        
                        char ch = 'n';
                        printf("Enter the number of rows and columns (max %d): \n", mrows);
                        printf("\033[1;32m");
                        printf("Rows: ");
                        printf("\033[0m");
                        scanf("%d", &rows);
                        printf("\033[1;32m"); 
                        printf("Columns: ");
                        printf("\033[0m");
                        scanf("%d", &cols);

                        if (rows > mrows || cols > mcols) {
                            printf("Matrix dimensions exceed maximum limits.\n");
                            continue;
                        }
                        readMatrix(rows, cols, matrix1);
                        printTransposedMatrix(cols, rows, matrix1);
                        printf("Convert more matrices? (y/n) :\nPress 'n' to go back to menu\n");
                        scanf(" %c", &ch);
                        if(ch == 'n'||ch == 'N')
                        break;
                        else{
                            continue;
                        }
                    }
                    break;
            default:
                printf("\033[1;31m"); 
                printf("Not Available!\n");
                printf("\033[0m");                     
        }
    }
    return 0;   
}

