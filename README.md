# Membrii echipei:
- Alexandra
- Angelo
- Daria
- Teo
# Detalii proiect

### Compatibilitate/Compilare
Programul nu se folosește de librării externe sau de funcții/subprograme ce funcționează doar pe anumite platforme. Așadar, acesta poate fi compilat pe orice platformă care dispune de compilatorul GNU/G++ sau Clang (LLVM) și de librăria `ncurses`.
Compilarea programului se poate face cu ajutorul următoarelor comenzi in terminal, în funcție de platformă:

|Platformă Compilator|Platformă Executabil|Compilator|Comandă|
|---|---|---|---|
|Linux x64|Linux x64|GNU/G++|`g++ -lncurses main.cpp -O2 -o studenti`|
|Linux x64|Linux x64|Clang|`clang++ -lncurses main.cpp -O2 -o studenti`|
|Windows x64|Windows x64|GNU/G++ MinGW-w64|`g++ -I/mingw64/include/ncurses -o studenti.exe main.cpp -O2 -lncurses -L/mingw64/bin -static`|
|macOS x64|macOS x64|Clang|`clang++ -lncurses main.cpp -O2 -o studenti`|

În cazul în care librăria `ncurses` nu este deja instalată, instalarea ei se poate realiza cu ajutorul următoarelor ghiduri, în funcție de sistemul de operare folosit: 
- Windows:

Compilatorul `mingw-w64` poate fi instalat utilizând următorul ghid: https://code.visualstudio.com/docs/cpp/config-mingw .

Trebuie instalate și următoarele pachete:
`pacman -S mingw-w64-x86_64-toolchain mingw-w64-ucrt-x86_64-ncurses mingw-w64-x86_64-ncurses`


- Linux: 

Ubuntu/Debian/Debian-based (apt) sau Fedora, CentOS (yum): https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/

Gentoo: `emerge sys-libs/ncurses`

Arch/Arch-based: `pacman -S ncurses`


- macOS: `xcode-select --install`

### Utilizarea macrourilor #define
Multe valori ale lungimilor/mărimilor șirurilor de caractere sau a altor date/structuri/variabile care au fost alese în mod arbitrar sunt definite în fișierul `define.h`, pentru a putea fi modificate rapid în cazul în care acest lucru este necesar.
Folosirea unui vector de tipul `std::vector` ar putea elimina necesitatea definirii mărimilor anumitor date, întrucât acesta poate să își modifice mărimea dinamic.
### Structura programului
Majoritatea, dacă nu toate subprogramele de care se folosește programul sunt definite în fișiere separate de `main.cpp`
Numele fișierelor reprezintă categoria din care fac parte subprogramele definite în acesta:

|Categorie|Fisier|Descriere|
|---|---|---|
|Bază de date|database.h|Conține subprograme ce accesează baza de date și fac operații cu/în aceasta.|
|Macro|define.h|Conține valori ale lungimilor/mărimilor șirurilor de caractere sau a altor date/structuri/variabile care au fost alese în mod arbitrar.|
|Inițializare fișiere|firstrun.h|Conține subprograme ce inițializează baza de date și fișierul de configurare cu valori implicite dacă acestea nu există deja.|
|Căutare|search.h|Conține subprogram ce sunt folosite pentru căutarea în baza de date a anumitor studenți după anumite criterii.|
|Setări|settings.h|Conține subprograme ce accesează fișierul de configurare.|
|Interfață|ui.h|Conține subprograme ce sunt folosite pentru a afișa interfața programului.|
### Structura de date
```c++
struct data
{
	int an, luna, zi;
};

struct student
{
	int cod;
	char nume[database_n_maxlength], prenume[database_pn_maxlength];
	struct data dn;
	int grupa;
	float medie;
	int val_bursa;
} studenti[database_size];
```
### Fișier bază de date
Programul se folosește de o bază de date (`database.csv`) în format CSV (Comma-Separated Values). Acest format permite editarea cu ajutorul oricărui program de calcul tabelar (Microsoft Excel, Google Sheets, OnlyOffice Spreadsheet Editor, etc.), dar poate fi editat cu ușurință și cu orice editor de text (Notepad, Notepad++, gedit, etc.). De asemenea, formatul poate fi citit de program fără a se folosi de funcții/subprograme complexe.
În fișierul bazei de date, fiecare linie corespunde unui student, iar parametrii (delimitați de virgulă '`,`') corespund fiecare unei variabile din structura de date.
Fișierul bazei de date este generat automat dacă nu există deja în folderul (directorul) programului și are următorul conținut implicit:

|COD|NUME      |PRENUME      |AN_NASTERE|LUNA_NASTERE|ZI_NASTERE|GRUPA|MEDIE|VAL_BURSA|
|--:|----------|-------------|---------:|-----------:|---------:|----:|----:|--------:|
|1  |Corbeanu  |Daniel       |2003      |10          |20        |1    |8.32 |500      |
|2  |Plesu     |Costin       |2004      |5           |19        |1    |7.12 |500      |
|3  |Bogza     |Andrei       |2000      |3           |32        |2    |9.23 |700      |
|4  |Ionescu   |Valentin     |1999      |7           |22        |2    |9.41 |700      |
|5  |Minea     |Dana         |2002      |6           |13        |2    |8.71 |500      |
|6  |Tomsa     |Ruxandra     |2003      |2           |7         |3    |9.21 |700      |
|7  |Răducanu  |Paula Ilinca |2001      |7           |12        |3    |7.65 |500      |
|8  |Anghelescu|Izabela      |2002      |12          |21        |2    |6.20 |0        |
|9  |Mica      |Alex         |2000      |1           |30        |2    |8.11 |0        |
|10 |Stancu    |Stefan       |2006      |1           |1         |1    |9.89 |700      |
|11 |Codreanu  |Catalin      |2005      |1           |14        |2    |5.98 |0        |
|12 |Tiberiu   |Andrei-Teodor|2004      |2           |4         |3    |6.23 |0        |
|13 |Lupescu   |Calin Marius |2000      |5           |8         |2    |8.31 |500      |
|14 |Andrei    |Filip        |2001      |1           |3         |3    |7.12 |0        |
|15 |Stefan    |Petru        |2003      |8           |21        |2    |6.98 |0        |
|16 |Dragomir  |Ioana        |2002      |4           |5         |2    |8.98 |500      |
|17 |Sandulescu|Rebeca       |1999      |7           |16        |1    |9.02 |500      |
|18 |Grul      |Sergiu       |2004      |4           |13        |2    |9.21 |500      |
|19 |Creanga   |Viorel       |1998      |2           |1         |3    |8.51 |700      |
|20 |Popa      |Marius       |2002      |7           |23        |2    |8.21 |0        |
|21 |Balan     |Toma         |2001      |3           |4         |1    |4.90 |0        |
|22 |Draghici  |Alin         |2000      |2           |2         |1    |5.30 |0        |
|23 |Petrescu  |Matei        |2002      |1           |6         |1    |9.91 |700      |
|24 |Morosanu  |Constantin   |2004      |2           |9         |2    |7.65 |0        |
|25 |Vulcan    |David        |2003      |7           |31        |3    |8.50 |500      |
|26 |Bucsa     |Madalina     |1999      |3           |30        |3    |8.41 |500      |
|27 |Ceausescu |Marta        |2000      |2           |21        |2    |9.41 |700      |


Numele și prenumele bazei de date implicite au fost generate cu ajutorul https://www.fantasynamegenerators.com/romanian-names.php și nu intenționează să descrie sau reprezinte nume reale.
### Fișier configurare
Programul se folosește de un fișier de configurare (`settings.ini`). Acesta conține parametri ce pot fi modificați după cerințele utilizatorului.
Fișierul de configurare este generat automat dacă nu există deja în folderul (directorul) programului și are ca valori implicite valorile cerinței problemei.
Programul analizează valorile fișierului de configurare și, la pornire, va afișa erori dacă acesta conține parametrii nedefiniți, dacă valorile anumitor parametri nu au sens (de exemplu, suma procentuală de studenți ce primesc bursă nu poate depăși `100%`). De asemenea, programul va afișa eroare pentru fiecare parametru lipsă.
##### Listă parametri:
|Parametru|Valoare implicită|Descriere|
|---|--:|---|
|val_bursa1|700|Valoarea monetară a primei burse|
|val_bursa2|500|Valoarea monetară a celei de a doua burse|
|procstud_bursa1|20|Procentajul de studenți ce vor primi prima bursă|
|procstud_bursa2|30|Procentajul de studenți ce vor cea de a doua bursă|
|medie_min|5|Media minimă pentru a promova|

### Interfața programului
Programul se folosește de librăria `ncurses` pentru afișarea interfaței. Librăria `ncurses` oferă diverse funcții/subprograme ce sunt folositoare pentru a formata textul afișat pe ecran și pentru a modifica parametrii terminalului fără folosirea unor interfațe de programare existente doar pe anumite platforme (Win32 API, Cocoa, etc.).
Interfața programului încearcă să fie cât mai accesibilă tuturor utilizatorilor, dar în același timp să fie cât mai versatilă. Pentru a realiza acest lucru, interfața se folosește de diferite caracteristici întâlnite deja în alte programe, precum căutarea în timp real în baza de date sau navigare în meniu cu ajutorul tastelor săgeți.
Elementele meniului principal pot fi accesate apăsând inițialele textului din lista (de exemplu, pentru a accesa setările, utilizatorul poate apăsa tasta `S`).
Interfața programului este centrată automat în terminal și se folosește de întreg spațiul terminalului.