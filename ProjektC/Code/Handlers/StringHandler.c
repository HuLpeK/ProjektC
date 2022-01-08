//
//  StringHandler.c
//  ProjektC
//
//  Created by Hubert Kulpaczyński on 08/01/2022.
//

#include "StringHandler.h"


char* itoa(int X, char* a) ///ZWOLNIC Pamiec z a
{
   
   unsigned long nDigits = floor(log10(abs(X))) + 1;
   if(a != NULL)
   {
        free(a);
        a=NULL;
   }

   char* tmp = calloc(nDigits, sizeof(char));
   sprintf(tmp, "%d", X);
   a = tmp;
   return a;
}
