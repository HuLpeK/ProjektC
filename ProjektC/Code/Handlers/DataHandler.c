/// Projekt Programistyczny System Zarządzania Budżetem Studenta
/// Autor: Hubert Kulpaczyński 330840
/// Uczelnia: Instytut Informatyki Uniwerstytetu Wrocławskiego

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
                
            for(int j = 0; j < VECTOR_SIZE(Wybraniec->Dzien[i]); j++)
            {
               struct Wydatek* Wydateczek = VECTOR_GET(Wybraniec->Dzien[i], struct Wydatek*, j);
                fprintf(fp, "%d %d#%lf;\n",i, Wydateczek->ID, Wydateczek->koszt);
            }
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
        
    
    while(1)
    {
        int* dzien = (int*)malloc(sizeof(int));
        int* ID = (int*)malloc(sizeof(int));
        double* koszt = (double*)malloc(sizeof(double));
        fscanf(fp, "%d %d#%lf;\n", dzien, ID, koszt);
        if(feof(fp))
        {
            free(dzien);
            free(ID);
            free(koszt);
            break;
        }
            
        struct Wydatek* Wydateczek = (struct Wydatek*)malloc(sizeof(struct Wydatek));
        Wydateczek->ID = *ID;
        Wydateczek->koszt = *koszt;
        VECTOR_ADD(wybraniec.Dzien[*dzien], Wydateczek);
        
    }
    
    
    fclose(fp);
    
    return  wybraniec;
}

void Wypisz_Wydatki(struct Uzytkownik Wybraniec, int START, int KONIEC)
{
    for(int i = START; i <= KONIEC; i++)
    {
        for(int j = 0; j < VECTOR_SIZE(Wybraniec.Dzien[i]); j++)
        {
            Date Datka = UnixToDate(i);
            struct Wydatek* Wydateczek = VECTOR_GET(Wybraniec.Dzien[i], struct Wydatek*, j);
            char* Evencik = VECTOR_GET(Wybraniec.Events.Array , char*, Wydateczek->ID);
            char pomocnik[256];
            strcpy(pomocnik, Evencik);
            pomocnik[strlen(pomocnik)-1] = '\0';
            char Miesiac[3];
            char Dzien[3];
            
            Miesiac[0] = (char)Datka.Miesiac/10+'0';
            Miesiac[1] = (char)Datka.Miesiac%10+'0';
            Miesiac[2] = '\0';
            
            Dzien[0] = (char)Datka.Dzien/10+'0';
            Dzien[1] = (char)Datka.Dzien%10+'0';
            Dzien[2] = '\0';
            
            printf("%d-%s-%s  %5s  %.2fzł\n", Datka.Rok, Miesiac, Dzien, pomocnik, Wydateczek->koszt);
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
    
    for(int i = 0; i < VECTOR_SIZE(Wybraniec.Events.Array); i++)
    {
        char* pomocnik = VECTOR_GET(Wybraniec.Events.Array, char*, i);
        if(strcmp(tmp, pomocnik) == 0)
        {
            *A = Wybraniec;
            free(tmp);
            return;
        }
    }
          
    VECTOR_ADD(Wybraniec.Events.Array, tmp);
    
    SaveFiles(&Wybraniec, Path);
    
    *A = Wybraniec;
}


void Dodaj_Wydatek(struct Uzytkownik* A, char Path[], int CYKL, int INTERVAL)
{
    struct Uzytkownik Wybraniec = *A;
    system("clear");
    
    printf("Podaj Date w której chcesz dodać wydatek:\nRRRR-MM-DD\n");
    
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
    double pomoc;
    scanf("%lf", &pomoc);
    
    Wydateczek->koszt = pomoc;
        
    for(int i = 0; i < VECTOR_SIZE(Wybraniec.Events.Array); i++)
        printf("[%d]: %s",i, VECTOR_GET(Wybraniec.Events.Array, char*, i));
    
    printf("Podaj ID wydatku któremu chcesz przypisać nowy Zmianę\n");
    
    int pomoc1;
    scanf("%d", &pomoc1);
    if(pomoc1 < 0 || pomoc1 >= VECTOR_SIZE(Wybraniec.Events.Array))
    {
        printf("Blad ID jest spoza zakresu!\n");
        free(Wydateczek);
        return;
    }
    Wydateczek->ID = pomoc1;
   
    for(int i = 0; i < CYKL; i++)
    {
        VECTOR_ADD(Wybraniec.Dzien[Dzionek], Wydateczek);
        Dzionek += INTERVAL;
    }
    SaveFiles(&Wybraniec, Path);
    
    *A = Wybraniec;
}

void Usun_Wydatek(struct Uzytkownik* Wybraniec, char Path[])
{
    system("clear");
    printf("Podaj Datę w której chcesz usunąć:\nRRRR-MM-DD\n");
    Date Datka;
    scanf("%d-%d-%d", &Datka.Rok, &Datka.Miesiac, &Datka.Dzien);
    
    int Dzionek = DateToUnix(Datka);
    
    for(int i = 0; i < VECTOR_SIZE(Wybraniec->Dzien[Dzionek]); i++)
    {
        struct Wydatek* X = VECTOR_GET(Wybraniec->Dzien[Dzionek], struct Wydatek*, i);
        char* Evencik = VECTOR_GET(Wybraniec->Events.Array , char*, X->ID);
        
        char pomocnik[256];
        strcpy(pomocnik, Evencik);
        pomocnik[strlen(pomocnik)-1] = '\0';
        
        printf("[%d] %s: %.2lfzł\n", i, pomocnik, X->koszt);
    }
    
    printf("Podaj numer wydatku który chcesz usunąc:\n");
    
    int D;
    scanf("%d", &D);
    
    VECTOR_DELETE(Wybraniec->Dzien[Dzionek], D);
    SaveFiles(Wybraniec, Path);
    
}

void Zestawienie(struct Uzytkownik* Wybraniec, char Path[], int START, int KONIEC,const int stan)
{
    FILE* fp;
    char user_path[strlen(Path)+strlen(Wybraniec->Name)+strlen("Events")+2];
    strcpy(user_path,Path);
    strcat(user_path, Wybraniec->Name);
    strcat(user_path, "/");
    
    char used_path[strlen(Path)+strlen(Wybraniec->Name)+strlen("Events")+2];

    strcpy(used_path, user_path);
    strcat(used_path, "Zestawienie.txt");
    
    if(stan == 0)
        fp = stdout;
    if(stan == 1)
    {
        fp = fopen(used_path, "w");
        
        if(fp == NULL)
        {
            printf("Blad Generalnei Zestawienia\n");
            int timeout = 5;
            while(timeout--)
            {
                printf("Powrót za %d", timeout);
                sleep(1);
            }
        }
    }
    if(stan != 0 && stan != 1)
        return;
    
    for(int i = START; i <= KONIEC; i++)
    {
        for(int j = 0; j < VECTOR_SIZE(Wybraniec->Dzien[i]); j++)
        {
            struct Wydatek* Wydateczek = VECTOR_GET(Wybraniec->Dzien[i], struct Wydatek*, j);
            char* Evencior = VECTOR_GET(Wybraniec->Events.Array, char*, Wydateczek->ID);
            char pomocnik[256];
            strcpy(pomocnik, Evencior);
            pomocnik[strlen(pomocnik)-1] = '\0';
            
            Date Datka = UnixToDate(i);
            char Miesiac[3];
            char Dzionek[3];
            
            Miesiac[0] = Datka.Miesiac/10+'0';
            Miesiac[1] = Datka.Miesiac%10+'0';
            Miesiac[2] = '\0';
            
            Dzionek[0] = Datka.Dzien/10+'0';
            Dzionek[1] = Datka.Miesiac%10+'0';
            Dzionek[2] = '\0';
            
            fprintf(fp, "%d-%s-%s:%s:%.2lfzł\n", Datka.Rok, Miesiac, Dzionek, pomocnik, Wydateczek->koszt);
        }
    }
    if(stan != 0)
        fclose(fp);
    
    
    if(stan == 0)
    {
        printf("<Kliknij Cokolwiek By Wrócić>\n");
        char ch;
        scanf("\n%c", &ch);
    }
    
    if(stan == 1)
    {
        printf("Wygenerowanie zestawienie do pliku: %s\n", used_path);
        int TIMEOUT = 5;
        while (TIMEOUT--) {
            printf("Powrót za %d!\n", TIMEOUT);
            sleep(1);
        }
        return;
    }

    
}

double Suma_Wydatki(struct Uzytkownik* Wybraniec, int START, int KONIEC)
{
    double SUMA = 0;
    
    for(int i = START; i <= KONIEC; i++)
    {
        for(int j = 0; j < VECTOR_SIZE(Wybraniec->Dzien[i]); j++)
        {
            struct Wydatek* Wydateczek = VECTOR_GET(Wybraniec->Dzien[i], struct Wydatek*, j);
            SUMA += Wydateczek->koszt;
        }
    }
    
    return SUMA;
}
