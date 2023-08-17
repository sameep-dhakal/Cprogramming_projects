#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void update_high_score(int score) {
    FILE *file = fopen("high.txt", "w");
    if (file != NULL) {
        fprintf(file, "%d", score);
        fclose(file);
        printf("New high score saved!\n");
    } else {
        printf("Unable to save high score.\n");
    }
}

int get_high_score() {
    int high_score = 0;
    FILE *file = fopen("high.txt", "r");
    if (file != NULL) {
        fscanf(file, "%d", &high_score);
        fclose(file);
    }
    return high_score;
}

void print_array(int array[], int count) {
    printf("Your guesses\t");
    for (int i = 0; i < count; i++) {
        printf("%d\t", array[i]);
    }
    printf("\n");
}

void play_game() {
    int guesses[101];
    int guess_count = 0;
    int random = rand() % 101;
    printf("Guess a number\t");
    while (1) {
        int guess;
        scanf("%d", &guess);
        guesses[guess_count] = guess;
        guess_count++;
        if (guess == random) {
            printf("You win\n");
            break;
        } else if (guess < random) {
            printf("You are low\n");
            printf("Try again\t");
        } else {
            printf("You are high\n");
            printf("Try again\t");
        }
    }
    print_array(guesses, guess_count);
    int current_high_score = get_high_score();
    if (guess_count < current_high_score || current_high_score == 0) {
        update_high_score(guess_count);
    }
}

int main() {
    srand(time(NULL));
    int choice;
    do {
        printf("0.Exit game \n1.Play game\n");
        printf("Enter your choice\t");
        scanf("%d", &choice);
        switch (choice) {
            case 0:
                printf("Thanks for nothing\n");
                return 0;
            case 1:
                play_game();
                printf("Lets play the game\n");
                break;
            default:
                printf("invalid");
                break;
        }
    } while (choice != 0);
    int high_score = get_high_score();
    printf("High Score: %d\n", high_score);
    return 0;
}
