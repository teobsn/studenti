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

// Urmatoarele 2 subprograme nu se afla in database.h deoarece se folosesc
// de variabila "medie_min" care este declarata in settings.h ¯\_(ツ)_/¯

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

    ui_start();

    return 0;
}