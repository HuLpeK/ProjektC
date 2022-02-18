/// Projekt Programistyczny System Zarządzania Budżetem Studenta
/// Autor: Hubert Kulpaczyński 330840
/// Uczelnia: Instytut Informatyki Uniwerstytetu Wrocławskiego

 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "Header.h"

#define TIMEOUT_TIME 5

int START_Header = 0;
char* sciezka_zapisu; //PREFIX do folderu SAVES/




struct Users UsersList;


void INIT(const char* slowo[])
{
    for(int i = 0; slowo[1][i] != '\0'; i++)
        if(slowo[1][i] == '/')
            START_Header = i+1;
    
    
    sciezka_zapisu = realloc(sciezka_zapisu, (START_Header)* sizeof(char));
    
    for(int i = 0; i < START_Header; i++)
        sciezka_zapisu[i] = slowo[1][i];
    
    sciezka_zapisu[START_Header] = '\0';
    
    for(int i = 1; i < UsersList.number_of_users; i++)
    {
        char* help;
        get_user(slowo[i], &help);
        add_user(help, i);
        free(help);
    }
}

void select_menu(void)
{
    while(1)
    {
        system("clear");
        printf("Wybierz użytkownika z listy lub dodaj kolejnego:\n");
        printf("[-1]: <Usuń Użytkownika>\n");
        printf("[0]: <Dodaj Użytkownika>\n");
        for(int i = 1; i < UsersList.number_of_users; i++)
        {
            printf("[%d]: ", i);
            
            printf("%s \n", UsersList.uzytkownicy[i]);
        }

        int wybor;
        scanf("%d", &wybor);
        
        
        if(wybor == -1)
            break;
        
        if(wybor == 0)
            Create_user();
        
        if(wybor >= 1 && wybor <= UsersList.number_of_users)
        {
            Select_User(wybor, UsersList, sciezka_zapisu);
        }
    }
    DelUser_Menu();
}

void WypiszUser(struct Uzytkownik* Wybraniec)
{
    printf("Użytkownik: %s\n", Wybraniec->Name);
}

void add_user(char* user, int index)
{
    if(index >= UsersList.number_of_users)
        UsersList.number_of_users++;
    char* tmp = (char*)calloc(strlen(user), sizeof(char));
    strcpy(tmp,user);
    UsersList.uzytkownicy[index] = tmp;
}


void get_user(const char path[], char** user)
{
    char* help = (char*)calloc(strlen(path)-START_Header, sizeof(char));
    int wskaznik = 0;
    for(int i = START_Header; path[i] != '\0'; i++)
        help[wskaznik++] = path[i];
    *user = help;
}

void DelArr_User(int X)
{
    int size = UsersList.number_of_users;
    for(int i = X; i < size-1; i++)
        strcpy(UsersList.uzytkownicy[i], UsersList.uzytkownicy[i+1]);
    

    UsersList.number_of_users--;
}

void DelUser_Menu(void)
{
    while(1)
    {
        system("clear");
        printf("Podaj Numer Użytkownika Do usunięcia\n");
        printf("[0] <Wroc do Menu>\n");
        for(int i = 1; i < UsersList.number_of_users; i++)
            printf("[%d]: %s\n", i, UsersList.uzytkownicy[i]);
        
        int wybor;
        scanf("%d", &wybor);
        
        if(wybor == 0)
            break;
        else
        {
            char path[strlen(sciezka_zapisu) + strlen(UsersList.uzytkownicy[wybor])];
            strcpy(path, sciezka_zapisu);
            strcat(path, UsersList.uzytkownicy[wybor]);

            DelFile_User(path);
            DelArr_User(wybor);
            select_menu();
        }
    }
}


void Select_User(int index, struct Users UsersList, char* sciezka_zapisu)
{
    char* user = UsersList.uzytkownicy[index];
    char user_path[strlen(sciezka_zapisu) + strlen(user)];
    
    strcpy(user_path, sciezka_zapisu);
    strcat(user_path, user);
    
    char used_path[strlen(user_path)+ strlen(user)];
    
    strcpy(used_path, user_path);
    strcat(used_path, "/");
    
    
    struct Uzytkownik Wybraniec;
    Wybraniec = ReadFiles(used_path);
    Wybraniec.Name = user;
    
    Select_User_Menu(&Wybraniec);
}

void Select_User_Menu(struct Uzytkownik* Wybraniec)
{
    while(1)
    {
        system("clear");
        WypiszUser(Wybraniec);


        
        printf("[-1] Wróć\n");
        printf("[0] Menu Wydatków\n");
        printf("[1] Menu Definicji Wydatków\n");
        printf("[2] Stworz Zestawienie\n");
        
        int D;
        scanf("%d", &D);
        
        if(D == -1)
            break;
        
        if(D == 0)
            Wydatek_Menu(Wybraniec);
        
        if(D == 1)
            Events_Menu(Wybraniec);
        
        if(D == 2)
            Zestawienie_Menu(Wybraniec);
    }
    //select_menu();
}

void Zestawienie_Menu(struct Uzytkownik* Wybraniec)
{
    while(1)
    {
        system("clear");
        WypiszUser(Wybraniec);
        
        printf("[-1] Wróć\n");
        printf("[0] Zestawienie Do Terminala\n");
        printf("[1] Zestawienie Do Pliku\n");
        
        int D;
        scanf("%d", &D);
        
        if(D == -1)
            break;
        if(D != -1 && D != 0 && D != 1)
            continue;
        
        system("clear");
        WypiszUser(Wybraniec);
        printf("[0] Zestawienie z całego okresu\n");
        printf("[1] Zestawienie z zadanego zakresu\n");
        
        int D1;
        scanf("%d", &D1);
        
        int START = 0;
        int KONIEC = 49999;
        
        if(D1 == 1)
        {
            printf("Podaj date początku i końca (obustronnie włącznie)\n RRRR-MM-DD RRRR-MM-DD");
            Date x;
            Date y;
            scanf("%d-%d-%d %d-%d-%d", &x.Rok, &x.Miesiac, &x.Dzien, &y.Rok, &y.Miesiac, &y.Dzien);
            START = DateToUnix(x);
            KONIEC = DateToUnix(y);
        }
        Zestawienie(Wybraniec, sciezka_zapisu, START, KONIEC, D);
                       
    }
}

void Wydatek_Menu(struct Uzytkownik* Wybraniec)
{
    while(1)
    {
        system("clear");
        WypiszUser(Wybraniec);


        
        printf("[-1] Wróć\n");
        printf("[0] Dodaj Wydatek\n");
        printf("[1] Wypisz Wydatki\n");
        printf("[2] Usuń Wydatek\n");
        printf("[3] Bilans Wydatków\n");
        
        int D;
        scanf("%d", &D);
        
        if(D == -1)
            break;
        
        if(D == 0)
        {
            system("clear");
            WypiszUser(Wybraniec);
            int CYKL = 1;
            int INTERVAL = 0;
            
            printf("[-1] Wróć\n");
            printf("[0] Dodaj W Pojedyńczo\n");
            printf("[1] Dodaj W Serii\n");
            
            int D1;
            scanf("%d", &D1);

            if(D1 == 1)
            {
                printf("Interwał:\n");
                scanf("%d", &INTERVAL);
                printf("Ilość Powtórzeń:\n");
                scanf("%d", &CYKL);
            }
            Dodaj_Wydatek(Wybraniec, sciezka_zapisu, CYKL, INTERVAL);
            continue;
        }
            
        
        if(D == 1)
        {
            system("clear");
            WypiszUser(Wybraniec);

            printf("W jakim Okresie?\n");
            printf("[-1] Wróć\n");
            printf("[0] Całym\n");
            printf("[1] Zdefiniowanym\n");

            int D1;
            scanf("%d", &D1);


            if(D1 == -1)
                continue;

            if(D1 == 0)
                Wypisz_Wydatki(*Wybraniec, 0, 49999);

            if(D1 == 1)
            {
                printf("Podaj Datę poczatkową i końca, daty będą użyte włącznie\n[RRRR-MM-DD RRRR-MM-DD]\n");
                Date START = {1970,1,1};
                Date KONIEC = {1970,1,1};

                scanf("%d-%d-%d %d-%d-%d", &START.Rok, &START.Miesiac, &START.Dzien, &KONIEC.Rok, &KONIEC.Miesiac, &KONIEC.Dzien);

                int start = DateToUnix(START);
                int koniec = DateToUnix(KONIEC);

                Wypisz_Wydatki(*Wybraniec, start, koniec);
                continue;
            }
        }
        
        if(D == 2)
            Usun_Wydatek(Wybraniec, sciezka_zapisu);
        
        if(D == 3)
        {
            system("clear");
            WypiszUser(Wybraniec);

            printf("W jakim Okresie?\n");
            printf("[-1] Wróć\n");
            printf("[0] Całym\n");
            printf("[1] Zdefiniowanym\n");

            int D1 = -2;
            scanf("%d", &D1);


            if(D1 == -1)
                continue;
            double wartosc = 0;
            if(D1 != 0 && D1 != 1)
                continue;
            if(D1 == 0)
                wartosc = Suma_Wydatki(Wybraniec, 0, 49999);

            if(D1 == 1)
            {
                printf("Podaj Datę poczatkową i końca, daty będą użyte włącznie\n[RRRR-MM-DD RRRR-MM-DD]\n");
                Date START = {1970,1,1};
                Date KONIEC = {1970,1,1};

                scanf("%d-%d-%d %d-%d-%d", &START.Rok, &START.Miesiac, &START.Dzien, &KONIEC.Rok, &KONIEC.Miesiac, &KONIEC.Dzien);

                int start = DateToUnix(START);
                int koniec = DateToUnix(KONIEC);

                wartosc = Suma_Wydatki(Wybraniec, start, koniec);
            }
            
            printf("\nBilans Wynosi: %.2lfzł\n", wartosc);
            
            printf("<kliknij cokolwiek by wrócić!>\n");
            char c;
            scanf("\n%c", &c);
        }
        
        
    }
}

void Events_Menu(struct Uzytkownik* Wybraniec)
{
    while(1)
    {
        system("clear");
        WypiszUser(Wybraniec);

        
        printf("[-1] Wróć\n");
        printf("[0] Wypisz wszystkie definicje wydatków\n");
        printf("[1] Zmień Nazwe Konkretnego Wydatku\n");
        printf("[2] Dodaj Zdefiniowany Wydatek\n");
        
        
        int D = -20;
        scanf("%d", &D);
        
        if(D == -1)
            break;
        if(D == 0)
        {
            Wypisz_Events(*Wybraniec);
            continue;
        }
            
        if(D == 1)
        {
            ZmienNazwe_Events(*Wybraniec, sciezka_zapisu);
            continue;
        }
                    
        if(D == 2)
        {
            DodajEvent_Events(Wybraniec, sciezka_zapisu);
            continue;
        }
      
    }
    
}




void Create_user(void)
{
    system("clear");
    printf("Podaj nazwe nowego użytkownika (Mozesz uzyc maksymalnie %d znakow!)\n", MAX_USER-1);
    char user[MAX_USER];
    
    scanf("\n%[^\n]%*c", user);
    
    for(int i = 1; i < UsersList.number_of_users; i++)
    {
        if(strcmp(UsersList.uzytkownicy[i],user) == 0)
        {
            printf("Blad! Uzytkownik juz istnieje!\n");
            for(int i = TIMEOUT_TIME; i > 0; i--)
            {
                printf("Powrot do Menu Glownego za: %d\n", i);
                sleep(1);
            }
            select_menu();
        }
            
    }
        
    char user_path[strlen(sciezka_zapisu) + strlen(user)];
    strcpy(user_path,sciezka_zapisu);
    strcat(user_path, user);
    
    mkdir(user_path, 0777);
    
    char used_path[strlen(user_path) + strlen(user)];
    strcpy(used_path, user_path);
    strcat(used_path, "/");
    

    CreateFiles(used_path);
    add_user(user, UsersList.number_of_users);
    //select_menu();
}




int main(int argc, const char * argv[]) {
    UsersList.number_of_users = argc;
    INIT(argv);
    
    select_menu();
    
    return 0;
}
