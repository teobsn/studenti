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

// Subprograme interfata

void ui_draw_database_refresh(int set_sortare, int set_bursier, int set_grupa, int set_promovare, int height, int ux)
{
    int tb_length = std::min(database_length, height);
    for (int i = 0; i <= tb_length; i++)
        for (int j = 1; j <= ux; j++)
            mvaddstr(5 + i, j, " ");

    switch (set_sortare)
    {
    case 0:
        database_sort_alf();
        break;
    case 1:
        database_sort_cod();
        break;
    case 2:
        database_sort_gr();
        break;
    case 3:
        database_sort_medie();
        break;
    case 4:
        database_sort_gr_medie();
        break;
    }

    int lmaxcod = 0, lmaxn = 0, lmaxpn = 0, lmaxgrupa = 0, lmaxvalbursa = 0;
    for (int i = 1; i <= database_length; i++)
    {
        lmaxcod = ncif(studenti[i].cod) > lmaxcod ? ncif(studenti[i].cod) : lmaxcod;
        lmaxn = strlen(studenti[i].nume) > lmaxn ? strlen(studenti[i].nume) : lmaxn;
        lmaxpn = strlen(studenti[i].prenume) > lmaxn ? strlen(studenti[i].prenume) : lmaxn;
        lmaxgrupa = ncif(studenti[i].grupa) > lmaxgrupa ? ncif(studenti[i].grupa) : lmaxgrupa;
        lmaxvalbursa = ncif(studenti[i].val_bursa) > lmaxvalbursa ? ncif(studenti[i].val_bursa) : lmaxvalbursa;
    }

    int x = 2;
    mvaddstr(5, x, "Cod");
    x += (strlen("Cod") > lmaxcod) ? strlen("Cod") : lmaxcod;
    int xcod = x;
    x++;
    mvaddstr(4, x, ui_symb_line_hd);
    mvaddstr(5, x, ui_symb_line_v);
    x += 2;

    int xn = x;
    mvaddstr(5, x, "Nume");
    x += (strlen("Nume") > lmaxn + 2) ? strlen("Nume") : lmaxn + 2;
    x++;
    mvaddstr(4, x, ui_symb_line_hd);
    mvaddstr(5, x, ui_symb_line_v);
    x += 2;

    int xpn = x;
    mvaddstr(5, x, "Prenume");
    x += (strlen("Prenume") > lmaxpn + 2) ? strlen("Prenume") : lmaxpn + 2;
    x++;
    mvaddstr(4, x, ui_symb_line_hd);
    mvaddstr(5, x, ui_symb_line_v);
    x += 2;

    int xdn = x;
    mvaddstr(5, x, "Data nasterii");
    x += (strlen("Data nasterii") > strlen("YYYY / MM / DD")) ? strlen("Data nasterii") : strlen("YYYY / MM / DD");
    x++;
    mvaddstr(4, x, ui_symb_line_hd);
    mvaddstr(5, x, ui_symb_line_v);
    x += 2;

    mvaddstr(5, x, "Grupa");
    x += (strlen("Grupa") > lmaxgrupa) ? strlen("Grupa") : lmaxgrupa;
    int xg = x;
    x++;
    mvaddstr(4, x, ui_symb_line_hd);
    mvaddstr(5, x, ui_symb_line_v);
    x += 2;

    mvaddstr(5, x, "Medie");
    x += (strlen("Medie") > strlen("10.00")) ? strlen("Medie") : strlen("10.00");
    int xm = x;
    x++;
    mvaddstr(4, x, ui_symb_line_hd);
    mvaddstr(5, x, ui_symb_line_v);
    x += 2;

    mvaddstr(5, x, "Valoare Bursa");
    x += (strlen("Valoare Bursa") > lmaxvalbursa) ? strlen("Valoare Bursa") : lmaxvalbursa;
    int xvb = x;
    x++;
    mvaddstr(4, x, ui_symb_line_hd);
    mvaddstr(5, x, ui_symb_line_v);
    x += 2;

    int xprom = x;
    mvaddstr(5, x, "Promovat");
    x += strlen("Promovat");
    x++;
    mvaddstr(4, x, ui_symb_line_hd);
    mvaddstr(5, x, ui_symb_line_v);
    x += 2;

    char aux_cod[4];
    char aux_dn[strlen("YYYY / MM / DD") + 1], aux_g[ncif(database_ngrupe)], aux_vb[ncif(INT32_MAX) + 1];

    int k = 1;
    bool st_valid = false;
    for (int i = 1; i <= tb_length; i++)
    {
        st_valid = true;

        if (set_bursier != 0)
            if (set_bursier - 1 == !studenti[i].val_bursa) // 0 => Nebursier; 1 >= Bursier
                st_valid = false;

        if (set_promovare != 0)
            if (set_promovare - 1 == !database_ver_corigent(i)) // 0 => Nepromovat; 1 >= Promovat
                st_valid = false;

        if (set_grupa)
            if (set_grupa != studenti[i].grupa)
                st_valid = false;

        if (st_valid)
        {
            itoa(studenti[i].cod, aux_cod, 10);
            mvaddstr(5 + k, xcod - strlen(aux_cod), aux_cod);

            mvaddstr(5 + k, xn, studenti[i].nume);
            mvaddstr(5 + k, xpn, studenti[i].prenume);

            char aux_dn_y[5], aux_dn_m[3], aux_dn_d[3];
            itoa(studenti[i].dn.an, aux_dn_y, 10);
            itoa(studenti[i].dn.luna, aux_dn_m, 10);
            itoa(studenti[i].dn.zi, aux_dn_d, 10);
            strcpy(aux_dn, aux_dn_y);
            strcat(aux_dn, " ");
            strcat(aux_dn, "/");
            strcat(aux_dn, " ");
            if (studenti[i].dn.luna < 10)
                strcat(aux_dn, " ");
            strcat(aux_dn, aux_dn_m);
            strcat(aux_dn, " ");
            strcat(aux_dn, "/");
            strcat(aux_dn, " ");
            if (studenti[i].dn.zi < 10)
                strcat(aux_dn, " ");
            strcat(aux_dn, aux_dn_d);
            mvaddstr(5 + k, xdn, aux_dn);

            itoa(studenti[i].grupa, aux_g, 10);
            mvaddstr(5 + k, xg - 1, aux_g);

            mvaddstr(5 + k, xm - strlen(ftoa(studenti[i].medie)), ftoa(studenti[i].medie));

            itoa(studenti[i].val_bursa, aux_vb, 10);
            mvaddstr(5 + k, xvb - strlen(aux_vb), aux_vb);

            mvaddstr(5 + k, xprom, database_ver_corigent(i) ? "Da" : "Nu");
            k++;
        }
    }
    char nstud_aux[ncif(INT32_MAX) + strlen(" Studenti") + 1];
    itoa(k - 1, nstud_aux, 10);
    if (k == 1)
        strcat(nstud_aux, " Student");
    else
    strcat(nstud_aux, " Studenti");

    for (int i = 1; i < COLS - 1; i++)
        mvaddstr(LINES - 2, i, ui_symb_line_h);
    mvaddstr(LINES - 2, 2, nstud_aux);
}

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

    // Fereastra cautare
    for (int i = 1; i < w2x0; i++)
        mvaddstr(4, i, ui_symb_line_h);
    mvaddstr(3, 2, "Cautare:");

    // Indicatii taste
    char aux_indicatii[] = "ESC=Iesire   A=Adaugare   D=Stergere   C=Cautare   S=Sortare   B=Bursier   G=Grupa   P=Promovat";
    mvaddstr(LINES - 1, COLS / 2 - strlen(aux_indicatii) / 2, aux_indicatii);

    // Optiuni
    int set_sortare = 1;
    // 0: Alfabetica
    // 1: Cod
    // 2: Grupa
    // 3: Medie (desc)
    // 4: Grupa + Medie
    mvaddstr(4 + set_sortare, w2x0 + 2, "*");

    int set_bursier = 0;
    // 0 = -
    // 1 = nu
    // 2 = da
    char set_bursier_aux[] = "-";
    mvaddstr(10, COLS - 3, set_bursier_aux);

    int set_grupa = 0;
    char set_grupa_aux[] = "-";
    mvaddstr(11, COLS - 2 - strlen(set_grupa_aux), set_grupa_aux);

    int set_promovare = 0;
    // 0 = -
    // 1 = nu
    // 2 = da
    char set_promovare_aux[] = "-";
    mvaddstr(12, COLS - 3, set_promovare_aux);

    int oy = 6, ox = 1, height = LINES - 8;
    int y = oy;

    ui_draw_database_refresh(set_sortare, set_bursier, set_grupa, set_promovare, height, w2x0 - 1);

    refresh();

    move(y, ox);

    bool run = true;
    while (run)
    {
        int key = getch();
        switch (key)
        {
        case controls_arr_down:
            y = std::min(y + 1, oy + height - 1);
            move(y, ox);
            break;
        case controls_arr_up:
            y = std::max(y - 1, oy);
            move(y, ox);
            break;

        case controls_backsp:
        case controls_backsp_2:
            break;

        case controls_esc:
            run = false;
            break;

        case controls_enter:
        case controls_enter_2:
            break;

        case 99: // C
            break;

        case 115: // S
            mvaddstr(4 + set_sortare, w2x0 + 2, " ");
            set_sortare++;
            set_sortare %= 5;
            mvaddstr(4 + set_sortare, w2x0 + 2, "*");
            ui_draw_database_refresh(set_sortare, set_bursier, set_grupa, set_promovare, height, w2x0 - 1);
            break;

        case 98: // B
            set_bursier++;
            set_bursier %= 3;
            switch (set_bursier)
            {
            case 0:
                strcpy(set_bursier_aux, "-");
                break;
            case 1:
                strcpy(set_bursier_aux, "N");
                break;
            case 2:
                strcpy(set_bursier_aux, "D");
                break;
            }
            ui_draw_database_refresh(set_sortare, set_bursier, set_grupa, set_promovare, height, w2x0 - 1);
            mvaddstr(10, COLS - 3, set_bursier_aux);
            break;

        case 112: // P
            set_promovare++;
            set_promovare %= 3;
            switch (set_promovare)
            {
            case 0:
                strcpy(set_promovare_aux, "-");
                break;
            case 1:
                strcpy(set_promovare_aux, "N");
                break;
            case 2:
                strcpy(set_promovare_aux, "D");
                break;
            }
            ui_draw_database_refresh(set_sortare, set_bursier, set_grupa, set_promovare, height, w2x0 - 1);
            mvaddstr(12, COLS - 3, set_promovare_aux);
            break;

        case 100: // D

            break;

        case 97: // A

            break;

        case 103: // G
            move(11, COLS - 2);
            bool run_aux = true;
            while (run_aux)
            {
                int key = getch();
                switch (key)
                {
                case controls_enter:
                case controls_enter_2:
                case controls_esc:
                    run_aux = false;
                    break;

                case controls_backsp:
                case controls_backsp_2:
                    set_grupa /= 10;
                    if (set_grupa)
                        itoa(set_grupa, set_grupa_aux, 10);
                    else
                        strcpy(set_grupa_aux, "-");
                    break;

                default:
                    if (48 <= key && key <= 57)
                    {
                        if (set_grupa <= INT32_MAX / 100)
                        {
                            set_grupa *= 10;
                            if (key != 48)
                                set_grupa += key - 48;
                        }
                        itoa(set_grupa, set_grupa_aux, 10);
                    }
                    break;
                }
                ui_draw_database_refresh(set_sortare, set_bursier, set_grupa, set_promovare, height, w2x0 - 1);
                mvaddstr(11, w2x0 + 2 + strlen("Grupa:"), "         ");
                mvaddstr(11, COLS - 2 - strlen(set_grupa_aux), set_grupa_aux);
            }
            move(y, ox);
            break;
        }
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