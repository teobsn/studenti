#include <cstring>
#include <fstream>
#include "define.h"

void ini_generate_default()
{ // https://stackoverflow.com/questions/6892754/creating-a-simple-configuration-file-and-parser-in-c
    const char config[] =
        "val_bursa1=700\n"
        "val_bursa2=500\n"
        "procstud_bursa1=20\n"
        "procstud_bursa2=30\n"
        "medie_min=5";

    std::ofstream fout(settings_filename);
    for (int i = 0; i < strlen(config); i++)
        fout << config[i];
    fout.close();
}

void database_generate_default()
{ // csv format: cod, nume, prenume, (an, luna, zi nastere), grupa, media, valoare bursa
    const char database[] =
        "COD,NUME,PRENUME,AN_NASTERE,LUNA_NASTERE,ZI_NASTERE,GRUPA,MEDIE,VAL_BURSA\n"
        "1,Corbeanu,Daniel,2003,10,20,1,8.32,500\n"
        "2,Plesu,Costin,2004,5,19,1,7.12,500\n"
        "3,Bogza,Andrei,2000,3,32,2,9.23,700\n"
        "4,Ionescu,Valentin,1999,7,22,2,9.41,700\n"
        "5,Minea,Dana,2002,6,13,2,8.71,500\n"
        "6,Tomsa,Ruxandra,2003,2,7,3,9.21,700\n"
        "7,Raducanu,Paula Ilinca,2001,7,12,3,7.65,500\n"
        "8,Anghelescu,Izabela,2002,12,21,2,6.20,0\n"
        "9,Mica,Alex,2000,1,30,2,8.11,0\n"
        "10,Stancu,Stefan,2006,1,1,1,9.89,700\n"
        "11,Codreanu,Catalin,2005,1,14,2,5.98,0\n"
        "12,Tiberiu,Andrei-Teodor,2004,2,4,3,6.23,0\n"
        "13,Lupescu,Calin Marius,2000,5,8,2,8.31,500\n"
        "14,Andrei,Filip,2001,1,3,3,7.12,0\n"
        "15,Stefan,Petru,2003,8,21,2,6.98,0\n"
        "16,Dragomir,Ioana,2002,4,5,2,8.98,500\n"
        "17,Sandulescu,Rebeca,1999,7,16,1,9.02,500\n"
        "18,Grul,Sergiu,2004,4,13,2,9.21,500\n"
        "19,Creanga,Viorel,1998,2,1,3,8.51,700\n"
        "20,Popa,Marius,2002,7,23,2,8.21,0\n"
        "21,Balan,Toma,2001,3,4,1,4.90,0\n"
        "22,Draghici,Alin,2000,2,2,1,5.30,0\n"
        "23,Petrescu,Matei,2002,1,6,1,9.91,700\n"
        "24,Morosanu,Constantin,2004,2,9,2,7.65,0\n"
        "25,Vulcan,David,2003,7,31,3,8.50,500\n"
        "26,Bucsa,Madalina,1999,3,30,3,8.41,500\n"
        "27,Ceausescu,Marta,2000,2,21,2,9.41,700\n";
    
    std::ofstream fout(database_filename);
    for (int i = 0; i < strlen(database); i++)
        fout << database[i];
    fout.close();
}

bool file_exists(const std::string &name)
{ // https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exists-using-standard-c-c11-14-17-c
    std::ifstream f(name.c_str());
    return f.good();
}

void firstrun()
{
    if (!file_exists(settings_filename))
        ini_generate_default();
    if (!file_exists(database_filename))
        database_generate_default();
}