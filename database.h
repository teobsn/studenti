#include <cstring>
#include <cmath>
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
    database_set(line, database_length);
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
    database_length--;

    database_validate();

    fin.close();
}

// Database operations

int database_ctoi(int cod)
{
    int i = 1;
    while (studenti[i++].cod != cod)
        i++;
    return i;
}

bool database_ver_ap_gr(int i, int gr)
{
    return studenti[i].grupa == gr;
}

int database_n_ap_gr(int gr)
{
    int n = 0;
    for (int i = 1; i <= database_length; i++)
        n += database_ver_ap_gr(i, gr);
    return n;
}

void database_cat_name(int i, char c[])
{
    strcpy(c, studenti[i].nume);
    strcat(c, " ");
    strcat(c, studenti[i].prenume);
}

void database_sort_alf()
{
    int i, j;
    char fnc[database_n_maxlength + database_pn_maxlength + 1], fni[database_n_maxlength + database_pn_maxlength + 1];

    for (i = 2; i <= database_length; i++)
    {
        struct student aux = studenti[i];
        database_cat_name(i, fnc);
        j = i - 1;

        database_cat_name(j, fni);
        while (j >= 1 && strcmp(fni, fnc) > 0)
        {
            studenti[j + 1] = studenti[j];
            j--;
            database_cat_name(j, fni);
        }

        studenti[j + 1] = aux;
    }
}

void database_sort_medie_ij(int i, int j)
{
    int k, l;
    for (k = i; k <= j; k++)
    {
        struct student aux = studenti[k];
        l = k - 1;

        while (l >= i &&
               ((int)(studenti[l].medie * 100) < (int)(aux.medie * 100)))
        {
            studenti[l + 1] = studenti[l];
            l--;
        }

        studenti[l + 1] = aux;
    }
}

void database_sort_medie()
{
    database_sort_medie_ij(1, database_length);
}

void database_sort_gr()
{
    int i, j;

    for (i = 2; i <= database_length; i++)
    {
        struct student aux = studenti[i];
        j = i - 1;

        while (j >= 1 && studenti[j].grupa > aux.grupa)
        {
            studenti[j + 1] = studenti[j];
            j--;
        }

        studenti[j + 1] = aux;
    }
}

void database_sort_gr_medie()
{
    database_sort_gr();

    int aux = 1, i = 1, j = i;
    while (j < database_length)
    {
        j = i;
        while (studenti[i].grupa == studenti[j + 1].grupa)
            j++;

        database_sort_medie_ij(i, j);

        i = j + 1;
    }
}

void database_sort_cod()
{
    int i, j;

    for (i = 2; i <= database_length; i++)
    {
        struct student aux = studenti[i];
        j = i - 1;

        while (j >= 1 && studenti[j].cod > aux.cod)
        {
            studenti[j + 1] = studenti[j];
            j--;
        }

        studenti[j + 1] = aux;
    }
}

void database_debug()
{
    for (int i = 0; i <= database_length; i++)
        std::cerr << studenti[i].cod << " " << studenti[i].nume << " " << studenti[i].prenume << " " << studenti[i].dn.an << "/" << studenti[i].dn.luna << "/" << studenti[i].dn.zi << " " << studenti[i].grupa << " " << studenti[i].medie << " " << studenti[i].val_bursa << "\n";
    std::cerr << "\n";
}