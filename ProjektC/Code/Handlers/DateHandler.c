//
//  DataHandler.c
//  ProjektC
//
//  Created by Hubert Kulpaczyński on 06/01/2022.
//

#include "DateHandler.h"


bool isLeap(int year)
{
    return (!(year % 4) && year % 100) || !(year % 400);
}


Date DataToUnix(int Dni)
{
    Date x = {1970,1,1};
       
//
    while(Dni >= (isLeap(x.Rok) ? 365:366))
    {
        Dni -= isLeap(x.Rok) ? 365:366;
        x.Rok++;
    }
        

    int MO_LEN[13] = { -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    if(isLeap(x.Rok))
        MO_LEN[2]++;

    for(int i = 1; i <= 12 && Dni > 0; i++)
    {
        if(Dni-MO_LEN[i] >= 0)
            Dni -= MO_LEN[i];
    }
    
    x.Dzien += Dni;
    
    return x;
}
