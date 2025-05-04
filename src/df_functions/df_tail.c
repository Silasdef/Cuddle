/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_tail_csv_2
*/

#include "dataframe.h"

static linked_list_t *get_starting_node(linked_list_t *head, int start_index)
{
    while (start_index > 0 && head != NULL) {
        start_index--;
        head = head->next;
    }
    return head;
}

static linked_list_t *store_tail_data(dataframe_t *data, int nb_rows)
{
    linked_list_t *head = get_starting_node(*data->storage,
        data->nb_rows - nb_rows < 0 ? 0 : data->nb_rows - nb_rows);
    linked_list_t *new_head = NULL;
    linked_list_t *current = NULL;
    linked_list_t *new_node = NULL;

    for (int i = 0; i < nb_rows && head; i++) {
        new_node = malloc(sizeof(linked_list_t));
        if (new_node == NULL)
            return NULL;
        new_node->data = dup_array(data, head->data);
        new_node->next = NULL;
        if (!new_head)
            new_head = new_node;
        else
            current->next = new_node;
        current = new_node;
        head = head->next;
    }
    return new_head;
}

dataframe_t *df_tail(dataframe_t *dataframe, int nb_rows)
{
    dataframe_t *new_data = malloc(sizeof(dataframe_t));

    if (!new_data || nb_rows < 0 || dataframe == NULL) {
        free(new_data);
        return NULL;
    }
    new_data->column_names = get_column_names(dataframe);
    new_data->column_types = get_type(dataframe);
    new_data->nb_cols = dataframe->nb_cols;
    new_data->nb_rows = nb_rows;
    new_data->separator = strdup(dataframe->separator);
    new_data->storage = malloc(sizeof(linked_list_t *));
    if (!new_data->storage) {
        free(new_data);
        return NULL;
    }
    *new_data->storage = store_tail_data(dataframe, new_data->nb_rows);
    return new_data;
}
