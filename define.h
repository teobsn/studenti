// File names
#define settings_filename "settings.ini"
#define database_filename "database.csv"

// File max line length
#define settings_maxlinelength 256
#define database_maxlinelength 256

// Database parameter sizes/lengths
#define database_n_maxlength 96
#define database_pn_maxlength 96
#define database_nparam 9
#define database_size 2048
#define database_ngrupe 8

// UI
#define ui_maxlength 128

#define ui_symb_selector ">"

// https://en.wikipedia.org/wiki/Box-drawing_character
#define ui_symb_line_v "|"
#define ui_symb_line_h "-"
#define ui_symb_line_ul "+"
#define ui_symb_line_ur "+"
#define ui_symb_line_dl "+"
#define ui_symb_line_dr "+"

#define ui_symb_line_vl "+"
#define ui_symb_line_vr "+"
#define ui_symb_line_hu "+"
#define ui_symb_line_hd "+"

#define ui_symb_corner "+"

// Keybinds
#define controls_arr_left KEY_LEFT
#define controls_arr_right KEY_RIGHT
#define controls_arr_up KEY_UP
#define controls_arr_down KEY_DOWN

#define controls_enter KEY_ENTER
#define controls_enter_2 10

#define controls_backsp KEY_BACKSPACE
#define controls_backsp_2 127
#define controls_esc 27 // ESC or ALT https://stackoverflow.com/questions/5977395/ncurses-and-esc-alt-keys