//
//  SafeFunctions.h
//  Safecracker
//
//  Created by Rodney Sampson on 8/10/16.
//  Copyright © 2016 Rodney Sampson II. All rights reserved.
//

#ifndef SafeFunctions_h
#define SafeFunctions_h

#include <stdio.h>
#include <stdbool.h>

#endif /* SafeFunctions_h */

bool compareCodes(int * safeCode, int userCode[4][4], int index);

int percentageOfCodesAlike(int safeCode[4], int codeGuess[4][4], int index);

void printUserSafeCodeGuess(int codeGuess[4][4], int index);
