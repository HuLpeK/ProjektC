/// Projekt Programistyczny System Zarządzania Budżetem Studenta
/// Autor: Hubert Kulpaczyński 330840
/// Uczelnia: Instytut Informatyki Uniwerstytetu Wrocławskiego

#ifndef DataHandler_h
#define DataHandler_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "./Vector.h"
#include "./DateHandler.h"
#define ARRAY_SIZE 50000

struct Wydatek{
    double koszt;
    int ID;
};

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
    vector Dzien[ARRAY_SIZE];
};

void SaveFiles(struct Uzytkownik* Wybraniec, char Path[]);
struct Uzytkownik InitUser(void);
struct Uzytkownik ReadFiles(char* Path);
void Wypisz_Wydatki(struct Uzytkownik Wybraniec, int START, int KONIEC);
void Wypisz_Events(struct Uzytkownik Wybraniec);
void ZmienNazwe_Events(struct Uzytkownik Wybraniec, char Path[]);
void DodajEvent_Events(struct Uzytkownik* A, char Path[]);
void Dodaj_Wydatek(struct Uzytkownik* A, char Path[], int CYKL, int INTERVAL);
void Usun_Wydatek(struct Uzytkownik* Wybraniec, char Path[]);
void Zestawienie(struct Uzytkownik* Wybraniec, char Path[], int START, int KONIEC, const int stan);
double Suma_Wydatki(struct Uzytkownik* Wybraniec, int START, int KONIEC);
#endif /* DataHandler_h */
