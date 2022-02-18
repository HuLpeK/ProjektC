
##S10: System Zarządzania Budżetem Studenta

#Dokumentacja Programisty


Kod znajduje się w scieżce *src/* 

1. src/Code/main.c
	* Wszystkie Menu
2. src/Code/Handlers
	1. DateHandler
		* Obsługa zapytań i operacji na datach.
		* Daty zapisywane są w formie ilości dni których ubyło od 01-01-1970 (ten dzień to dzień '0').
	2. DataHandler
		* Obsługa zapytań i operacji na danych. W tym:
			* Zapisywanie Danych Do Pliku
			* Wczytywnie Danych z Pliku
			* Edycja Wczytanych Danych
			* Wypisywanie danych 
			* Tworzenie zestawień	
		
	3. CreateFileHandler
		* Odpowiada za stworzenie odpowiedniych plików nowego użytkownika.
	4. Vector
		* Moduł struktury która obsługuje wszelkie działania na danych.
	


