#include<stdio.h> 
#include <stdlib.h> 
#include <time.h>  
// Array of positive quotes 
const char *positiveQuotes[] = {
    "We grow through what we go through.",
    "Every wave of life reach us for a reason",
    "If it make you happy iy does not have to make sense to others",
    "Believe in yourself and all that you are.",   
    "You are capable of amazing things.",     
    "Your positive actions will lead to positive outcomes.",    
    "Every day is a new beginning.",   
    "The present moment is all you ever have",
    "You are strong, you are brave, you are enough.", 
    "Happiness is a choice.",    
   "You are the artist of your own life.",   
   "You have the power to make it a great day.",     
   "All things great are wound up with all things little." };

  int main() {    
           srand(time(NULL)); 
              int numQuotes = sizeof(positiveQuotes) / sizeof(positiveQuotes[0]); 
           int randomIndex = rand() % numQuotes;      
              printf("Positive Quote of the Day:\n%s\n", positiveQuotes[randomIndex]);  
              return 0; 
}