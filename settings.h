#include <cstring>
// #include <string>
#include <fstream>
#include <iostream>
#include "define.h"

int val_bursa1 = -1;
int val_bursa2 = -1;
int procstud_bursa1 = -1;
int procstud_bursa2 = -1;
int medie_min = -1;

void settings_set(char key[], char value[])
{
    /* Switchurile nu functioneaza cu vectori/matrice (=> siruri de caractere sau stringuri)
    // https://stackoverflow.com/questions/48005819/can-we-use-switch-case-statement-with-strings-in-c
    switch(key)
    {
        case "val_bursa1":
            val_bursa1 = std::atoi(value);
            break;
        case "val_bursa2":
            val_bursa2 = std::atoi(value);
            break;
        case "procstud_bursa1":
            procstud_bursa1 = std::atoi(value);
            break;
        case "procstud_bursa2":
            procstud_bursa2 = std::atoi(value);
            break;
        default:
            std::cerr << "Settings key is invalid: " << "key: '" << key << "' with value: '" << value << "'";
    }
    */

    if (!strcmp(key, "val_bursa1"))
        val_bursa1 = std::atoi(value);
    else if (!strcmp(key, "val_bursa2"))
        val_bursa2 = std::atoi(value);
    else if (!strcmp(key, "procstud_bursa1"))
        procstud_bursa1 = std::atoi(value);
    else if (!strcmp(key, "procstud_bursa2"))
        procstud_bursa2 = std::atoi(value);
    else if (!strcmp(key, "medie_min"))
        medie_min = std::atoi(value);
    else
        std::cerr << "(err) Settings: key is invalid: "
                  << "key: '" << key << "' with value: '" << value << "'\n";
}

void settings_validate()
{
    if (procstud_bursa1 + procstud_bursa2 > 100)
        std::cerr << "(err) Settings: procstud_bursa1 + procstud_bursa2 > 100\n";

    if (procstud_bursa1 == -1)
        std::cerr << "(err) Settings: procstud_bursa1 missing or =-1\n";
    if (procstud_bursa2 == -1)
        std::cerr << "(err) Settings: procstud_bursa2 missing or =-1\n";
    if (val_bursa1 == -1)
        std::cerr << "(err) Settings: val_bursa1 missing or =-1\n";
    if (val_bursa2 == -1)
        std::cerr << "(err) Settings: val_bursa2 missing or =-1\n";
    if (medie_min == -1)
        std::cerr << "(err) Settings: medie_min missing or =-1\n";
}

void settings_read()
{
    std::ifstream fin(settings_filename);

    char aux[settings_maxlinelength], key[settings_maxlinelength], value[settings_maxlinelength];
    while (!fin.eof())
    {
        fin.getline(aux, settings_maxlinelength);
        if (strlen(aux))
        {
            int n = strchr(aux, '=') - aux;
            strncpy(key, aux, n);
            key[n] = '\0';
            strcpy(value, strchr(aux, '=') + 1);

            settings_set(key, value);
        }
    }

    settings_validate();

    fin.close();
}