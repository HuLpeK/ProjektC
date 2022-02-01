//
//  CreateFileHandler.c
//  ProjektC
//
//  Created by Hubert Kulpaczyński on 08/01/2022.
//

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
    FILE* fp = fopen(pom, "w+");
    
    if(fp == NULL)
    {
        printf("Blad Tworzenia Pliku %s\n", pom);
        rmdir(Path);
        exit(0);
    }
    char* tab[] = {"15", "Zakupy", "Kieszonkowe", "Czynsz", "Wynagrodzenie z Pracy", "Kosmetyki", "Paliwo", "Kino", "Ubrania", "Książki", "Abonament", "Internet", "Spotify", "Netflix", "Urbankart", "Bilety Komunikacji Społecznej"};
    
    for(int i = 0; i <= atoi(tab[0]); i++)
        fprintf(fp, "%s;", tab[i]);
    
    fclose(fp);
}