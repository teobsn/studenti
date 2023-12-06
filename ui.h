#include "define.h"
#include <ncurses.h>
#include <cstring>

bool ui_exit = false;

char ui_menu_opts1[][ui_maxlength] = {
    "Baza de date",
    "Setari",
    "Despre",
    "Iesire"};

char ui_about_1[][ui_maxlength] = {
    "Andrei Angelo-Iustin",
    "Bostan Codrut-Teodor",
    "Matei Daria",
    "Jucan Alexandra"};

int ui_input_arrowmenu1(int height, int oy, int ox)
{
    mvaddstr(oy, ox, ui_symb_selector);
    move(oy, ox);
    refresh();

    int y = oy;

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

        case controls_enter:
        case controls_enter_2:
            run = false;
            break;

        case 49: // 1
        case 98: // B
            y = oy;
            run = false;
            break;
        case 50:  // 2
        case 115: // S
            y = oy + 1;
            run = false;
            break;
        case 51:  // 3
        case 100: // D
            y = oy + 2;
            run = false;
            break;
        case 52:  // 4
        case 105: // I
            y = oy + 3;
            run = false;
            break;
        }
        mvaddstr(y, ox, ui_symb_selector);
        move(y, ox);
    }

    return y - oy;
}

void ui_draw_database()
{
}

void ui_draw_settings()
{
}

void ui_draw_about()
{
    clear();
    int k = -2;
    for (int i = 0; i <= 3; i++)
    {
        attrset(A_BOLD | COLOR_PAIR(i + 1));
        mvaddstr(LINES / 2 + k + i, COLS / 2 - strlen(ui_about_1[i]) / 2, ui_about_1[i]);
        attroff(A_BOLD | COLOR_PAIR(i + 1));
    }

    mvaddstr(LINES / 2 + k - 1, COLS / 2 - strlen("Proiect realizat de:") / 2, "Proiect realizat de:");

    move(0, 0);

    refresh();

    bool run = true;
    while (run)
    {
        int key = getch();
        if ((key == controls_enter) || (key == controls_enter_2))
            clear(), run = false;
    }
}

void ui_draw_mainmenu()
{
    int k = -2;
    for (int i = 0; i <= 3; i++)
        mvaddstr(LINES / 2 + k + i, COLS / 2 + 1, ui_menu_opts1[i]);

    // https://pubs.opengroup.org/onlinepubs/7908799/xcurses/chgat.html
    // https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/attrib.html
    mvchgat(LINES / 2 + k + 0, COLS / 2 + 1, 1, A_UNDERLINE, NULL, NULL);
    mvchgat(LINES / 2 + k + 1, COLS / 2 + 1, 1, A_UNDERLINE, NULL, NULL);
    mvchgat(LINES / 2 + k + 2, COLS / 2 + 1, 1, A_UNDERLINE, NULL, NULL);
    mvchgat(LINES / 2 + k + 3, COLS / 2 + 1, 1, A_UNDERLINE, NULL, NULL);

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