#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

double evalTerm(char* expr, int* index);
double evalFactor(char* expr, int* index);

double getVal(char *expr, int *index) {
    double result = 0.0;
    int sign = 1;

    if (expr[*index] == '+' || expr[*index] == '-') {
        sign = (expr[*index] == '-') ? -1 : 1;
        (*index)++;
    }

    while (isdigit(expr[*index])) {
        result = result * 10 + (expr[*index] - '0');
        (*index)++;
    }

    if (expr[*index] == '.') {
        (*index)++;
        double decimal = 0.1;

        while (isdigit(expr[*index])) {
            result += (expr[*index] - '0') * decimal;
            decimal *= 0.1;
            (*index)++;
        }
    }

    if (expr[*index] == '*') {
        (*index)++;
        double nextVal = getVal(expr, index);
        result *= nextVal;
    }

    return result * sign;
}

double evalExpr(char* expr, int* index) {
    double result = evalTerm(expr, index);

    while (expr[*index] == '+' || expr[*index] == '-') {
        char op = expr[*index];
        (*index)++;
        double nextValue = evalTerm(expr, index);

        if (op == '+') {
            result += nextValue;
        } else if (op == '-') {
            result -= nextValue;
        }
    }

    return result;
}

double evalTerm(char* expr, int* index) {
    double result = evalFactor(expr, index);

    while (expr[*index] == '*' || expr[*index] == '/') {
        char op = expr[*index];
        (*index)++;
        double nextValue = evalFactor(expr, index);

        if (op == '*') {
            result *= nextValue;
        } else if (op == '/') {
            if (nextValue == 0) {
                printf("Error: Division by zero.\n");
                exit(EXIT_FAILURE);
            }
            result /= nextValue;
        }
    }

    return result;
}

double evalFactor(char* expr, int* index) {
    double result = getVal(expr, index);

    while (expr[*index] == '^') {
        (*index)++;
        double exponent = evalFactor(expr, index);
        result = pow(result, exponent);
    }

    if (expr[*index] == '(') {
        (*index)++;
        result = evalExpr(expr, index);
        if (expr[*index] != ')') {
            printf("Error: Missing closing parenthesis.\n");
            exit(EXIT_FAILURE);
        }
        (*index)++;
    }

    return result;
}

void calc(char expr[]) {
    char exprnospc[100];
    int i, j = 0, index = 0;
    double result;
    printf("\nEnter arithmetic expression: ");
    fgets(expr, 100, stdin);
    for (i = 0; expr[i] != '\0'; ++i) {
        if (!isspace(expr[i])) {
            exprnospc[j++] = expr[i];
        }
    }
    exprnospc[j] = '\0';
    result = evalExpr(exprnospc, &index);
    if (result == (int)result) {
        printf("Result = %d\n\n", (int)result);
    } else if (result >= 1e5 || (result <= -1e5 || (result > 0 && result < 1e-5) || (result < 0 && result > -1e-5))) {
        printf("Result = %E\n\n", result);
    } else {
        printf("Result = %f\n\n", result);
    }
}

int main() {
    char expr[100];
    int ch;

    printf("=====================\n");
    printf("SCIENTIFIC CALCULATOR\n");
    printf("=====================\n\n");
    do {
        printf("1. Calculator\n");
        printf("2. Quit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);
        getchar();
        switch (ch) {
            case 1:
                calc(expr);
                break;
            case 2:
                printf("\nQuitting.\n");
                break;
            default:
                printf("\nInvalid\n");
        }
    } while (ch != 2);
    return 0;
}
