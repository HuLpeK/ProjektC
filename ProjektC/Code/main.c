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

int START_Header = 0;
char* sciezka_zapisu;
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

int main(int argc, const char * argv[]) {
    
    INIT(argv[1]);
    printf("Wybierz użytkownika z listy lub dodaj kolejnego:\n");
    
    printf("[0]: <Dodaj Użytkownika>\n");
    for(int i = 1; i < argc; i++)
    {
        printf("[%d]: ", i);
        for(int j = START_Header;  argv[i][j] != '\0'; j++)
            putchar(argv[i][j]);
        putchar('\n');
    }
    
    
    int wybor;
    scanf("%d", &wybor);
    
    if(wybor == 0)
    {
        printf("Podaj nazwe nowego użytkownika (Mozesz uzyc maksymalnie 256 znakow!)\n");
        char user[256];
        
        scanf("\n%[^\n]%*c", user);
			
        char user_path[strlen(sciezka_zapisu) + strlen(user)];
        strcpy(user_path,sciezka_zapisu);
        strcat(user_path, user);
        
        printf("%s", user_path);
        
        mkdir(sciezka_zapisu, 0777);
        FILE *fp = fopen(user_path, "w+");
        
        if(fp == NULL)
        {
            printf("Blad Tworzenia Nowego Uzytkownika!!!");
            exit(0);
        }
        
        
            
    }
    
    ///
    return 0;
}
