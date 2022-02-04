//
//  SaveFileHandler.h
//  ProjektC
//
//  Created by Hubert Kulpaczyński on 04/02/2022.
//

#ifndef SaveFileHandler_h
#define SaveFileHandler_h

#include <stdio.h>
#include <string.h>
#include "./Vector.h"
#include "./DataHandler.h"

void SaveFiles(struct Uzytkownik Wybraniec, char Path[]);
void SaveFiles_Events(struct Uzytkownik Wybraniec, char Path[]);
#endif /* SaveFileHandler_h */
