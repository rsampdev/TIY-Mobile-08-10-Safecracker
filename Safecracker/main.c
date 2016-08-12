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
#include <limits.h>
#include <math.h>
#include "SafeFunctions.h"

void start(void);

int main(int argc, const char * argv[]) {
    
    start();
    
    return 0;
}

void start() {
    
    char userInput[50] = "\0";
    char * userName = "\0";
    
    int numberOfItemsScanned = 0;
    int guessLimit = 3; // take in user unput to set this
    int timesGuessed = 0;
    
    printf("Welcome to Safecracker!\n\nThe game where you are a burgular trying to break into a safe.\n\nGuess the safe code before the cops show up.\n\nThe safe code is only 4 numbers long and the numbers are only 0 through a max number value that you set.\n\n~Because the person trying to break into the safe always chooses the max number for the code?~\n\n"); // take in user unput to set this
    
    while (numberOfItemsScanned != 1) {
        fpurge(stdin);
        printf("What is your burgular's name?\n\n");
        numberOfItemsScanned = scanf("%[^\n]", userInput);
        printf("\n");
    }
    
    numberOfItemsScanned = 0;
    
    int maxNumberValue = INT_MAX;
    
    while (numberOfItemsScanned != 1) {
        fpurge(stdin);
        printf("What is the max value for a number?\n\n");
        numberOfItemsScanned = scanf("%d", &maxNumberValue);
        printf("\n");
    }
    
    numberOfItemsScanned = 0;
    
    int safeCodeLength = 4;
    int safeCode[4] = {arc4random_uniform(maxNumberValue + 1), arc4random_uniform(maxNumberValue + 1), arc4random_uniform(maxNumberValue + 1), arc4random_uniform(maxNumberValue + 1)};
    int userSafeCodeGuess[guessLimit + 1][4];
    
    userName = userInput;
    numberOfItemsScanned = 0;
    
    printf("Remember if you enter a number larger than the max number value it will be reduced to the max number value.\n\nNow let's get cracking!\n");
    
    while (timesGuessed < guessLimit) {
        fpurge(stdin);
        printf("\nEnter all of the numbers for your guess with a dash between each single digit. Like this: 1-2-3-0\n\n");
        numberOfItemsScanned = scanf("%d %d %d %d", &userSafeCodeGuess[timesGuessed][0], &userSafeCodeGuess[timesGuessed][1], &userSafeCodeGuess[timesGuessed][2], &userSafeCodeGuess[timesGuessed][3]);
        
        for (int i = 0; i < safeCodeLength; i++) {
            if (userSafeCodeGuess[timesGuessed][0] > maxNumberValue) {
                userSafeCodeGuess[timesGuessed][0] = abs(maxNumberValue);
            }
        }
        
        if (numberOfItemsScanned == safeCodeLength) {
            
            if (compareCodes(safeCode, userSafeCodeGuess, timesGuessed)) {
                printf("\n%s, you get away scot free. The safe code was ", userName);
                printUserSafeCodeGuess(userSafeCodeGuess, timesGuessed);
                printf("just like you thought.\n\n");
                break;
            } else if(!compareCodes(safeCode, userSafeCodeGuess, timesGuessed)) {
                if (timesGuessed == 2) {
                    printf("\n%s, you were sentenced 25 years to life. \n\nThe code was %d %d %d %d but you guessed ", userName, safeCode[0], safeCode[1],safeCode[2], safeCode[3]);
                    printUserSafeCodeGuess(userSafeCodeGuess, timesGuessed);
                    break;
                } else {
                    printf("\n%s, you did not guess the right code for the safe.\n\n", userName);
                    printf("%s, you got %d/4 of the numbers right", userName, percentageOfCodesAlike(safeCode, userSafeCodeGuess, timesGuessed));
                    
                    char choice = '0';
                    printf("\n\nType 't' to try again, 'p' to print your past guesses or 'c' to close the game.\n\n");
                    fpurge(stdin);
                    numberOfItemsScanned = scanf("%c", &choice);
                    timesGuessed++;
                    
                    while (numberOfItemsScanned != 1) {
                        if (choice == (int)'t') {
                            printf("\n%d try(s) left\n", guessLimit - (timesGuessed));
                        } else if(choice == (int)'p') {
                            
                            int turnNumber = timesGuessed + 1;
                            
                            while (turnNumber >= timesGuessed) {
                                fpurge(stdin);
                                printf("\nWhich turn do you want your guesses from?\n\n");
                                printf("Type '1' for the first turn, '2' for the second turn and '3' for the third turn.\n\n");
                                numberOfItemsScanned = scanf("%d", &turnNumber);
                                
                                if (turnNumber <= timesGuessed) {
                                    printf("\n| guess %d | %d %d %d %d | %d/4 |\n", timesGuessed + 1, userSafeCodeGuess[turnNumber - 1][0], userSafeCodeGuess[turnNumber - 1][1], userSafeCodeGuess[turnNumber - 1][2], userSafeCodeGuess[turnNumber - 1][3], percentageOfCodesAlike(safeCode, userSafeCodeGuess, turnNumber));
                                } else {
                                    printf("You have not completed that turn yet or that is not a valid turn. Try again.\n\n");
                                    continue;
                                }
                            }
                        } else if(choice == (int)'c') {
                            sleep(1);
                            printf("\nclosing...\n\n");
                            sleep(1);
                            break;
                        } else {
                            printf("\n%d try(s) left\n", guessLimit - (timesGuessed));
                            numberOfItemsScanned = 4;
                        }
                    }
                }
            }
        } else {
            printf("\n");
            start();
            break;
        }
        
    }
}
