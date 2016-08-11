//
//  main.c
//  Safecracker
//
//  Created by Rodney Sampson on 8/10/16.
//  Copyright © 2016 Rodney Sampson II. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "SafeFunctions.h"

void start(void);

int getASCIIValue();

int main(int argc, const char * argv[]) {
    
    start();
    
    return 0;
}

void start() {
    
    char userInput[50] = "\0";
    char * userName = "\0";
    
    int safeCode[] = {arc4random_uniform(4), arc4random_uniform(4), arc4random_uniform(4), arc4random_uniform(4)};
    int userSafeCodeGuess[4][4];
    
    int numberOfItemsScanned = 0;
    int timesGuessed = 0;
    
    char * guesses[4][4];
    
    //  V get rid of this
    for (int i = 0; i < 4; i++) {
        printf("%d\n", safeCode[i]);
    }
    // ^ get rid of this
    
    printf("Welcome to Safecracker! The game where you are a cat burgular trying to break into a safe. \n\nGuess the code before the cops show up. The numbers are only between 0 and 3.\n\n");
    
    while (numberOfItemsScanned != 1) {
        fpurge(stdin);
        printf("What is your robbers's name?\n\n");
        numberOfItemsScanned = scanf("%[^\n]", userInput);
        printf("\n");
    }
    
    numberOfItemsScanned = 0;
    userName = userInput;
    
    printf("Lets get cracking!\n");
    
    while (timesGuessed < 3) {
        fpurge(stdin);
        printf("\nEnter all of the numbers for your guess with a forward slash between each single digit:\n\n");
        numberOfItemsScanned = scanf("%d/%d/%d/%d", &userSafeCodeGuess[timesGuessed][0], &userSafeCodeGuess[timesGuessed][1], &userSafeCodeGuess[timesGuessed][2], &userSafeCodeGuess[timesGuessed][3]);
        
        if (numberOfItemsScanned == 4) {
            
            if (compareCodes(safeCode, userSafeCodeGuess, timesGuessed)) {
                printf("\n%s, you get away scot free. The safe code was %d %d %d %d just like you thought.\n\n", userName, safeCode[0], safeCode[1], safeCode[2], safeCode[3]);
                break;
            } else if(!compareCodes(safeCode, userSafeCodeGuess, timesGuessed)) {
                if (timesGuessed == 2) {
                    printf("\n%s, you were sentenced 25 years to life. \n\nThe code was %d %d %d %d but you guessed %d %d %d %d.\n\n", userName, safeCode[0], safeCode[1], safeCode[2], safeCode[3], userSafeCodeGuess[timesGuessed][0], userSafeCodeGuess[timesGuessed][1], userSafeCodeGuess[timesGuessed][2], userSafeCodeGuess[timesGuessed][3]);
                    break;
                } else {
                    printf("\nYou did not guess the right code for the safe.\n\n");
                    
                    int percentage = 0;
                    
                    for (int i = 0; i < 4; i++) {
                        if (userSafeCodeGuess[timesGuessed][i] == safeCode[i]) {
                            percentage++;
                        }
                    }
                    
                    printf("You got %d/4 of the number right", percentage);
                    
                    char choice = '0';
                    printf("\n\nType 't' to try again, 'p' to print your past guesses or 'c' to close the game.\n\n");
                    fpurge(stdin);
                    scanf("%c", &choice);
                    
                    if (choice == (int)'t') {
                        printf("\n%d try(s) left\n", 3 - (timesGuessed + 1));
                        timesGuessed++;
                    } else if(choice == (int)'p') {
                        
                        printf("\n| guess %d : %s %s %s %s |\n\n", timesGuessed + 1, guesses[timesGuessed][0], guesses[timesGuessed][1], guesses[timesGuessed][2], guesses[timesGuessed][3]);
                        
                    } else if(choice == (int)'c') {
                        sleep(1);
                        printf("\nclosing...\n\n");
                        sleep(1);
                        break;
                    } else {
                        printf("\n%d try(s) left\n", 3 - (timesGuessed + 1));
                        timesGuessed++;
                    }
                }
            }
        } else {
            continue;
        }
        
    }
}
