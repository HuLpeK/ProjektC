/// Projekt Programistyczny System Zarządzania Budżetem Studenta
/// Autor: Hubert Kulpaczyński 330840
/// Uczelnia: Instytut Informatyki Uniwerstytetu Wrocławskiego

#ifndef CreateFileHandler_h
#define CreateFileHandler_h
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void CreateFile_Events(char* Path);
void DelFile_User(char Path[]);
void CreateFiles(char Path[]);
void CreateFile_Date(char Path[]);


#endif /* CreateFileHandler_h */
