//
//  SaveFileHandler.c
//  ProjektC
//
//  Created by Hubert Kulpaczyński on 04/02/2022.
//

#include "SaveFileHandler.h"


void SaveFiles(struct Uzytkownik Wybraniec, char Path[])
{
    char user_path[strlen(Path)+64];
    strcpy(user_path,Path);
    strcat(user_path, Wybraniec.Name);
    strcat(user_path, "/");
    SaveFiles_Events(Wybraniec, user_path);
}


void SaveFiles_Events(struct Uzytkownik Wybraniec, char Path[])
{
    char UsingPath[strlen(Path)+10];
    
    strcpy(UsingPath, Path);
    strcat(UsingPath, "Events");
    
    FILE* fp = fopen(UsingPath, "w");
    
    if(fp == NULL)
    {
        printf("Błąd Dostępu Pliku %s!\n", UsingPath);
        exit(0);
    }
    
    for(int i = 0; i < VECTOR_SIZE(Wybraniec.Events.Array); i++)
        fprintf(fp, "%s", VECTOR_GET(Wybraniec.Events.Array, char*, i));
}

