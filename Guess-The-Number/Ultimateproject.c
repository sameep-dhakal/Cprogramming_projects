#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


// Function to play a single round of the game
void playGame(int lowerrange, int upperrange) {
    int secretNumber = rand() % (upperrange - lowerrange + 1) + lowerrange;
    int guess;
    int attempts = 0;

    printf("I have selected a number between %d and %d. Try to guess it!\n", lowerrange, upperrange);

    do {
        printf("Enter your guess: ");
        scanf("%d", &guess);
        attempts++;

        if (guess < secretNumber) {
            printf("Too low! Try again.\n");
        } else if (guess > secretNumber) {
            printf("Too high! Try again.\n");
        } else {
            printf("\033[1;34m"); 
            printf("Congratulations! You guessed the number %d in %d attempts!\n", secretNumber, attempts);
            printf("\033[0m");
            printf("\033[1;36m");
            printf("\nPlease come again and try our harder levels.\n \n Thank you!!!");
            printf("\033[0m");
            break;
        }
    } while (1);
}

int main() {
    srand(time(0));
    printf("\033[1;34m");
    printf("\n \nWelcome to the GUESS THE NUMBER game!\n");
    printf("\n \n");
    printf(" #         #  ##########  #          #########  ##########   #         #  ##########    ##    ##     \n");
    printf(" #         #  #           #          #          #        #   #  #   #  #  #             ##    ##     \n");
    printf(" #         #  #           #          #          #        #   #    #    #  #             ##    ##     \n");
    printf(" #         #  ##########  #          #          #        #   #         #  ##########    ##    ##     \n");
    printf(" #    #    #  #           #          #          #        #   #         #  #             ##    ##     \n");
    printf(" #  #   #  #  #           #          #          #        #   #         #  #                          \n");
    printf(" #         #  ##########  ########   #########  ##########   #         #  ##########    #     #      \n");
    printf("\n-------------------------------------------------------------------------------------------------------------\n");
    printf("\033[0m");
    
    printf("\033[1;35m");
    printf("Brought to you by:\n Sugam Sen Sinjali\n");
    printf("\033[0m");
    printf("\033[1;32m");
    printf(" #######   #     #  #######        #        #        #           \n");
    printf(" #         #     #  #             # #       #  #   # #           \n");
    printf(" #######   #     #  #  ####     # # # #     #        #           \n");
    printf("       #   #     #  #     #    #       #    #        #           \n");
    printf(" #######   #######  #######   #         #   #        #           \n");
    printf("\033[0m");
    printf("\n");
    printf("\033[1;36m");
    printf(" *******  *******  *        *   *********        *        *         *******      \n");
    printf(" *           *     * *      *        *          * *       *            *          \n");
    printf(" *******     *     *   *    *        *        * * * *     *            *          \n");
    printf("       *     *     *    *   *   *    *       *       *    *            *          \n");
    printf(" *******  *******  *      * *   ******     *           *  * *****   *******       \n");
    printf("\033[0m");
    
    printf("-------------------------------------------------------------------------------------------------------------");

    char choice[5];
    printf("\033[1;37m");
    printf("\nDo you want to play? (yes/no):\n ");
    printf("\033[0m");
    scanf("%s", choice);

    if (strcmp(choice, "yes") == 0) {
        printf("\033[1;31m");
        printf("Let's see what you can do!");
        printf("\033[0m");
        int difficulty;
        printf("\033[1;32m");
        printf("\nSelect difficulty level:\n");
        printf("1. Easy (1-100)\n");
        printf("2. Medium (1-1000)\n");
        printf("3. Hard (1-10000)\n");
        printf("\033[0m");
        printf("\033[1;31m");
        printf("\nEnter the number corresponding to your choice:\n ");
        printf("\033[0m");
        scanf("%d", &difficulty);

        int lowerrange, upperrange;

        switch (difficulty) {
            case 1:
                lowerrange = 1;
                upperrange = 100;
                break;
            case 2:
                lowerrange = 1;
                upperrange = 1000;
                break;
            case 3:
                lowerrange = 1;
                upperrange = 10000;
                break;
            default:
                printf("\033[1;34m");
                printf("-------------------------------------------------------------------------------------------------------------");
                printf("\nxxxxxxxxxxxx\tInvalid choice\txxxxxxxxxxxxxxx \n");
                printf("\033[1;36m");
                printf("Tip:  Run again and Try putting the choice between 1 and 3 only\n");
                printf("\033[0m");
                printf("\033[0m");
                printf("\033[1;31m");
                printf("EXITING......");
                printf("\033[0m");
                return 1;
        }

        playGame(lowerrange, upperrange);

    } else {
        printf("\033[1;36m");
        printf("\nTip:  Try writing 'yes' as a whole word to proceed.\n");
        printf("\033[0m");
        printf("\033[1;31m");
        printf("\nCome back when you grow up, kid. Sayonara.\n");
        printf("\033[0m");
    }

    return 0;
}
