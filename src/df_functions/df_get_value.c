/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_get_value
*/

#include "dataframe.h"

int check_column(dataframe_t *data, const char *column)
{
    for (int i = 0; i < data->nb_cols; i++) {
        if (strcmp(data->column_names[i], column) == 0)
            return 1;
    }
    return 0;
}

void *find_value(dataframe_t *data, int row, int nb_column)
{
    linked_list_t *head = *data->storage;

    for (int i = 0; i != row; i++)
        head = head->next;
    return head->data[nb_column];
}

void *df_get_value(dataframe_t *dataframe, int row, const char *column)
{
    if (dataframe == NULL || dataframe->nb_rows < row
        || check_column(dataframe, column) == 0)
        return NULL;
    for (int i = 0; i < dataframe->nb_cols; i++) {
        if (strcmp(dataframe->column_names[i], column) == 0)
            return find_value(dataframe, row, i);
    }
    return NULL;
}
