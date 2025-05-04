/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** dup_functions
*/

#include "dataframe.h"

void *dup_int_string(dataframe_t *data,
    int i, void **array, void *new_data)
{
    int size = 0;

    if (data->column_types[i] == INT) {
        size = sizeof(int);
        new_data = malloc(size);
        memcpy(new_data, array[i], size);
        return new_data;
    }
    if (data->column_types[i] == STRING) {
        new_data = strdup((char *)array[i]);
        return new_data;
    }
    return NULL;
}

void *dup_float_uint_bool(dataframe_t *data,
    int i, void **array, void *new_data)
{
    int size = sizeof(unsigned int);

    if (data->column_types[i] == UINT) {
        new_data = malloc(size);
        memcpy(new_data, array[i], size);
        return new_data;
    }
    if (data->column_types[i] == FLOAT) {
        size = sizeof(float);
        new_data = malloc(size);
        memcpy(new_data, array[i], size);
        return new_data;
    }
    if (data->column_types[i] == BOOL) {
        size = sizeof(int);
        new_data = malloc(size);
        memcpy(new_data, array[i], size);
        return new_data;
    }
    return NULL;
}

void *dup_type(dataframe_t *data, int i, void **array)
{
    void *new = NULL;

    new = dup_int_string(data, i, array, new);
    if (new != NULL)
        return new;
    return dup_float_uint_bool(data, i, array, new);
}

void **dup_array(dataframe_t *data, void **array)
{
    void **new_array = NULL;

    if (data == NULL)
        return NULL;
    new_array = malloc(sizeof(void *) *(data->nb_cols + 1));
    if (new_array == NULL)
        return NULL;
    for (int i = 0; i < data->nb_cols; i++)
        new_array[i] = dup_type(data, i, array);
    new_array[data->nb_cols] = NULL;
    return new_array;
}
