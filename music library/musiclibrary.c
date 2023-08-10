#include <stdio.h>
#include <string.h>

struct Music {
    char name[100];
    char artist[100];
    int album;
    char genre[20];
};

void display(struct Music songs[], int count) {
    printf("\nMusic Organizer:\n");
    printf("----------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("Name: %s | Artist: %s | Album: %d | Genre: %s\n",
               songs[i].name, songs[i].artist, songs[i].album, songs[i].genre);
    }
    printf("----------------------------\n");
}

void displayGrouped(struct Music songs[], int count) {
    printf("\nGrouped Music:\n");
    printf("----------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%s: ", songs[i].genre);
        int j = i;
        while (j < count && strcmp(songs[j].genre, songs[i].genre) == 0) {
            printf("%s, ", songs[j].name);
            j++;
        }
        printf("\n");
        i = j - 1;
    }
    printf("----------------------------\n");
}
void displayartist(struct Music songs[],int count){
     printf("\nGrouped artist:\n");
    printf("----------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%s: ", songs[i].genre);
        int j = i;
        while (j < count && strcmp(songs[j].genre, songs[i].genre) == 0) {
            printf("%s, ", songs[j].artist);
            j++;
        }
        printf("\n");
        i = j - 1;
    }
    printf("----------------------------\n");

}
void sortByAlbum(struct Music songs[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (songs[i].album > songs[j].album) {
                struct Music temp = songs[i];
                songs[i] = songs[j];
                songs[j] = temp;
            }
        }
    }
}

int main() {
    struct Music songs[100];
    int count = 0;

    printf("Welcome to the Music Organizer!\n");
    do {
        printf("\nEnter Music Details:\n");
        printf("Name: ");
        scanf("%s", songs[count].name);
        printf("Artist: ");
        scanf("%s", songs[count].artist);
        printf("Album Number: ");
        scanf("%d", &songs[count].album);
        printf("Choose Genre (rock/pop/rap/classical/others): ");
        scanf("%s", songs[count].genre);
        count++;

        char choice;
        printf("Do you want to add more music? (y/n): ");
        scanf(" %c", &choice);
        if (choice != 'y' && choice != 'Y') {
            break;
        }
    } while (1);

    // Sorting by genre, then name, then album
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(songs[i].genre, songs[j].genre) > 0 ||
                (strcmp(songs[i].genre, songs[j].genre) == 0 && strcmp(songs[i].name, songs[j].name) > 0) ||
                (strcmp(songs[i].genre, songs[j].genre) == 0 && strcmp(songs[i].name, songs[j].name) == 0 && songs[i].album > songs[j].album)) {
                struct Music temp = songs[i];
                songs[i] = songs[j];
                songs[j] = temp;
            }
        }
    }

    displayGrouped(songs, count);
    sortByAlbum(songs, count);
    display(songs, count);
    displayartist(songs,count);
    return 0;
}
