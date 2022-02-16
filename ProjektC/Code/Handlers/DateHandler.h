//
//  DataHandler.h
//  ProjektC
//
//  Created by Hubert Kulpaczyński on 06/01/2022.
//

#ifndef DateHandler_h
#define DateHandler_h

#include <stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Date
{
    int Rok;
    int Miesiac;
    int Dzien;
} Date;

bool isLeap(int year);

Date UnixToData(int Dni);
int DataToUnix(Date Data);
int CheckDate(Date Data);
#endif /* DataHandler_h */
