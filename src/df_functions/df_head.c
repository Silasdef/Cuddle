/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_head_csv_2
*/

#include "dataframe.h"

static linked_list_t *store_head_data(dataframe_t *data, int nb_rows)
{
    linked_list_t *head = *data->storage;
    linked_list_t *new_head = NULL;
    linked_list_t *current = NULL;
    linked_list_t *new_node = NULL;

    for (int i = 0; i < nb_rows; i++) {
        new_node = malloc(sizeof(linked_list_t));
        if (!new_node)
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

column_type_t *get_type(dataframe_t *dataframe)
{
    column_type_t *type = malloc(sizeof(column_type_t) * dataframe->nb_cols);

    if (type == NULL)
        return NULL;
    for (int i = 0; i < dataframe->nb_cols; i++)
        type[i] = dataframe->column_types[i];
    return type;
}

char **get_column_names(dataframe_t *dataframe)
{
    char **array = malloc(sizeof(char *) * (dataframe->nb_cols + 1));

    if (array == NULL)
        return NULL;
    for (int i = 0; i < dataframe->nb_cols; i++)
        array[i] = strdup(dataframe->column_names[i]);
    array[dataframe->nb_cols] = NULL;
    return array;
}

dataframe_t *df_head(dataframe_t *dataframe, int nb_rows)
{
    dataframe_t *new_data = malloc(sizeof(dataframe_t));

    if (!new_data || nb_rows < 0 || dataframe == NULL) {
        free(new_data);
        return NULL;
    }
    new_data->column_names = get_column_names(dataframe);
    new_data->column_types = get_type(dataframe);
    new_data->nb_cols = dataframe->nb_cols;
    new_data->nb_rows =
    (nb_rows > dataframe->nb_rows) ? dataframe->nb_rows : nb_rows;
    new_data->separator = strdup(dataframe->separator);
    new_data->storage = malloc(sizeof(linked_list_t *));
    if (!new_data->storage) {
        free(new_data);
        return NULL;
    }
    *new_data->storage = store_head_data(dataframe, new_data->nb_rows);
    return new_data;
}
