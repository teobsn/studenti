#include <cstring>
#include "define.h"

int search_comparison(char s[], char c[])
{
    char *r = strstr(s, c);
    if (r)
        return r - s;
    else
        return -1;
}