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
char uzytkownicy[256][256];
void INIT(const char slowo[])
{
    for(int i = 0; slowo[i] != '\0'; i++)
        if(slowo[i] == '/')
            START_Header = i+1;
    
    
    sciezka_zapisu = realloc(sciezka_zapisu, (START_Header)* sizeof(char));
    
    for(int i = 0; i < START_Header; i++)
        sciezka_zapisu[i] = slowo[i];
    
    sciezka_zapisu[START_Header] = '\0';
}

void get_user(const char path[], char** user)
{
    char* help = (char*)calloc(strlen(path)-START_Header, sizeof(char));
    for(int i = START_Header; path[i] != '\0'; i++)
        help[i] = path[i];
    *user = help;

}


int main(int argc, const char * argv[]) {
    
    INIT(argv[1]);
    char* X;
    get_user(argv[2], &X);
    for(int i = 0; X[i] != '\0'; i++)
        putchar(X[i]);
    
    exit(0);
    
    printf("Wybierz użytkownika z listy lub dodaj kolejnego:\n");
    
    printf("[0]: <Dodaj Użytkownika>\n"); // Stworz To do select_menu
    for(int i = 1; i < argc; i++)
    {
        printf("[%d]: ", i);
        for(int j = START_Header;  argv[i][j] != '\0'; j++)
            putchar(argv[i][j]);
        putchar('\n');
    }
    
    
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
