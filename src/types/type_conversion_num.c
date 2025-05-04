/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** type_conversion_num
*/

#include "dataframe.h"

void convert_string_to_int(linked_list_t *current, int i)
{
    int converted_int = 0;

    converted_int = atoi((char *) current->data[i]);
    free(current->data[i]);
    current->data[i] = malloc(sizeof(int));
    if (!current->data[i])
        return;
    *(int *) current->data[i] = converted_int;
}

void convert_string_to_uint(linked_list_t *current, int i)
{
    int converted_uint = 0;

    converted_uint = strtoul((char *) current->data[i], NULL, 10);
    free(current->data[i]);
    current->data[i] = malloc(sizeof(unsigned int));
    if (!current->data[i])
        return;
    *(unsigned int *) current->data[i] = converted_uint;
}

void convert_string_to_float(linked_list_t *current, int i)
{
    float converted_float = 0;

    converted_float = atof((char *) current->data[i]);
    free(current->data[i]);
    current->data[i] = malloc(sizeof(float));
    if (!current->data[i])
        return;
    *(float *) current->data[i] = converted_float;
}
