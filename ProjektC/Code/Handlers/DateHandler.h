/// Projekt Programistyczny System Zarządzania Budżetem Studenta
/// Autor: Hubert Kulpaczyński 330840
/// Uczelnia: Instytut Informatyki Uniwerstytetu Wrocławskiego

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

Date UnixToDate(int Dni);
int DateToUnix(Date Data);
int CheckDate(Date Data);
#endif /* DataHandler_h */
