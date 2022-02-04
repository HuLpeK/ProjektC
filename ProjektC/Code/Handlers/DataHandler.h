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
#include <string.h>
#include <assert.h>
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

struct Uzytkownik{
    char* Name;
    struct Events Events;
    vector Array[ARRAY_SIZE];
};

struct Uzytkownik InitUser(void);
struct Uzytkownik ReadFiles(char* Path);
void Wypisz_Events(struct Uzytkownik Wybraniec);
void ZmienNazwe_Events(struct Uzytkownik Wybraniec);
struct Uzytkownik DodajEvent_Events(struct Uzytkownik Wybraniec);
#endif /* DataHandler_h */
