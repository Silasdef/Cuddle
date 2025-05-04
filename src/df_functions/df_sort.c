/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_sort
*/

#include "dataframe.h"

static void check_node_swapping(int *sorted, int i, linked_list_t *dummy,
    bool (*sort_func)(void *value1, void *value_2))
{
    linked_list_t *prev = dummy;
    linked_list_t *curr = dummy->next;
    linked_list_t *tmp = NULL;

    while (curr && curr->next) {
        if (sort_func(curr->data[i], curr->next->data[i])) {
            tmp = curr->next;
            curr->next = tmp->next;
            tmp->next = curr;
            prev->next = tmp;
            *sorted = 0;
        }
        prev = prev->next;
        curr = prev->next;
    }
}

static void store_data(dataframe_t *new,
    bool (*sort_func)(void *value1, void *value_2), int i)
{
    linked_list_t dummy;
    int sorted = 1;

    dummy.next = *new->storage;
    do {
        sorted = 1;
        check_node_swapping(&sorted, i, &dummy, sort_func);
    } while (!sorted);
    *new->storage = dummy.next;
}

static dataframe_t *dup_sort_data(dataframe_t *dataframe, int column_index,
    bool (*sort_func)(void *value1, void *value_2))
{
    dataframe_t *new = NULL;

    new = dup_data(dataframe);
    store_data(new, sort_func, column_index);
    return new;
}

dataframe_t *df_sort(dataframe_t *dataframe, const char *column,
    bool (*sort_func)(void *value1, void *value_2))
{
    int column_index = -1;

    if (check_column(dataframe, column) == 0)
        return NULL;
    for (int i = 0; i < dataframe->nb_cols; i++) {
        if (strcmp(dataframe->column_names[i], column) == 0) {
            column_index = i;
            break;
        }
    }
    if (column_index == -1)
        return NULL;
    return dup_sort_data(dataframe, column_index, sort_func);
}
