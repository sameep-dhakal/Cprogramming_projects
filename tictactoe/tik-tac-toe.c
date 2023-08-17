#include <stdio.h>

char board[3][3]; 

void Board() {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void signBoard(char mark, int row, int col) {
    board[row][col] = mark;
}

int checkWin() {
    int i;
    for(i = 0; i < 3; i++) {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') return 1;
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') return 1;
    }
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') return 1;
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') return 1;
    return 0;
}

int main() {
    int i, row, col;
    char mark;
    for (i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
    for(i = 0; i < 9; i++) {
        Board();
        if(i % 2 == 0) mark = 'X';
        else mark = 'O';
        printf("Enter the row and column for %c: ", mark);
        scanf("%d %d", &row, &col);
        signBoard(mark, row, col);
        if(checkWin()) {
            printf("%c Wins!\n", mark);
            break;
        }
    }
    return 0;
}
