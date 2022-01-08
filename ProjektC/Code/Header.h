//
//  Header.h
//  ProjektC
//
//  Created by Hubert Kulpaczyński on 06/01/2022.
//

#ifndef Header_h
#define Header_h

#include "./Handlers/DateHandler.h"
#include "./Handlers/DataHandler.h"
#include "./Handlers/StringHandler.h"

void INIT(const char * slowo[]);
void get_user(const char path[], char** user);
void add_user(char* user, int index);
void select_menu();
void Create_user();


#endif /* Header_h */
