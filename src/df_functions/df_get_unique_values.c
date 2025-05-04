/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_get_value
*/

#include "dataframe.h"

static int is_same(int type, void **array, void *value)
{
    for (int i = 0; array[i] != NULL; i++) {
        if ((type == STRING && strcmp(array[i], value) == 0)
        || (type == INT && *(int *)array[i] == *(int *)value)
        || (type == UINT
        && *(unsigned int *)array[i] == *(unsigned int *)value)
        || (type == FLOAT && *(float *)array[i] == *(float *)value))
            return 0;
    }
    return 1;
}

void **find_unique_values(dataframe_t *data, int nb_column)
{
    linked_list_t *head = *data->storage;
    void **array = malloc(sizeof(void *) * (data->nb_rows + 1));
    int index = 0;

    for (int i = 0; i != data->nb_rows; i++) {
        array[index] = NULL;
        if (is_same(data->column_types[nb_column],
            array, head->data[nb_column])) {
            array[index] = dup_type(data, nb_column, head->data);
            index++;
        }
        head = head->next;
    }
    array[index] = NULL;
    return array;
}

void **df_get_unique_values(dataframe_t *dataframe, const char *column)
{
    if (dataframe == NULL
        || check_column(dataframe, column) == 0)
        return NULL;
    for (int i = 0; i < dataframe->nb_cols; i++) {
        if (strcmp(dataframe->column_names[i], column) == 0)
            return find_unique_values(dataframe, i);
    }
    return NULL;
}
