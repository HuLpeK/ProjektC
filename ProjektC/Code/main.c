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

#include "Header.h"

int START_Header = 0;
char* sciezka_zapisu;
char* uzytkownicy[256];
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
    printf("Wybierz użytkownika z listy lub dodaj kolejnego:\n");
    
    printf("[0]: <Dodaj Użytkownika>\n"); // Stworz To do select_menu
    for(int i = 1; i < number_of_users; i++)
    {
        printf("[%d]: ", i);
        
        printf("%s \n", uzytkownicy[i]);
    }

    int wybor;
    scanf("%d", &wybor);a
}

int main(int argc, const char * argv[]) {
    number_of_users = argc;
    INIT(argv);

    
    select_menu();
    
    
    int wybor;
    scanf("%d", &wybor);
    
    if(wybor == 0) // SPRAWDZ czy jak dodajesz plik to taki nie istnieje!
    {
        printf("Podaj nazwe nowego użytkownika (Mozesz uzyc maksymalnie 256 znakow!)\n");
        char user[256];
        
        scanf("\n%[^\n]%*c", user);
        
			
        char user_path[strlen(sciezka_zapisu) + strlen(user)];
        strcpy(user_path,sciezka_zapisu);
        strcat(user_path, user);
        
        mkdir(sciezka_zapisu, 0777);
        FILE *fp = fopen(user_path, "w+");
        
        if(fp == NULL)
        {
            printf("Blad Tworzenia Nowego Uzytkownika!!!");
            exit(0);
        }
        printf("%s", user_path);
            
    }
    
    ///
    return 0;
}
