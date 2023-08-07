#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "term.h"

#define bool _Bool
#define true 1
#define false 0

/* Include windows headers if compiling on Windows. */
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#endif

/* Maximum possible string length allowed. */
#define MAX_LEN 100

typedef enum {
    Watched = 1,
    PlanToWatch = 2,
    Watching = 3,
    Dropped = 4,
    Unwatched = 5
} WatchState;

WatchState get_state() {
    printf("Change state to:\n");
    printf("\t1. Watched\n");
    printf("\t2. Plan to watch\n");
    printf("\t3. Watching\n");
    printf("\t4. Dropped\n");
    printf("\t5. Unwatched\n");

    int value;
retry:
    if (scanf("%d", &value) != 1) {
        fprintf(stderr, "Please enter a number!\n");
        goto retry;
    }
    if (value < 1 || value > 5) {
        fprintf(stderr, "Enter a valid state!\n");
        goto retry;
    }
    fflush(stdin);

    return (WatchState)value;
}

const char* watch_state_to_string(WatchState state) {
    switch (state) {
        case Watched:
            return "Watched";
        case PlanToWatch:
            return "Plan to watch";
        case Watching:
            return "Watching";
        case Dropped:
            return "Dropped";
        case Unwatched:
            return "Unwatched";
        default:
            return "Unknown";
    }
}

typedef struct {
    char name[MAX_LEN];
    WatchState state;
} Movie;

typedef struct {
    char name[MAX_LEN];
    int episodes;
    WatchState state;
} Series;

typedef struct {
    char uname[MAX_LEN];

    /* Both `movies` and `series` are malloc'd and grow their size as needed. */
    Movie* movies;
    int movie_count;
    int movie_cap;

    Series* series;
    int series_count;
    int series_cap;
} Profile;

Movie movie_new() {
    Movie movie;

    printf("Enter name for movie:\n");
    fgets(movie.name, MAX_LEN, stdin);
    /* Removes the newline character that fgets() puts at the end. */
    movie.name[strcspn(movie.name, "\n")] = 0;
    fflush(stdin);

    movie.state = Unwatched;
    return movie;
}

void movie_print(Movie movie) {
    printf("\tMovie name: %s\n", movie.name);
    printf("\tState: %s\n", watch_state_to_string(movie.state));
}

/* Get a movie from the movie list in a profile. */
Movie* movie_get(Profile* p, const char* name) {
    for (int i = 0; i < p->movie_count; i++) {
        if (strcmp(p->movies[i].name, name) == 0) {
            return &p->movies[i];
        }
    }

    return NULL;
}

/* This is only called when we are sure that the movie with the provided
 * name exists, so there is no need to check if it does. The situation
 * is similar with series_remove(). */
void movie_remove(Profile* p, const char* name) {
    for (int i = 0; i < p->movie_count; i++) {
        if (strcmp(p->movies[i].name, name) == 0) {
            for (int j = i; j < p->movie_count - 1; j++) {
                p->movies[j] = p->movies[j + 1];
            }

            p->movie_count--;
            return;
        }
    }

    fprintf(stderr, "Series not found.");
    return;
}

/* Add a movie to the movie list in a profile. */
void movie_add(Profile* p, Movie movie) {
    /* This if statement checks if the capacity of the `movies` array is less
     * than the number of elements, and if so it increases the capacity by
     * using the realloc() function. Same thing done with series_add(). */
    if (p->movie_cap <= p->movie_count) {
        /* Get the current capacity of the movie array. */
        int cap = p->movie_cap;

        /* Grow the capacity as needed. */
        p->movie_cap = cap < 8 ? 8 : cap * 2;

        /* Now set the size of `movies` to the new grown capacity. */
        p->movies = realloc(p->movies, p->movie_cap * sizeof(Movie));
        if (p->movies == NULL) {
            perror("Out of memory for movies");
            exit(1);
        }
    }

    p->movies[p->movie_count++] = movie;
}


Series series_new() {
    Series series;

    printf("Enter name for series:\n");
    fgets(series.name, MAX_LEN, stdin);
    series.name[strcspn(series.name, "\n")] = 0;
    fflush(stdin);

    char buf[MAX_LEN];
    int value;
    printf("Enter number of episodes:\n");

retry:
    fgets(buf, MAX_LEN, stdin);
    fflush(stdin);
    if (sscanf(buf, "%d", &value) != 1) {
        fprintf(stderr, "Please enter a number!\n");
        goto retry;
    } else {
        series.episodes = value;
    }

    series.state = Unwatched;
    return series;
}

void series_print(Series series) {
    printf("\tSeries name: %s\n", series.name);
    printf("\tEpisodes: %d\n", series.episodes);
    printf("\tState: %s\n", watch_state_to_string(series.state));
}

Series* series_get(Profile* p, const char* name) {
    for (int i = 0; i < p->series_count; i++) {
        if (strcmp(p->series[i].name, name) == 0) {
            return &p->series[i];
        }
    }

    return NULL;
}

void series_remove(Profile* p, const char* name) {
    for (int i = 0; i < p->series_count; i++) {
        if (strcmp(p->series[i].name, name) == 0) {
            for (int j = i; j < p->series_count - 1; j++) {
                p->series[j] = p->series[j + 1];
            }

            p->series_count--;
            return;
        }
    }

    fprintf(stderr, "Series not found.");
    return;
}

void series_add(Profile* p, Series series) {
    if (p->series_cap <= p->series_count) {
        int cap = p->series_cap;
        p->series_cap = cap < 8 ? 8 : cap * 2;
        p->series = realloc(p->series, p->series_cap * sizeof(Series));
        if (p->series == NULL) {
            perror("Out of memory for series");
            exit(1);
        }
    }

    p->series[p->series_count++] = series;
}

void wait_for_key() {
    printf("Press any key to go back.\n");
    __getch();
}

Profile* new_profile() {
    clrscr();
    Profile* p = malloc(sizeof(Profile));
    if (p == NULL) {
        perror("Out of memory for profile");
        exit(1);
    }

    GREEN();
    center_text("New Profile.\n\n");
    RESET();

    printf("Enter a username to use for the profile.\n");
    fgets(p->uname, MAX_LEN, stdin);
    p->uname[strcspn(p->uname, "\n")] = 0;

    fflush(stdin);

    /* Both `movies` and `series` start off completely empty. */
    p->movies = NULL;
    p->movie_count = 0;
    p->movie_cap = 0;

    p->series = NULL;
    p->series_count = 0;
    p->series_cap = 0;

    printf("Profile created.\n");
    wait_for_key();
    return p;
}

/* Print out the stuff in a profile. */
void show_profile(Profile* profile) {
    RED();
    printf("PROFILE:\n");
    RESET();

    printf("Name: %s\n", profile->uname);

    printf("Movies in list: ");
    if (profile->movie_count == 0) {
        printf("none\n");
    } else {
        printf("\n");
        for (int i = 0; i < profile->movie_count; i++) {
            movie_print(profile->movies[i]);
        }
    }

    printf("Series in list: ");
    if (profile->series_count == 0) {
        printf("none\n");
    } else {
        printf("\n");
        for (int i = 0; i < profile->series_count; i++) {
            series_print(profile->series[i]);
        }
    }
}

void reset_profile(Profile* profile) {
    if (profile->movies != NULL) {
        free(profile->movies);
        profile->movies = NULL;
        profile->movie_cap = 0;
        profile->movie_count = 0;
    }

    if (profile->series != NULL) {
        free(profile->series);
        profile->series = NULL;
        profile->series_cap = 0;
        profile->series_count = 0;
    }
}

/* Read the profile from a file. */
Profile* get_profile() {
    Profile* profile = malloc(sizeof(Profile));
    if (profile == NULL) {
        perror("Out of memory for profile");
        exit(1);
    }
    FILE* f = fopen("profile.bin", "r");
    if (f == NULL) {
        // Profile does not exist / failed to open.
        return NULL;
    }

    /* Read basic data like the username, number of movies and number of series.
     * We'll need the two numbers while malloc-ing to allocate exactly the
     * right amount of memory. */
    fread(&profile->uname, sizeof(profile->uname), 1, f);
    fread(&profile->movie_count, sizeof(profile->movie_count), 1, f);
    fread(&profile->series_count, sizeof(profile->series_count), 1, f);

    /* Set the capacity for the movie and series arrays to some safe number. */
    profile->movie_cap = profile->movie_count * 2;
    profile->series_cap = profile->series_count * 2;

    /* Bunch of mallocs */
    profile->movies = malloc(sizeof(Movie) * profile->movie_cap);
    for (int i = 0; i < profile->movie_count; i++) {
        fread(&profile->movies[i], sizeof(Movie), 1, f);
    }

    profile->series = malloc(sizeof(Series) * profile->series_cap);
    for (int i = 0; i < profile->series_count; i++) {
        fread(&profile->series[i], sizeof(Series), 1, f);
    }

    fclose(f);
    return profile;
}

/* Save the profile to a file. */
void save_profile(Profile* profile) {
    FILE* f = fopen("profile.bin", "w");
    if (f == NULL) {
        perror("Failed to save profile");
        exit(1);
    }

    // Write basic data
    fwrite(&profile->uname, sizeof(profile->uname), 1, f);
    fwrite(&profile->movie_count, sizeof(profile->movie_count), 1, f);
    fwrite(&profile->series_count, sizeof(profile->series_count), 1, f);

    // write movies
    for (int i = 0; i < profile->movie_count; i++) {
        fwrite(&profile->movies[i], sizeof(Movie), 1, f);
    }

    // write series
    for (int i = 0; i < profile->series_count; i++) {
        fwrite(&profile->series[i], sizeof(Series), 1, f);
    }

    fclose(f);
}

/* Free all of the arrays allocated. Don't want memory leaks, yknow? */
void cleanup(Profile* profile) {
    if (profile->movies != NULL) {
        free(profile->movies);
        profile->movies = NULL;
    }

    if (profile->series != NULL) {
        free(profile->series); 
        profile->series = NULL;
    }
}

void print_header() {
    GREEN();
    center_text("Watchlist.\n");
    RESET();
    center_text("====================\n");
}

void print_menu() {
    printf("\t[1] View your profile\n");
    printf("\t[2] Add a movie\n");
    printf("\t[3] Add a series\n");
    printf("\t[4] Find and modify a movie or series\n");
    printf("\t[5] Reset the profile\n");
    printf("\t[6] Exit\n");
}

void print_movie_modification_menu() {
    printf("\t[1] Change name\n");
    printf("\t[2] Change the watched state\n");
    printf("\t[3] Remove movie from the list\n");
    printf("\t[4] Go back\n");
}

void print_series_modification_menu() {
    printf("\t[1] Change name\n");
    printf("\t[2] Change number of episodes\n");
    printf("\t[3] Change the watched state\n");
    printf("\t[4] Remove series from the list\n");
    printf("\t[5] Go back\n");
}

void modify_movie(Profile* profile, Movie* movie) {
    clrscr();
    print_header();
    movie_print(*movie);
    print_movie_modification_menu();

    while (true) {
        if (__kbhit()) {
            int key = __getch();

            switch (key) {
                case 49: { // 1
                    clrscr();
                    printf("Enter a new name.\n");
                    printf("%s --> ", movie->name);

                    fgets(movie->name, MAX_LEN, stdin);
                    movie->name[strcspn(movie->name, "\n")] = 0;

                    printf("Name changed.\n");
                    wait_for_key();
                    fflush(stdin);
                    break;
                }
                case 50: { // 2
                    clrscr();
                    movie->state = get_state();
                    printf("%s is now set as %s.\n",
                            movie->name, watch_state_to_string(movie->state));
                    wait_for_key();
                    break;
                } 
                case 51: { // 3
                    clrscr();
                    movie_remove(profile, movie->name);
                    printf("%s removed.\n", movie->name);
                    wait_for_key();
                    return;
                }
                case 52: return; // 4
                default: {
                    fprintf(stderr, "Invalid option. Try again!\n");
                    wait_for_key();
                    break;
                }
            }

            clrscr();
            print_header();
            movie_print(*movie);
            print_movie_modification_menu();
        }
    }
}

void modify_series(Profile* profile, Series* series) {
    clrscr();
    print_header();
    series_print(*series);
    print_series_modification_menu();

    while (true) {
        if (__kbhit()) {
            int key = __getch();

            switch (key) {
                case 49: { // 1: Change the name
                    clrscr();
                    printf("Enter a new name.\n");
                    printf("%s --> ", series->name);

                    fgets(series->name, MAX_LEN, stdin);
                    series->name[strcspn(series->name, "\n")] = 0;

                    printf("Name changed.\n");
                    wait_for_key();
                    fflush(stdin);
                    break;
                }
                case 50: { // 2: Change the number of episodes
                    clrscr();
                    printf("Enter the new number of episodes.\n");
                    printf("%d --> ", series->episodes);

                    char buf[MAX_LEN];
                    int value;
retry:
                    fgets(buf, MAX_LEN, stdin);
                    if (sscanf(buf, "%d", &value) != 1) {
                        fprintf(stderr, "Please enter a number!\n");
                        goto retry;
                    }
                    series->episodes = value;

                    printf("Number of episodes changed.\n");
                    wait_for_key();
                    fflush(stdin);
                    break;
                } 
                case 51: { // 3: Toggle the watched state
                    clrscr();
                    series->state = get_state();
                    printf("%s is now set as %s.\n",
                            series->name, watch_state_to_string(series->state));
                    wait_for_key();
                    break;
                }
                case 52: { // 4: Remove series
                    clrscr();
                    series_remove(profile, series->name);
                    printf("%s removed.\n", series->name);
                    wait_for_key();
                    return;
                }
                case 53: return; // 5: Go back
                default: {
                    fprintf(stderr, "Invalid option. Try again!\n");
                    wait_for_key();
                    break;
                }
            }

            clrscr();
            print_header();
            series_print(*series);
            print_series_modification_menu();
        }
    }
}

void open_menu(Profile* profile) {
    clrscr();
    print_header();
    print_menu();

    while (true) {
        /* If a key was pressed, handle it. */
        if (__kbhit()) {
            int key = __getch();
            fflush(stdin);
            clrscr();
            switch (key) {
                /* Checking the ASCII values. */
                case 49: { // 1
                    show_profile(profile);
                    wait_for_key();
                    fflush(stdin);
                    break;
                }
                case 50: { // 2
                    movie_add(profile, movie_new());
                    printf("Movie added.\n");
                    wait_for_key();
                    fflush(stdin);
                    break;
                }
                case 51: { // 3
                    series_add(profile, series_new());
                    printf("Series added.\n");
                    wait_for_key();
                    fflush(stdin);
                    break; 
                }
                case 52: { // 4
                    char query[MAX_LEN];
                    printf("Enter the movie or series to look for:\n");
                    fgets(query, MAX_LEN, stdin);
                    query[strcspn(query, "\n")] = 0;
                    
                    Movie* found_movie = movie_get(profile, query);
                    if (found_movie != NULL) {
                        printf("Found a movie with the provided name:\n");
                        modify_movie(profile, found_movie);
                        goto search_done;
                    }

                    Series* found_series = series_get(profile, query);
                    if (found_series != NULL) {
                        printf("Found a series with the provided name:\n");
                        modify_series(profile, found_series);
                        goto search_done;
                    }

                    fprintf(stderr, "Nothing found with that name.\n");
                    wait_for_key();
search_done:
                    fflush(stdin);
                    break;
                }
                case 53: { // 5
                    reset_profile(profile);
                    printf("Profile has been reset.\n");
                    wait_for_key();
                    fflush(stdin);
                    break;
                }
                case 54: // 6
                    return;
                default: {
                    fprintf(stderr, "Invalid key! Try again.\n");
                    wait_for_key();
                    fflush(stdin);
                    break;
                }
            }
            clrscr();
            print_header();
            print_menu();
        }
    }
}

int main(void) {
    Profile* p = get_profile();
    if (p == NULL) {
        center_text("No profile found. Create one? (y/n)\n");
        char choice;
retry:
        choice = __getch();

        if (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
            printf("Please enter y or n.\n");
            fflush(stdin);
            goto retry;
        }

        if (choice == 'y' || choice == 'Y') {
            p = new_profile();
        } else {
            printf("Exiting..\n");
            return 0;
        }
    }

    open_menu(p);
    save_profile(p);

    cleanup(p);

    return 0;
}
