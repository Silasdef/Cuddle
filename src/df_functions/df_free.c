/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_infos.c
*/

#include "dataframe.h"

void free_array(dataframe_t *dataframe)
{
    for (int i = 0; i < dataframe->nb_cols; i++)
        free(dataframe->column_names[i]);
    free(dataframe->column_names);
}

void df_free(dataframe_t *dataframe)
{
    linked_list_t *head = *dataframe->storage;
    linked_list_t *current = NULL;

    while (head != NULL) {
        current = head;
        for (int j = 0; j < dataframe->nb_cols; j++)
            free(head->data[j]);
        free(head->data);
        head = current->next;
        free(current);
    }
    free(dataframe->storage);
    free_array(dataframe);
    free(dataframe->separator);
    free(dataframe->column_types);
    free(dataframe);
}
