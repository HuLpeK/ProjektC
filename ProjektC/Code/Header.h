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
#include "./Handlers/CreateFileHandler.h"
#include "./Handlers/Vector.h"
#include "./Handlers/SaveFileHandler.h"

#define MAX_USER 256


struct Users{
    int number_of_users;
    char* uzytkownicy[MAX_USER];
};

void INIT(const char * slowo[]);
void WypiszUser(struct Uzytkownik Wybraniec);
void Select_User(int index, struct Users UsersList, char* sciezka_zapisu);
void get_user(const char path[], char** user);
void add_user(char* user, int index);
void Select_User(int index, struct Users UsersList, char* sciezka_zapisu);
void Select_User_Menu(struct Uzytkownik Wybraniec);
void Events_Menu(struct Uzytkownik Wybraniec);
void select_menu(void);
void Create_user(void);
void DelUser_Menu(void);
void DelArr_User(int X);
void ZmienNazwe_Events(struct Uzytkownik Wybraniec);

#endif /* Header_h */
