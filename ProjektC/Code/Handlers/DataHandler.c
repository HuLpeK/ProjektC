//
//  DataHandler.c
//  ProjektC
//
//  Created by Hubert Kulpaczyński on 06/01/2022.
//

#include "DataHandler.h"



void SaveFiles(struct Uzytkownik* Wybraniec, char Path[])
{
    char user_path[strlen(Path)+strlen(Wybraniec->Name)+strlen("Events")+2];
    strcpy(user_path,Path);
    strcat(user_path, Wybraniec->Name);
    strcat(user_path, "/");
    
    char used_path[strlen(Path)+strlen(Wybraniec->Name)+strlen("Events")+2];
    //Zapisywanie do pliku Events
    strcpy(used_path, user_path);
    strcat(used_path, "Events");
    FILE* fp = fopen(used_path, "w");
    for(int i = 0; i < VECTOR_SIZE(Wybraniec->Events.Array); i++)
        fprintf(fp, "%s", VECTOR_GET(Wybraniec->Events.Array, char*, i));
    
    fclose(fp);

    
}

struct Uzytkownik InitUser()
{
    struct Uzytkownik wybaraniec;
    
    for(int i = 0; i < ARRAY_SIZE; i++)
        vector_init(&wybaraniec.Dzien[i]);
    
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

void ZmienNazwe_Events(struct Uzytkownik Wybraniec, char Path[])
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
    
    SaveFiles(&Wybraniec, Path);

}

void DodajEvent_Events(struct Uzytkownik* A, char Path[])
{
    struct Uzytkownik Wybraniec = *A;
    system("clear");
    printf("Użytkownik: %s\n", Wybraniec.Name);
    
    printf("Podaj nazwe nowego zdefiniowanego wydatku:\n");
    
    char* tmp = (char*)calloc(256,sizeof(char));
    scanf("\n%[^\n]%*c", tmp);

    strcat(tmp, "\n");
    VECTOR_ADD(Wybraniec.Events.Array, tmp);
    
    
    for(int i = 0; i < VECTOR_SIZE(Wybraniec.Events.Array); i++)
        printf("%s", VECTOR_GET(Wybraniec.Events.Array, char*, i));
    
    SaveFiles(&Wybraniec, Path);
    
    *A = Wybraniec;
}


void Dodaj_Wydatek(struct Uzytkownik Wybraniec, char Path[])
{
    system("clear");
    
    printf("Podaj Date w której chcesz dodać wydatek: [RRRR-MM-DD]\n");
    
    int Rok,Miesiac,Dzien;
    scanf("%d-%d-%d", &Rok, &Miesiac, &Dzien);
          
    Date Data = {Rok,Miesiac,Dzien};
    if(!CheckDate(Data))
    {
        printf("Błąd podania daty!\n");
        return;
    }
    
    Dzien = DateToUnix(Data);
    
    struct Wydatek* Wydateczek = (struct Wydatek*)malloc(sizeof(struct Wydatek));
    
    printf("Podaj Wartość (jeśli to odchód to dodaj minus przed wartościa)\n");
    int pomoc;
    scanf("%d", &pomoc);
    
    Wydateczek->koszt = pomoc;
        
    for(int i = 0; i < VECTOR_SIZE(Wybraniec.Events.Array); i++)
        printf("[%d]: %s",i, VECTOR_GET(Wybraniec.Events.Array, char*, i));
    
    printf("Podaj ID wydatku któremu chcesz przypisać nowy Zmianę\n");
    
    int pomoc1;
    scanf("%d", &pomoc1);
    
    Wydateczek->ID = pomoc1;
    
    
    VECTOR_ADD(Wybraniec.Dzien[Dzien], Wydateczek);
    SaveFiles(&Wybraniec, Path);
}
