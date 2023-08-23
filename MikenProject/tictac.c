#include <stdio.h>

// Function to display the Tic Tac Toe board
void display_board(char board[3][3]) {
    printf("-------------\n");
    for (int i = 0; i < 3; i++) {
        printf("| %c | %c | %c |\n", board[i][0], board[i][1], board[i][2]);
        printf("-------------\n");
    }
}

// Function to check for a win
int check_win(char board[3][3], char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return 1;  // Row win
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return 1;  // Column win
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return 1;  // Diagonal win
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return 1;  // Diagonal win
    return 0;  // No win
}

int main() {
    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int row, col;
    char player = 'X';
    int moves = 0;

    printf("Tic Tac Toe\n");
    display_board(board);

    while (moves < 9) {
        printf("Player %c's turn. Enter row and column (e.g., 1 2): ", player);
        scanf("%d %d", &row, &col);

        if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ') {
            printf("Invalid move. Try again.\n");
            continue;
        }

        board[row - 1][col - 1] = player;
        display_board(board);

        if (check_win(board, player)) {
            printf("Player %c wins!\n", player);
            break;
        }

        player = (player == 'X') ? 'O' : 'X';
        moves++;
    }

    if (moves == 9) {
        printf("It's a draw!\n");
    }

    return 0;
}

//MIKEN BANIYA
//ACE079BCT037
#include <stdio.h>

// Function to display the Tic Tac Toe board
void display_board(char board[3][3]) {
    printf("-------------\n");
    for (int i = 0; i < 3; i++) {
        printf("| %c | %c | %c |\n", board[i][0], board[i][1], board[i][2]);
        printf("-------------\n");
    }
}

// Function to check for a win
int check_win(char board[3][3], char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return 1;  // Row win
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return 1;  // Column win
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return 1;  // Diagonal win
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return 1;  // Diagonal win
    return 0;  // No win
}

int main() {
    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int row, col;
    char player = 'X';
    int moves = 0;

    printf("Tic Tac Toe\n");
    display_board(board);

    while (moves < 9) {
        printf("Player %c's turn. Enter row and column (e.g., 1 2): ", player);
        scanf("%d %d", &row, &col);

        if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ') {
            printf("Invalid move. Try again.\n");
            continue;
        }

        board[row - 1][col - 1] = player;
        display_board(board);

        if (check_win(board, player)) {
            printf("Player %c wins!\n", player);
            break;
        }

        player = (player == 'X') ? 'O' : 'X';
        moves++;
    }

    if (moves == 9) {
        printf("It's a draw!\n");
    }

    return 0;
}