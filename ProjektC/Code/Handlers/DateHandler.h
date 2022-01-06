//
//  DataHandler.h
//  ProjektC
//
//  Created by Hubert Kulpaczyński on 06/01/2022.
//

#ifndef DataHandler_h
#define DataHandler_h

#include <stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Dejt
{
    int Rok;
    int Miesiac;
    int Dzien;
} Dejt;

bool isLeap(int year);

Dejt DataToUnix(int Dni);


#endif /* DataHandler_h */
