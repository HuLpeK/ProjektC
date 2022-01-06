//
//  main.c
//  ProjektC
//
//  Created by Hubert Kulpaczyński on 06/01/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int START_Header = 0;

void INIT(const char slowo[])
{
    for(int i = 0; slowo[i] != '\0'; i++)
        if(slowo[i] == '/')
            START_Header = i+1;
}

int main(int argc, const char * argv[]) {
    
    INIT(argv[1]);
    printf("Wybierz użytkownika z listy lub dodaj kolejnego:\n");
    
    printf("0: <Dodaj Użytkownika>\n");
    for(int i = 1; i < argc; i++)
    {
    
        printf("%d: ", i);
        for(int j = START_Header;  argv[i][j] != '\0'; j++)
            putchar(argv[i][j]);
        putchar('\n');
        
    }
    
    ///
    return 0;
}
