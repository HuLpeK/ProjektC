mkdir ./ProjektC/Saves

gcc -lm ./ProjektC/Code/main.c ./ProjektC/Code/Handlers/DateHandler.c ./ProjektC/Code/Handlers/DataHandler.c ./ProjektC/Code/Handlers/CreateFileHandler.c ./ProjektC/Code/Handlers/Vector.c ./ProjektC/Code/Handlers/SaveFileHandler.c -o ./ProjektC/Code/main.o

chmod +x ./ProjektC/Code/main.o

​#gcc -lm ./ProjektC/Code/main.c ./ProjektC/Code/Handlers/DateHandler.c ./ProjektC/Code/Handlers/DataHandler.c ./ProjektC/Code/Handlers/DataHandler.h ./ProjektC/Code/Handlers/CreateFileHandler.c ./ProjektC/Code/Handlers/Vector.c -o ./ProjektC/Code/main.o
​
chmod +x ./ProjektC/Code/main.c
