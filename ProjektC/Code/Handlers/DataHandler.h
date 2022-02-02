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


#define SIZE 50000


struct Events{
    int Size;
    char* Array;
};

struct Day{ // od 01-01-1970 do 01-01-2100 = 47 483 DNI
    int Event_Number;
    int Value;
    
};
#define SIZE 50000
struct Days{
    struct Day Array;
};

struct User{
    char* Name;
    
    struct Events Events;
    struct Days Array[SIZE];
    
};



#endif /* DataHandler_h */
