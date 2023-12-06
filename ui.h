#include "define.h"
#include <ncurses.h>

char ui_menu_opts1[][ui_maxlength] = {
    // https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
    "Baza de date",
    "Setari",
    "Despre",
};

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
        case 50: // 2
        case 115: // S
            y = oy + 1;
            run = false;
            break;
        case 51: // 3
        case 100: // D
            y = oy + 2;
            run = false;
            break;
        }
        mvaddstr(y, ox, ui_symb_selector);
        move(y, ox);
    }

    return y;
}

void ui_draw_database()
{

}

void ui_draw_settings()
{

}

void ui_draw_about()
{

}

void ui_draw_mainmenu()
{
    int k = -2;
    for (int i = 0; i <= 2; i++)
        mvaddstr(LINES / 2 + k + i, COLS / 2 + 1, ui_menu_opts1[i]);

    // https://pubs.opengroup.org/onlinepubs/7908799/xcurses/chgat.html
    // https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/attrib.html
    mvchgat(LINES / 2 + k + 0, COLS / 2 + 1, 1, A_UNDERLINE, NULL, NULL);
    mvchgat(LINES / 2 + k + 1, COLS / 2 + 1, 1, A_UNDERLINE, NULL, NULL);
    mvchgat(LINES / 2 + k + 2, COLS / 2 + 1, 1, A_UNDERLINE, NULL, NULL);

    int r = ui_input_arrowmenu1(3, LINES / 2 + k, COLS / 2 - 1);
    switch(r)
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
    }
}

void ui_start()
{
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    ui_draw_mainmenu();
}