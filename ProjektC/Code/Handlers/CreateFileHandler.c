/// Projekt Programistyczny System Zarządzania Budżetem Studenta
/// Autor: Hubert Kulpaczyński 330840
/// Uczelnia: Instytut Informatyki Uniwerstytetu Wrocławskiego

#include "CreateFileHandler.h"


void DelFile_User(char Path[])
{
    char X[strlen(Path)];
    strcpy(X, "rm -r ");
    strcat(X, Path);
    system(X);
}

void CreateFile_Events(char Path[])
{
    char pom[strlen(Path)];
    strcpy(pom, Path);
    strcat(pom, "Events");
    FILE* fp = fopen(pom, "a+");
    
    if(fp == NULL)
    {
        printf("Blad Tworzenia Pliku %s\n", pom);
        rmdir(Path);
        exit(0);
    }
    
    char* tab[] = {"15", "Zakupy", "Kieszonkowe", "Czynsz", "Wynagrodzenie z Pracy", "Kosmetyki", "Paliwo", "Kino", "Ubrania", "Książki", "Abonament", "Internet", "Spotify", "Netflix", "Urbankarta", "Bilety Komunikacji Społecznej"};
    
    for(int i = 1; i <= atoi(tab[0]); i++)
        fprintf(fp, "%s\n", tab[i]);
    
    fclose(fp);
}

void CreateFile_Date(char Path[])
{
    char pom[strlen(Path)];
    strcpy(pom, Path);
    strcat(pom, "Date");
    FILE* fp = fopen(pom, "a+");
    
    if(fp == NULL)
    {
        printf("Blad Tworzenia Pliku %s\n", pom);
        rmdir(Path);
        exit(0);
    }
    
    fclose(fp);
}

void CreateFiles(char Path[])
{
    CreateFile_Events(Path);
    CreateFile_Date(Path);
}
