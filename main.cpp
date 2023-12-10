// Librarii C/C++
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <utility>

// Ncurses
#ifdef __unix__
#include <ncurses.h>
#endif

#ifdef _WIN32
#include <curses.h>
#include <cstdint>
#endif

// Fisiere subprograme
#include "database.h"
#include "define.h"
#include "firstrun.h"
#include "search.h"
#include "settings.h"
#include "ui.h"

bool ui_exit = false;

// Subprograme baza de date

int database_n_bursieri_gr_b1(int gr)
{
    int nt = database_n_ap_gr(gr);
    float nb = nt * ((float)procstud_bursa1 / 100);

    int nb_int;
    if (nb > (int)nb)
        nb_int = floor(nb) + 1;

    return nb_int;
}

int database_n_bursieri_gr_b2(int gr)
{
    int nt = database_n_ap_gr(gr);
    float nb = nt * ((float)procstud_bursa2 / 100);

    int nb_int;
    if (nb > (int)nb)
        nb_int = floor(nb) + 1;

    return std::min(nb_int, nt - database_n_bursieri_gr_b1(gr));
}

int database_n_bursieri_gr(int gr)
{
    return database_n_bursieri_gr_b1(gr) + database_n_bursieri_gr_b2(gr);
}

void database_update_bursieri()
{
    database_sort_gr_medie();

    int i = 1, aux = 0;
    while (i <= database_length)
    {
        int nb1, nb2;
        if (studenti[i].grupa != aux)
        {
            nb1 = database_n_bursieri_gr_b1(studenti[i].grupa), nb2 = database_n_bursieri_gr_b2(studenti[i].grupa), aux = studenti[i].grupa;

            for (int j = 0; j < nb1; j++)
                studenti[i + j].val_bursa = val_bursa1;

            for (int j = nb1; j < nb1 + nb2; j++)
                studenti[i + j].val_bursa = val_bursa2;
        }
        i++;
    }
}

// Subprograme interfata

void ui_draw_database()
{
    clear();

    // Intreg terminalul
    for (int i = 1; i < LINES - 2; i++)
        mvaddstr(i, 0, ui_symb_line_v);
    
    for (int i = 1; i < COLS - 1; i++)
        mvaddstr(0, i, ui_symb_line_h);

    for (int i = 1; i < LINES - 2; i++)
        mvaddstr(i, COLS - 1, ui_symb_line_v);

    for (int i = 1; i < COLS - 1; i++)
        mvaddstr(LINES - 2, i, ui_symb_line_h);

    for (int i = 1; i < COLS - 1; i++)
        mvaddstr(2, i, ui_symb_line_h);


    mvaddstr(0, 0, ui_symb_line_dr);
    mvaddstr(0, COLS - 1, ui_symb_line_dl);
    
    mvaddstr(LINES - 2, COLS - 1, ui_symb_line_ul);
    mvaddstr(LINES - 2, 0, ui_symb_line_ur);

    mvaddstr(2, 0, ui_symb_line_vr);
    mvaddstr(2, COLS - 1, ui_symb_line_dl);
    
    // Fereastra principala

    mvaddstr(1, 2, "Lista Studenti");

    // Fereastra secundara
    int w2_width = 17;
    int w2x0 = COLS - w2_width - 2;

    for (int i = 1; i < LINES - 2; i++)
        mvaddstr(i, w2x0, ui_symb_line_v);

    mvaddstr(0, w2x0, ui_symb_line_hd);
    mvaddstr(2, w2x0, ui_symb_line_hd);

    mvaddstr(LINES - 2, w2x0, ui_symb_line_ul);

    mvaddstr(1, w2x0 + 2, "Optiuni");

    mvaddstr(3, w2x0 + 2, "Sortare:");
    mvaddstr(4, w2x0 + 4, "Alfabetica");
    mvaddstr(5, w2x0 + 4, "Cod");
    mvaddstr(6, w2x0 + 4, "Grupa");
    mvaddstr(7, w2x0 + 4, "Medie (desc)");
    mvaddstr(8, w2x0 + 4, "Grupa + Medie");

    mvaddstr(10, w2x0 + 2, "Bursier:");
    mvaddstr(11, w2x0 + 2, "Grupa:");
    mvaddstr(12, w2x0 + 2, "Promovat:");

    // Indicatii taste
    mvaddstr(LINES - 1, 0, "ESC=Iesire   ");

    // Optiuni
    int set_sortare = 1;
    // 0: Alfabetica
    // 1: Cod
    // 2: Grupa
    // 3: Medie (desc)
    // 4: Grupa + Medie
    mvaddstr(4 + set_sortare, w2x0 + 2, "*");

    bool set_bursier = false;
    mvaddstr(10, COLS - 3, set_bursier ? "D" : "N");

    int set_grupa = 0;
    char set_grupa_aux[] = "-";
    mvaddstr(11, COLS - 2 - strlen(set_grupa_aux), set_grupa_aux);

    int set_promovare = 0;
    // 0 = -
    // 1 = nu
    // 2 = da
    char set_promovare_aux[] = "-";
    mvaddstr(12, COLS - 3, set_promovare_aux);

    // Loop
    refresh();

    bool run = true;
    while (run)
    {
        int key = getch();
        if ((key == controls_enter) || (key == controls_enter_2) || (key == controls_esc))
            run = false;
    }
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
        if (ncif(set[y - oy]))
        {
            mvaddstr(y, ox + 2 + ncif(set[y - oy]), " ");
            move(y, ox + 2 + ncif(set[y - oy]));
        }
        else
        {
            mvaddstr(y, ox + 2, "0");
            move(y, ox + 3);
        }
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
    database_update_bursieri();
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
    refresh();
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
    setlocale(LC_ALL, "");
    initscr();
    if (has_colors())
    {
        use_default_colors();
        start_color();

        init_pair(1, COLOR_GREEN, -1);
        init_pair(2, COLOR_CYAN, -1);
        init_pair(3, COLOR_MAGENTA, -1);
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
    database_update_bursieri();
    database_sort_cod();

    ui_start();

    endwin();
    return 0;
}