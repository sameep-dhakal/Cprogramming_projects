#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// Structure to hold hours, minutes, and seconds
struct time
{
    int hrs;
    int min;
    int sec;
};

// Function to perform countdown
void countdown(int seconds) {
    int i;
    while (seconds >= 0) {
        int hours = seconds / 3600;
        int minutes = (seconds % 3600) / 60;
        int remainingSeconds = seconds % 60;
        
        // Display remaining time with formatting
        clrscr();
        printf("*********************************\n");
        printf("*\tCountdown Timer!!!\t*\n");
        printf("*********************************\n*");
        for(i=0;i<31;i++)
            printf(" ");
        printf("*\n");
        printf("*\t%02d hrs :%02d min :%02d sec\t*\n*", hours, minutes, remainingSeconds);
        for(i=0;i<31;i++)
            printf(" ");
        printf("*\n");
        printf("*********************************\n");
        fflush(stdout); // Flush the output buffer to update the displayed time
        sleep(1);       // Delay for 1 second
        seconds--;
    }
    printf("Time's up!!!\n");
}

int main() {
    struct time t;
    int totalSeconds;
    char ch;

    FILE *fptr;
    fptr = fopen("record.txt", "w+");
    if (fptr == NULL) {
        printf("File not found\n");
        exit(0);
    } else {
        printf("File created successfully\n");
    }

label:
    do {
        printf("Enter the duration in hrs:min:sec: ");
        scanf("%02d:%02d:%02d", &t.hrs, &t.min, &t.sec);
        if (t.hrs < 0 || t.min < 0 || t.sec < 0) {
            printf("Invalid duration. Please set a positive duration.\n");
        }
    } while (t.hrs < 0 || t.min < 0 || t.sec < 0);

    // Write the time data to the file
    fwrite(&t, sizeof(t), 1, fptr);

    totalSeconds = t.hrs * 3600 + t.min * 60 + t.sec;
    printf("Countdown starting...\n");
    countdown(totalSeconds);

    printf("Do you want to continue (Y/N)?: ");
    scanf(" %c", &ch);
    if (ch == 'Y' || ch == 'y') {
        goto label;
    }

    // Print the recorded durations from the file
    rewind(fptr); // Move the file pointer to the beginning of the file
    clrscr();
    printf("Record:\n");
    while (fread(&t, sizeof(t), 1, fptr) == 1) {
        printf("%02d hrs:%02d min:%02d sec\n", t.hrs, t.min, t.sec);
    }

    fclose(fptr);
    getch();
    return 0;
}