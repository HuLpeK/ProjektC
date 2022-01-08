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
#define MAX_USER 256

int START_Header = 0;
char* sciezka_zapisu; //PREFIX do folderu SAVES
char* uzytkownicy[MAX_USER]; // w [0] trzymamy wielkosc tablicy
int number_of_users;



void INIT(const char* slowo[])
{
    for(int i = 0; slowo[1][i] != '\0'; i++)
        if(slowo[1][i] == '/')
            START_Header = i+1;
    
    
    sciezka_zapisu = realloc(sciezka_zapisu, (START_Header)* sizeof(char));
    
    for(int i = 0; i < START_Header; i++)
        sciezka_zapisu[i] = slowo[1][i];
    
    sciezka_zapisu[START_Header] = '\0';
    
    for(int i = 1; i < number_of_users; i++)
    {
        char* help;
        get_user(slowo[i], &help);
        add_user(help, i);
    }
}
void add_user(char* user, int index)
{
    if(index >= number_of_users)
        number_of_users++;
    char* tmp = (char*)calloc(strlen(user), sizeof(char));
    strcpy(tmp,user);
    uzytkownicy[index] = tmp;
}


void get_user(const char path[], char** user)
{
    char* help = (char*)calloc(strlen(path)-START_Header, sizeof(char));
    int wskaznik = 0;
    for(int i = START_Header; path[i] != '\0'; i++)
        help[wskaznik++] = path[i];
    *user = help;
}


void select_menu()
{
    system("clear");
    printf("Wybierz użytkownika z listy lub dodaj kolejnego:\n");
    printf("[-1]: <Usuń Użytkownika>\n");
    printf("[0]: <Dodaj Użytkownika>\n"); // Stworz To do select_menu
    for(int i = 1; i < number_of_users; i++)
    {
        printf("[%d]: ", i);
        
        printf("%s \n", uzytkownicy[i]);
    }

    int wybor;
    scanf("%d", &wybor);
    
    
    if(wybor == 0)
        Create_user();
   
    
}

void Create_user()
{
    system("clear");
    printf("Podaj nazwe nowego użytkownika (Mozesz uzyc maksymalnie %d znakow!)\n", MAX_USER-1);
    char user[MAX_USER];
    
    scanf("\n%[^\n]%*c", user);
    
    for(int i = 1; i < number_of_users; i++)
    {
        if(strcmp(uzytkownicy[i],user) == 0)
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
    
    printf("%s %s\n", sciezka_zapisu, user_path);
    char used_path[strlen(user_path) + strlen(user)];
    strcpy(used_path, user_path);
    strcat(used_path, "/tst");
    
    FILE *fp = fopen(used_path, "w+"); // DEBUG
    
    if(fp == NULL)
    {
        printf("Blad Tworzenia Nowego Uzytkownika!!!");
//        del_user(user_path);
        exit(0);
    }
    add_user(user, number_of_users);
    select_menu();
    
}



int main(int argc, const char * argv[]) {
    number_of_users = argc;
    INIT(argv);
    
    select_menu();
       
    return 0;
}
