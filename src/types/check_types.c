/*
** EPITECH PROJECT, 2025
** bscuddle
** File description:
** check_types
*/

#include "dataframe.h"

int is_int(char *str)
{
    int i = (str[0] == '-') ? 1 : 0;

    for (; i < (int) strlen(str); i++) {
        if (str[i] > '9' || str[i] < '0')
            return 0;
    }
    return 1;
}

int is_uint(char *str)
{
    for (int i = 0; i < (int) strlen(str); i++) {
        if (str[i] > '9' || str[i] < '0') {
            return 0;
        }
    }
    return 1;
}

int is_float(char *str)
{
    int i = (str[0] == '-') ? 1 : 0;
    int is_comma = 0;

    for (; i < (int) strlen(str); i++) {
        is_comma = (str[i] == '.') ? is_comma + 1 : is_comma;
        if ((str[i] == '.' && is_comma <= 1) ||
            (str[i] >= '0' && str[i] <= '9'))
            continue;
        return 0;
    }
    return 1;
}

int is_bool(char *str)
{
    char *str_cpy = strdup(str);

    for (size_t i = 0; i < strlen(str_cpy); i++)
        str_cpy[i] = tolower(str_cpy[i]);
    if (strcmp(str_cpy, "true") == 0 || strcmp(str_cpy, "false") == 0) {
        free(str_cpy);
        return 1;
    }
    free(str_cpy);
    return 0;
}
