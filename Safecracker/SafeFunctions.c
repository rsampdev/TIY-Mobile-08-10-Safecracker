//
//  SafeFunctions.c
//  Safecracker
//
//  Created by Rodney Sampson on 8/10/16.
//  Copyright © 2016 Rodney Sampson II. All rights reserved.
//

#include "SafeFunctions.h"

bool compareCodes(int * safeCode, int userCode[4][4], int index) {
    int * sc;
    sc = safeCode;
    
    int * uc;
    uc = userCode[index];
    
    return uc[0] == sc[0] && uc[1] == sc[1] && uc[2] == sc[2] && uc[3] == sc[3];
}
