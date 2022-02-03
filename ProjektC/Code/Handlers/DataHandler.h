//
//  DataHandler.h
//  ProjektC
//
//  Created by Hubert Kulpaczyński on 06/01/2022.
//

#ifndef DataHandler_h
#define DataHandler_h

#include <stdio.h>
#include <stdlib.h>
#include "Vector.h"

#define ARRAY_SIZE 50000

struct Events{
    int Size;
    vector Array;
};

struct Day{ // od 01-01-1970 do 01-01-2100 = 47 483 DNI
    int Event_Number;
    int Value;
    
};

struct Days{
    struct Day Array;
};

struct User{
    char* Name;
    struct Events Events;
    vector Array[ARRAY_SIZE];
    
};

struct User InitUser(void);
struct User ReadFiles(char* Path);

#endif /* DataHandler_h */
