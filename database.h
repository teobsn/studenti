#include <cstring>
#include <fstream>
#include <iostream>
#include "define.h"

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

// Meta

int database_length = 0;

void database_set(char p[], int i, int k)
{
    switch (k)
    {
    case 1:
        studenti[i].cod = std::atoi(p);
        break;
    case 2:
        strcpy(studenti[i].nume, p);
        break;
    case 3:
        strcpy(studenti[i].prenume, p);
        break;
    case 4:
        studenti[i].dn.an = std::atoi(p);
        break;
    case 5:
        studenti[i].dn.luna = std::atoi(p);
        break;
    case 6:
        studenti[i].dn.zi = std::atoi(p);
        break;
    case 7:
        studenti[i].grupa = std::atoi(p);
        break;
    case 8:
        studenti[i].medie = std::atof(p);
        break;
    case 9:
        studenti[i].val_bursa = std::atoi(p);
        break;
    }
}

void database_set(char line[], int i)
{
    char c[database_maxlinelength];
    char *p = strtok(line, ",");
    for (int j = 1; j <= database_nparam; j++)
    {
        strcpy(c, p);
        database_set(c, i, j);
        p = strtok(NULL, ",");
    }
}

void database_add(char line[])
{
    database_set(line, database_length + 1);
    database_length++;
}

void database_delete(int cod)
{
    int k = 0;
    for (int i = 1; i <= database_length; i++)
        if (studenti[i].cod == cod)
            k = i;

    if (k == database_length)
        database_length--;
    else if (k)
    {
        for (int i = k; i <= database_length; i++)
            studenti[i] = studenti[i + 1];
        database_length--;
    }
    else
        std::cerr << "(err) Cod invalid: " << cod << "\n";
}

void database_validate()
{
    // std::cerr << "(err) Database: ?????\n";

    /*
    for (int i = 0; i < database_length; i++)
        std::cerr << studenti[i].cod << " " << studenti[i].nume << " " << studenti[i].prenume << " " << studenti[i].dn.an << "/" << studenti[i].dn.luna << "/" << studenti[i].dn.zi << " " << studenti[i].grupa << " " << studenti[i].medie << " " << studenti[i].val_bursa << "\n";
    */
}

void database_read()
{
    std::ifstream fin(database_filename);

    char line[database_maxlinelength];
    while (!fin.eof())
    {
        fin.getline(line, database_maxlinelength);
        if (strlen(line))
            database_add(line);
    }

    database_validate();

    fin.close();
}