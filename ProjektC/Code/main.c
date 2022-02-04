//
//  main.c
//  ProjektC
//
//  Created by Hubert Kulpaczyński on 06/01/2022.
//

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
    }
}

void WypiszUser(struct Uzytkownik Wybraniec)
{
    printf("Użytkownik: %s\n", Wybraniec.Name);
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
    system("clear");
    printf("Podaj Numer Użytkownika Do usunięcia\n");
    printf("[0] <Wroc do Menu>\n");
    for(int i = 1; i < UsersList.number_of_users; i++)
        printf("[%d]: %s\n", i, UsersList.uzytkownicy[i]);
    
    int wybor;
    scanf("%d", &wybor);
    
    if(wybor == 0)
        select_menu();
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
    
    Select_User_Menu(Wybraniec);
}

void Select_User_Menu(struct Uzytkownik Wybraniec)
{
    system("clear");
//    printf("Nazwa Użytkownika: %s\n", Wybraniec.Name);
    WypiszUser(Wybraniec);
    
    printf("[-1] Wróć\n");
    printf("[0] Dodaj Wydatek\n");
    printf("[1] Menu Definicji Wydatków\n");
    printf("[2] Stworz Zestawienie\n");
    
    int D;
    scanf("%d", &D);
    
    if(D == -1)
        select_menu();
    
    if(D == 0);
    
    if(D == 1)
        Events_Menu(Wybraniec);
}

void Events_Menu(struct Uzytkownik Wybraniec)
{
    system("clear");
//    printf("Nazwa Użytkownika: %s\n", Wybraniec.Name);
    WypiszUser(Wybraniec);
    
    printf("[-1] Wróć\n");
    printf("[0] Wypisz wszystkie definicje wydatków\n");
    printf("[1] Zmień Nazwe Konkretnego Wydatku\n");
    printf("[2] Dodaj Zdefiniowany Wydatek\n");
    
    
    int D;
    scanf("%d", &D);
    
    if(D == -1)
        Select_User_Menu(Wybraniec);
    if(D == 0)
        Wypisz_Events(Wybraniec);
//    if(D == 1)
//        ZmienNazwe_Events(Wybraniec);
}



void Wypisz_Events(struct Uzytkownik Wybraniec)
{
    system("clear");
//    printf("Użytkownik: %s\n", Wybraniec.Name);
    WypiszUser(Wybraniec);
    
    for(int i = 0; i < VECTOR_SIZE(Wybraniec.Events.Array); i++)
        printf("[%d] %s", i,VECTOR_GET(Wybraniec.Events.Array, char*, i));
    
    printf("<Kliknij Cokolwiek By Wrócić>\n");
    char ch;
    scanf("\n%c", &ch);
    
    Events_Menu(Wybraniec);
}


void select_menu(void)
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
        DelUser_Menu();

    
    if(wybor == 0)
        Create_user();
    
    if(wybor >= 1 && wybor <= UsersList.number_of_users)
    {
        Select_User(wybor, UsersList, sciezka_zapisu);
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
    select_menu();
}




int main(int argc, const char * argv[]) {
    UsersList.number_of_users = argc;
    INIT(argv);
    
    select_menu();
    
    
    
    return 0;
}
