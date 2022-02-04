//
//  DataHandler.c
//  ProjektC
//
//  Created by Hubert Kulpaczyński on 06/01/2022.
//

#include "DataHandler.h"

struct Uzytkownik InitUser()
{
    struct Uzytkownik wybaraniec;
    
    for(int i = 0; i < ARRAY_SIZE; i++)
        vector_init(&wybaraniec.Array[i]);
    
    vector_init(&wybaraniec.Events.Array);
    
    return wybaraniec;
}

struct Uzytkownik ReadFiles(char* Path)
{
    struct Uzytkownik wybraniec = InitUser();
    
    char help[strlen(Path)+15];
    
    strcpy(help, Path);
    strcat(help, "Events");
    
    FILE* fp = fopen(help, "r");
    if(fp == NULL)
    {
        printf("Blad Wczytywania pliku %s\n", help);
        return wybraniec;
    }
    
    while(1)
    {
        char* tmp = (char*)calloc(256,sizeof(char));
        if(fgets(tmp, 256, fp) == NULL)
            break;
        VECTOR_ADD(wybraniec.Events.Array, tmp);
    }
    
    return  wybraniec;
}

void Wypisz_Events(struct Uzytkownik Wybraniec)
{
    system("clear");
    
    
    for(int i = 0; i < VECTOR_SIZE(Wybraniec.Events.Array); i++)
        printf("[%d] %s", i,VECTOR_GET(Wybraniec.Events.Array, char*, i));

    printf("<Kliknij Cokolwiek By Wrócić>\n");
    char ch;
    scanf("\n%c", &ch);
    
}

void ZmienNazwe_Events(struct Uzytkownik Wybraniec)
{
    system("clear");

    printf("Użytkownik: %s\n", Wybraniec.Name);
    
    printf("Wybierz Zdefiniowany wydatek którego nazwe chcesz zmienić:\n");
    
    for(int i = 0; i < VECTOR_SIZE(Wybraniec.Events.Array); i++)
        printf("[%d] %s", i,VECTOR_GET(Wybraniec.Events.Array, char*, i));
    
    int wybor;
    scanf("%d", &wybor);
    
    while(wybor < 0 || wybor >= VECTOR_SIZE(Wybraniec.Events.Array))
    {
        printf("Błąd Podaj Liczbe z zakresu!\n %d-%d\n", 0, VECTOR_SIZE(Wybraniec.Events.Array)-1);
        scanf("%d", &wybor);
    }
    
    printf("Podaj Nową Nazwe!\n");
    
    char* tmp = (char*)calloc(256,sizeof(char));
    scanf("\n%[^\n]%*c", tmp);
    strcat(tmp, "\n");


    VECTOR_SET(Wybraniec.Events.Array, wybor, tmp);

}

struct Uzytkownik DodajEvent_Events(struct Uzytkownik Wybraniec)
{
    system("clear");
    printf("Użytkownik: %s\n", Wybraniec.Name);
    
    printf("Podaj nazwe nowego zdefiniowanego wydatku:\n");
    
    char* tmp = (char*)calloc(256,sizeof(char));
    scanf("\n%[^\n]%*c", tmp);

    VECTOR_ADD(Wybraniec.Events.Array, tmp);
    
    
    for(int i = 0; i < VECTOR_SIZE(Wybraniec.Events.Array); i++)
        printf("%s", VECTOR_GET(Wybraniec.Events.Array, char*, i));
    
    
    
//    SaveFiles(Wybraniec, sciezka_zapisu);
    
    return Wybraniec;
}
