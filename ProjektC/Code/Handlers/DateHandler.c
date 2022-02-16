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


Date UnixToData(int Dni)
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

int DataToUnix(Date Data)
{
    Date x = {1970,1,1};
    int DNI = 0;
    
    int MO_LEN[13] = { -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    DNI += Data.Dzien - x.Dzien;
    for(int i = 1; 1 <= 12 && x.Miesiac != Data.Miesiac; i++)
    {
        DNI += MO_LEN[i];
        x.Miesiac++;
    }
    
    for(; x.Rok != Data.Rok; x.Rok++)
    {
        if(isLeap(x.Rok))
            DNI++;
        DNI+=365;
    }
    
    return DNI;
}


int CheckDate(Date Data)
{
    int MO_LEN[13] = { -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if(isLeap(Data.Rok))
        MO_LEN[2]++;
    if(Data.Rok < 1970 || Data.Miesiac <= 0 || Data.Dzien <= 0 || Data.Miesiac > 12)
        return 0;
    
    if(MO_LEN[Data.Miesiac] > Data.Dzien)
        return 0;
    
    
    return 1;
}
