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

int main()
{
    firstrun();
    settings_read();
    database_read();

    // Ncurses init
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    return 0;
}