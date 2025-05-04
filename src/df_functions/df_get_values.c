/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_get_value
*/

#include "dataframe.h"

void **find_values(dataframe_t *data, int nb_column)
{
    linked_list_t *head = *data->storage;
    void **array = malloc(sizeof(void *) * (data->nb_rows + 1));

    for (int i = 0; i != data->nb_rows; i++) {
        array[i] = dup_type(data, nb_column, head->data);
        head = head->next;
    }
    array[data->nb_rows] = NULL;
    return array;
}

void **df_get_values(dataframe_t *dataframe, const char *column)
{
    if (dataframe == NULL
        || check_column(dataframe, column) == 0)
        return NULL;
    for (int i = 0; i < dataframe->nb_cols; i++) {
        if (strcmp(dataframe->column_names[i], column) == 0)
            return find_values(dataframe, i);
    }
    return NULL;
}
