//
//  DataHandler.c
//  ProjektC
//
//  Created by Hubert Kulpaczyński on 06/01/2022.
//

#include "DataHandler.h"

struct User InitUser()
{
    struct User wybaraniec;
    
    for(int i = 0; i < ARRAY_SIZE; i++)
        vector_init(&wybaraniec.Array[i]);
    
    vector_init(&wybaraniec.Events.Array);
    
    return wybaraniec;
}

struct User ReadFiles(char* Path)
{
    struct User wybraniec = InitUser();
    
    
    return  wybraniec;
}
