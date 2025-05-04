/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** type_conversion
*/

#include "dataframe.h"
#include <stdlib.h>
#include <stdio.h>

static char *fill_str(int num, int len, int is_negative)
{
    char *str = (char *) malloc(len + 1);
    int abs_num = 0;

    if (str == NULL)
        return NULL;
    str[len] = '\0';
    abs_num = (num < 0) ? -num : num;
    for (int i = len - 1; i >= is_negative; i--) {
        str[i] = (abs_num % 10) + '0';
        abs_num /= 10;
    }
    return str;
}

char *int_to_string(int num)
{
    int len = 0;
    int is_negative = 0;
    int n = num;
    char *str = NULL;

    if (num < 0) {
        is_negative = 1;
        n = -num;
    }
    do {
        len++;
        n /= 10;
    } while (n > 0);
    len += is_negative;
    str = fill_str(num, len, is_negative);
    if (is_negative)
        str[0] = '-';
    return str;
}

char *uint_to_string(unsigned int num)
{
    int len = 0;
    unsigned int n = num;
    char *str = NULL;

    do {
        len++;
        n /= 10;
    } while (n > 0);
    str = (char *) malloc(len + 1);
    if (str == NULL)
        return NULL;
    str[len] = '\0';
    for (int i = len - 1; i >= 0; i--) {
        str[i] = (num % 10) + '0';
        num /= 10;
    }
    return str;
}

static char *build_frac_str(unsigned int frac_int, int precision)
{
    char *str = malloc(precision + 1);

    if (!str)
        return NULL;
    str[precision] = '\0';
    for (int i = precision - 1; i >= 0; i--) {
        str[i] = (frac_int % 10) + '0';
        frac_int /= 10;
    }
    return str;
}

static void fill_both(char *res, char **int_frac,
    int int_len, int *pos)
{
    int prec = 6;

    for (int i = 0; i < int_len; i++) {
        res[*pos] = int_frac[0][i];
        (*pos)++;
    }
    res[*pos] = '.';
    (*pos)++;
    for (int i = 0; i < prec; i++) {
        res[*pos] = int_frac[1][i];
        (*pos)++;
    }
}

static char *assemble_float_str(char **int_frac, int is_negative)
{
    int int_len = strlen(int_frac[0]);
    int prec = strlen(int_frac[1]);
    int total_len = (is_negative ? 1 : 0) + int_len + 1 + prec;
    char *res = malloc(total_len + 1);
    int pos = 0;

    if (!res)
        return NULL;
    if (is_negative) {
        res[pos] = '-';
        pos++;
    }
    fill_both(res, int_frac, int_len, &pos);
    res[pos] = '\0';
    return res;
}

static char **fill_int_frac(float num)
{
    int int_part = 0;
    float frac_part = 0;
    char *int_str = NULL;
    char *frac_str = NULL;
    unsigned int frac_int = 0;
    int precision = 6;
    char **int_frac = malloc(sizeof(char *) * 2);

    int_part = (int)num;
    frac_part = num - int_part;
    int_str = uint_to_string((unsigned int)int_part);
    if (!int_str)
        return NULL;
    frac_int = (unsigned int)(frac_part * pow(10, precision) + 0.5);
    frac_str = build_frac_str(frac_int, precision);
    int_frac[0] = int_str;
    int_frac[1] = frac_str;
    return int_frac;
}

char *float_to_string(float num)
{
    int is_negative = 0;
    char *result = NULL;
    char **int_frac = NULL;

    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    int_frac = fill_int_frac(num);
    result = assemble_float_str(int_frac, is_negative);
    free(int_frac[0]);
    free(int_frac[1]);
    free(int_frac);
    return result;
}
