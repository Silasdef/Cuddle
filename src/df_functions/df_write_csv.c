/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_infos.c
*/

#include "dataframe.h"

static void write_column_name(FILE *file, dataframe_t *dataframe)
{
    for (int i = 0; i < dataframe->nb_cols; i++) {
        fprintf(file, "%s", dataframe->column_names[i]);
        if (i + 1 < dataframe->nb_cols)
            fprintf(file, "%s", dataframe->separator);
    }
    fprintf(file, "\n");
}

static void write_data(FILE *file, linked_list_t *head, dataframe_t *dataframe)
{
    for (int i = 0; i < dataframe->nb_cols; i++) {
        if (dataframe->column_types[i] == INT)
            fprintf(file, "%d", *(int *)head->data[i]);
        if (dataframe->column_types[i] == FLOAT)
            fprintf(file, "%.2f", *(float *)head->data[i]);
        if (dataframe->column_types[i] == UINT)
            fprintf(file, "%u", *(unsigned int *)head->data[i]);
        if (dataframe->column_types[i] == STRING)
            fprintf(file, "%s", (char *)head->data[i]);
        if (dataframe->column_types[i] == BOOL)
            fprintf(file, "%s", ((char *)head->data[i]));
        if (i + 1 < dataframe->nb_cols)
            fprintf(file, "%s", dataframe->separator);
    }
    fprintf(file, "\n");
}

int df_write_csv(dataframe_t *dataframe, const char *filename)
{
    FILE *file = NULL;
    linked_list_t *head = NULL;

    if (dataframe == NULL)
        return 84;
    file = fopen(filename, "w");
    if (file == NULL)
        return 84;
    head = *dataframe->storage;
    write_column_name(file, dataframe);
    while (head != NULL) {
        write_data(file, head, dataframe);
        head = head->next;
    }
    fclose(file);
    return 0;
}
