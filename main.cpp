// Librarii C/C++
#include <iostream>
#include <cmath>
#include <cstring>
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

bool ui_exit = false;

char ui_menu_opts1[][ui_maxlength] = {
    "Baza de date",
    "Setari",
    "Despre",
    "Iesire"};

char ui_settings_list[][ui_maxlength] = {
    "Valoare Bursa 1",
    "Valoare Bursa 2",
    "Procent Studenti Bursa 1",
    "Procent Studenti Bursa 2",
    "Medie minima promovare"};

// Subprograme intefata

void ui_draw_database()
{
}

void ui_draw_settings()
{
    clear();
    int k = -2;
    for (int i = 0; i <= 4; i++)
        mvaddstr(LINES / 2 + k + i, COLS / 2 - strlen(ui_settings_list[i]), ui_settings_list[i]);

    mvaddstr(LINES / 2 + k - 1, COLS / 2 - strlen("Setari:") / 2, "Setari:");
    mvchgat(LINES / 2 + k - 1, COLS / 2 - strlen("Setari") / 2, strlen("Setari"), A_BOLD, NULL, NULL);

    int set[16];
    char aux[settings_maxlinelength];
    for (int i = 0; i <= 4; i++)
    {
        switch (i)
        {
        case 0:
            set[i] = val_bursa1;
            break;
        case 1:
            set[i] = val_bursa2;
            break;
        case 2:
            set[i] = procstud_bursa1;
            break;
        case 3:
            set[i] = procstud_bursa2;
            break;
        case 4:
            set[i] = medie_min;
            break;
        }

        itoa(set[i], aux, 10);
        mvaddstr(LINES / 2 + k + i, COLS / 2 + 3, aux);
    }

    int height = 5;

    int ox = COLS / 2 + 1;
    int oy = LINES / 2 + k;
    int y = oy;

    mvaddstr(oy, ox, ui_symb_selector);
    move(oy, ox + 2 + ncif(set[0]));

    refresh();

    bool run = true;
    while (run)
    {
        int key = getch();
        switch (key)
        {
        case controls_arr_down:
            mvaddstr(y, ox, " ");
            y = std::min(y + 1, oy + height - 1);
            break;
        case controls_arr_up:
            mvaddstr(y, ox, " ");
            y = std::max(y - 1, oy);
            break;
        case controls_arr_right:
            run = false;
            break;

        case controls_backsp:
        case controls_backsp_2:
            set[y - oy] /= 10;
            break;

        case controls_esc:
        case controls_enter:
        case controls_enter_2:
            run = false;
            break;

        default:
            if (48 <= key && key <= 57)
            {
                if (set[y - oy] <= INT32_MAX / 100)
                {
                    set[y - oy] *= 10;
                    if (key != 48)
                        set[y - oy] += key - 48;
                }
                itoa(set[y - oy], aux, 10);
                mvaddstr(y, COLS / 2 + 3, aux);
            }
            break;
        }

        mvaddstr(y, ox, ui_symb_selector);
        mvaddstr(y, ox + 2 + ncif(set[y - oy]), " ");
        move(y, ox + 2 + ncif(set[y - oy]));
    }

    for (int i = 0; i <= 4; i++)
    {
        switch (i)
        {
        case 0:
            val_bursa1 = set[i];
            break;
        case 1:
            val_bursa2 = set[i];
            break;
        case 2:
            procstud_bursa1 = set[i];
            break;
        case 3:
            procstud_bursa2 = set[i];
            break;
        case 4:
            medie_min = set[i];
            break;
        }
    }
}

void ui_draw_mainmenu()
{
    clear();
    int k = -2;
    for (int i = 0; i <= 3; i++)
    {
        mvaddstr(LINES / 2 + k + i, COLS / 2 + 1, ui_menu_opts1[i]);
        mvchgat(LINES / 2 + k + i, COLS / 2 + 1, 1, A_UNDERLINE, NULL, NULL);
    }
    // https://pubs.opengroup.org/onlinepubs/7908799/xcurses/chgat.html
    // https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/attrib.html

    int r = ui_input_arrowmenu1(4, LINES / 2 + k, COLS / 2 - 1);
    switch (r)
    {
    case 0:
        ui_draw_database();
        break;
    case 1:
        ui_draw_settings();
        break;
    case 2:
        ui_draw_about();
        break;
    case 3:
        ui_exit = true;
        break;
    }
}

void ui_start()
{
    initscr();
    if (has_colors())
    {
        use_default_colors();
        start_color();

        init_pair(1, COLOR_GREEN, -1);
        init_pair(2, COLOR_CYAN, -1);
        init_pair(3, COLOR_RED, -1);
        init_pair(4, COLOR_BLUE, -1);
    }
    raw();
    noecho();
    keypad(stdscr, TRUE);

    while (!ui_exit)
        ui_draw_mainmenu();

    clear();
    refresh();
}

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