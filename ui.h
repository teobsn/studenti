#include "define.h"
#include <cstring>

#ifdef __unix__
#include <ncurses.h>
#endif

#ifdef _WIN32
#include <curses.h>
#include <cstdint>
#endif

char ui_about_1[][ui_maxlength] = {
    "Andrei Angelo-Iustin",
    "Bostan Codrut-Teodor",
    "Matei Daria",
    "Jucan Alexandra"};

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

int ncif(int x)
{
    uint8_t n = 0;
    while (x)
        x /= 10, n++;
    return n;
}

char* itoa(int value, char* result, int base) { // https://stackoverflow.com/questions/8257714/how-can-i-convert-an-int-to-a-string-in-c
    // check that the base is valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
  
    // Reverse the string
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

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

    move(LINES - 1, COLS - 1);

    refresh();

    bool run = true;
    while (run)
    {
        int key = getch();
        if ((key == controls_enter) || (key == controls_enter_2) || (key == controls_esc))
            run = false;
    }
}