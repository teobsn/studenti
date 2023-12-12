#include <cstring>
#include "define.h"

int search_comparison(char s[], char c[])
{
    if (strlen(c) < search_minlength)
        return -2;

    char aux[database_n_maxlength + database_pn_maxlength + 1];
    for (int i = 0; i < std::strlen(s) - strlen(c); i++)
    {
        strncpy(aux, s + i, strlen(c));
        aux[strlen(c)] = '\0';
        if (!strcmp(aux, c))
            return i;
    }

    return -1;
}

