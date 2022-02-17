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

    //Zapisywanie do pliku Date
    strcpy(used_path, user_path);
    strcat(used_path, "Date");
    fp = fopen(used_path, "w");
    
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        if(VECTOR_SIZE(Wybraniec->Dzien[i]) != 0)
        {
    
//            fprintf(fp, "%d-%d-%d ", Datka.Rok, Datka.Miesiac, Datka.Dzien);
            fprintf(fp, "%d ", i);
            for(int j = 0; j < VECTOR_SIZE(Wybraniec->Dzien[i]); i++)
            {
               struct Wydatek* Wydateczek = VECTOR_GET(Wybraniec->Dzien[i], struct Wydatek*, j);
                fprintf(fp, "%d-%d; ", Wydateczek->ID, Wydateczek->koszt);
            }
//            fprintf(fp, "\n");
        }
        
    }
    
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
    
    fclose(fp);
    
    strcpy(help, Path);
    strcat(help, "Date");
    
    fp = fopen(help, "r");
        
    int dzien = -1;
    while(fscanf(fp, "%d", &dzien))
    {
        if(feof(fp))
            break;
        int* ID = (int*)malloc(sizeof(int));
        int* koszt = (int*)malloc(sizeof(int));
        while(fscanf(fp, " %d-%d;", ID, koszt))
        {
            if(feof(fp))
                break;
            struct Wydatek* Wydateczek = (struct Wydatek*)malloc(sizeof(struct Wydatek));
            Wydateczek->ID = *ID;
            Wydateczek->koszt = *koszt;
            VECTOR_ADD(wybraniec.Dzien[dzien], Wydateczek);
        }
    }
    
    
    fclose(fp);
    
    return  wybraniec;
}

void Wypisz_Wydatki(struct Uzytkownik Wybraniec, int START, int KONIEC)
{
    for(int i = START; i <= KONIEC; i++)
    {
        
//        printf("%d", VECTOR_SIZE(Wybraniec.Dzien[i]));
        for(int j = 0; j < VECTOR_SIZE(Wybraniec.Dzien[i]); j++)
        {
            Date Datka = UnixToDate(i);
            struct Wydatek* Wydateczek = VECTOR_GET(Wybraniec.Dzien[i], struct Wydatek*, j);
            char* Evencik = VECTOR_GET(Wybraniec.Events.Array , char*, Wydateczek->ID);
            char pomocnik[256];
            strcpy(pomocnik, Evencik);
            pomocnik[strlen(pomocnik)-1] = '\0';
            printf("%d-%d-%d: %s %d\n", Datka.Rok, Datka.Miesiac, Datka.Dzien, pomocnik, Wydateczek->koszt);
        }
    }
    
    printf("<Kliknij Cokolwiek By Wrócić>\n");
    char ch;
    scanf("\n%c", &ch);
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


void Dodaj_Wydatek(struct Uzytkownik* A, char Path[])
{
    struct Uzytkownik Wybraniec = *A;
    system("clear");
    
    printf("Podaj Date w której chcesz dodać wydatek: [RRRR-MM-DD]\n");
    
    int Rok,Miesiac,Dzionek;
    Rok = -1; Miesiac = -1; Dzionek = -1;
    scanf("%d-%d-%d", &Rok, &Miesiac, &Dzionek);
          
    Date Data = {Rok,Miesiac,Dzionek};
    if(!CheckDate(Data))
    {
        printf("Błąd podania daty!\n");
        return;
    }
    
    Dzionek = DateToUnix(Data);
    
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
    
    VECTOR_ADD(Wybraniec.Dzien[Dzionek], Wydateczek);
//    SaveFiles(&Wybraniec, Path);
    
    *A = Wybraniec;
}



