// Librarii C/C++
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <utility>

// Ncurses
#include <ncurses.h>

// Fisiere subprograme
#include "ui.h"
#include "settings.h"
#include "firstrun.h"
#include "database.h"
#include "search.h"

void database_sort_az()
{
    for (int i = 1; i <= database_size - 1; i++)
        for (int j = i + 1; j <= database_size; j++)
        {
            if (strcmp(studenti[i].nume, studenti[j].nume) > 0 || (strcmp(studenti[i].nume, studenti[j].nume) == 0 && strcmp(studenti[i].prenume, studenti[j].prenume) > 0))
            {
                struct student aux = studenti[i];
                studenti[i] = studenti[j];
                studenti[j] = aux;
            }
        }
}

bool database_ver_corigent(int i)
{
    return (studenti[i].medie >= medie_min);
}

int database_n_corigenti()
{
    int k = 0;
    for (int i = 1; i <= database_size; i++)
        k += database_ver_corigent(i);
    return k;
}

int main()
{
    firstrun();
    settings_read();
    database_read();

    // Ncurses init
    /*
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    */
    for (int i = 1; i <= database_length; i++)
        std::cerr << studenti[i].cod << " " << studenti[i].nume << " " << studenti[i].prenume << " " << studenti[i].dn.an << "/" << studenti[i].dn.luna << "/" << studenti[i].dn.zi << " " << studenti[i].grupa << " " << studenti[i].medie << " " << studenti[i].val_bursa << "\n";

    database_sort_az();
    for (int i = 1; i <= database_length; i++)
        std::cerr << studenti[i].cod << " " << studenti[i].nume << " " << studenti[i].prenume << " " << studenti[i].dn.an << "/" << studenti[i].dn.luna << "/" << studenti[i].dn.zi << " " << studenti[i].grupa << " " << studenti[i].medie << " " << studenti[i].val_bursa << "\n";

    return 0;
}