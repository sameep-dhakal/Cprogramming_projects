#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct WeatherData {
    char city[50];
    float temperature;
    float humidity;
    float pressure;
};

void saveWeatherData(struct WeatherData *data, int count, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fwrite(data, sizeof(struct WeatherData), count, file);

    fclose(file);
}

void loadWeatherData(struct WeatherData **data, int *count, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    *count = file_size / sizeof(struct WeatherData);
    *data = (struct WeatherData *)malloc(file_size);

    fread(*data, sizeof(struct WeatherData), *count, file);

    fclose(file);
}

void searchWeatherData(const struct WeatherData *data, int count, const char *city) {
    printf("Search results for city '%s':\n", city);
    int found = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(data[i].city, city) == 0) {
            printf("City: %s\n", data[i].city);
            printf("Temperature: %.2f\n", data[i].temperature);
            printf("Humidity: %.2f\n", data[i].humidity);
            printf("Pressure: %.2f\n\n", data[i].pressure);
            found = 1;
        }
    }

    if (!found) {
        printf("City not found.\n\n");
    }
}

int compareByCity(const void *a, const void *b) {
    return strcmp(((struct WeatherData *)a)->city, ((struct WeatherData *)b)->city);
}

void sortWeatherData(struct WeatherData *data, int count) {
    qsort(data, count, sizeof(struct WeatherData), compareByCity);
}

int main() {
    int numEntries = 3;
    struct WeatherData *weatherArray = (struct WeatherData *)malloc(numEntries * sizeof(struct WeatherData));

    for (int i = 0; i < numEntries; i++) {
        printf("Enter weather data for city %d:\n", i + 1);
        printf("City: ");
        scanf("%s", weatherArray[i].city);
        printf("Temperature: ");
        scanf("%f", &weatherArray[i].temperature);
        printf("Humidity: ");
        scanf("%f", &weatherArray[i].humidity);
        printf("Pressure: ");
        scanf("%f", &weatherArray[i].pressure);
    }

    // Save weather data to file
    saveWeatherData(weatherArray, numEntries, "./weather_data.dat");

    // Free the memory allocated for weatherArray
    free(weatherArray);

    // Load weather data from file
    struct WeatherData *loadedData;
    int loadedCount;
    loadWeatherData(&loadedData, &loadedCount, "./weather_data.dat");

    int choice;
    char searchCity[50];

    while (1) {
        printf("Weather Detection System Menu:\n");
        printf("1. Search for weather data by city\n");
        printf("2. Sort and display weather data by city\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter city name to search: ");
                scanf("%s", searchCity);
                searchWeatherData(loadedData, loadedCount, searchCity);
                break;
            case 2:
                sortWeatherData(loadedData, loadedCount);
                printf("Weather Data Sorted by City:\n");
                for (int i = 0; i < loadedCount; i++) {
                    printf("City: %s\n", loadedData[i].city);
                    printf("Temperature: %.2f\n", loadedData[i].temperature);
                    printf("Humidity: %.2f\n", loadedData[i].humidity);
                    printf("Pressure: %.2f\n\n", loadedData[i].pressure);
                }
                break;
            case 3:
                free(loadedData);
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
