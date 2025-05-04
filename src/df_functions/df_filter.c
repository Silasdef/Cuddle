/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_filter
*/

#include "dataframe.h"

static int find_nb_column(dataframe_t *data, const char *column)
{
    for (int i = 0; i < data->nb_cols; i++) {
        if (strcmp(data->column_names[i], column) == 0)
            return i;
    }
    return 0;
}

static linked_list_t *create_new_node(dataframe_t *data, void **data_row)
{
    linked_list_t *new_node = malloc(sizeof(linked_list_t));

    if (!new_node)
        return NULL;
    new_node->data = dup_array(data, data_row);
    new_node->next = NULL;
    return new_node;
}

static linked_list_t *store_filter_data(dataframe_t *data,
    bool(*filter_func)(void *value), int nb_column, linked_list_t *current)
{
    linked_list_t *head = *data->storage;
    linked_list_t *new_head = NULL;
    linked_list_t *new_node = NULL;

    for (int i = 0; i < data->nb_rows; i++) {
        if (!filter_func(head->data[nb_column])) {
            head = head->next;
            continue;
        }
        new_node = create_new_node(data, head->data);
        if (!new_node)
            return NULL;
        if (!new_head)
            new_head = new_node;
        else
            current->next = new_node;
        current = new_node;
        head = head->next;
    }
    return new_head;
}

dataframe_t *init_dataframe(dataframe_t *dataframe, const char *column)
{
    dataframe_t *new_data = malloc(sizeof(dataframe_t));

    if (!new_data || dataframe == NULL
        || check_column(dataframe, column) == 0) {
        free(new_data);
        return NULL;
    }
    new_data->column_names = get_column_names(dataframe);
    new_data->column_types = get_type(dataframe);
    new_data->nb_cols = dataframe->nb_cols;
    new_data->separator = strdup(dataframe->separator);
    new_data->storage = malloc(sizeof(linked_list_t *));
    if (!new_data->storage) {
        free(new_data);
        return NULL;
    }
    return new_data;
}

dataframe_t *df_filter(dataframe_t *dataframe,
    const char *column, bool(*filter_func)(void *value))
{
    dataframe_t *new_data = NULL;
    linked_list_t *current = NULL;

    new_data = init_dataframe(dataframe, column);
    if (!new_data)
        return NULL;
    *new_data->storage = store_filter_data(dataframe,
        filter_func, find_nb_column(dataframe, column), current);
    new_data->nb_rows = 0;
    return new_data;
}
