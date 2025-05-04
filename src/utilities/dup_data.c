/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** dup_data
*/

#include "dataframe.h"

static char **dup_names(char **tab, int nb_rows, int nb_cols)
{
    char **my_tab = malloc(sizeof(char *) * (nb_rows + 1));
    int len = 0;

    if (my_tab == NULL)
        return NULL;
    for (int i = 0; i < nb_cols; i++) {
        my_tab[i] = strdup(tab[i]);
        len = i;
    }
    my_tab[len + 1] = NULL;
    return my_tab;
}

static column_type_t *dup_types(column_type_t *tab, int nb_cols)
{
    column_type_t *my_tab = malloc(sizeof(char *) * (nb_cols));

    if (my_tab == NULL)
        return NULL;
    for (int i = 0; i < nb_cols; i++)
        my_tab[i] = tab[i];
    return my_tab;
}

static void **fill_data(void **data,
    column_type_t *types, dataframe_t *dataframe)
{
    void **mydata = malloc(sizeof(void *) * dataframe->nb_cols);

    if (mydata == NULL)
        return mydata;
    for (int i = 0; i < dataframe->nb_cols; i++) {
        if (types[i] == INT || types[i] == FLOAT || types[i] == UINT) {
            mydata[i] = data[i];
        } else {
            mydata[i] = (void *) strdup((char *) data[i]);
        }
    }
    return mydata;
}

void dup_storage(dataframe_t *dataframe, dataframe_t *new)
{
    linked_list_t *current = *dataframe->storage;
    linked_list_t *new_node = NULL;
    linked_list_t **new_head = malloc(sizeof(linked_list_t *));

    *new_head = NULL;
    new->storage = new_head;
    for (; current != NULL; current = current->next) {
        new_node = malloc(sizeof(linked_list_t));
        if (new_node == NULL)
            return;
        new_node->data = fill_data(current->data,
            dataframe->column_types, dataframe);
        new_node->next = NULL;
        add_node(new, new_node);
    }
}

dataframe_t *dup_data(dataframe_t *dataframe)
{
    dataframe_t *new = malloc(sizeof(dataframe_t));

    new->nb_rows = dataframe->nb_rows;
    new->nb_cols = dataframe->nb_cols;
    new->column_names = dup_names(dataframe->column_names,
        dataframe->nb_rows, dataframe->nb_cols);
    new->column_types = dup_types(dataframe->column_types, dataframe->nb_cols);
    new->separator = strdup(dataframe->separator);
    dup_storage(dataframe, new);
    return new;
}
