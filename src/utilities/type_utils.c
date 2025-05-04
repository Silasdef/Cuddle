/*
** EPITECH PROJECT, 2025
** Visual Studio Live Share (Workspace)
** File description:
** type_utils
*/

#include "dataframe.h"

int my_str_isnum(char *str)
{
    for (size_t i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i]))
            return 0;
    }
    return 1;
}

int num_to_int(linked_list_t *current, int i, double val)
{
    int *new_val = malloc(sizeof(int));

    if (!new_val)
        return 0;
    *new_val = (int) val;
    current->data[i] = (void *) new_val;
    return 1;
}

int num_to_float(linked_list_t *current, int i, double val)
{
    float *new_val = malloc(sizeof(float));

    if (!new_val)
        return 0;
    *new_val = (float) val;
    current->data[i] = (void *) new_val;
    return 1;
}

int num_to_uint(linked_list_t *current, int i, double val)
{
    unsigned int *new_val = malloc(sizeof(unsigned int));

    if (!new_val || val < 0)
        return 0;
    *new_val = (unsigned int) val;
    current->data[i] = (void *) new_val;
    return 1;
}
