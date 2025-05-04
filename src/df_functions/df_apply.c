/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_apply
*/

#include "dataframe.h"

static void apply(dataframe_t *applied, int i,
    void *(*apply_func)(void *value))
{
    linked_list_t *current = *applied->storage;

    for (; current != NULL; current = current->next) {
        current->data[i] = apply_func(current->data[i]);
    }
}

dataframe_t *df_apply(dataframe_t *dataframe, const char *column,
    void *(*apply_func)(void *value))
{
    dataframe_t *applied = NULL;

    if (dataframe == NULL ||
    check_column(dataframe, column) == 0)
        return NULL;
    applied = dup_data(dataframe);
    for (int i = 0; i < applied->nb_cols; i++) {
        if (strcmp(applied->column_names[i], column) == 0)
            apply(applied, i, apply_func);
    }
    return applied;
}
