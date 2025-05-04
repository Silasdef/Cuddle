/*
** EPITECH PROJECT, 2025
** bscuddle
** File description:
** utilities
*/

#include "dataframe.h"

int get_size(const char *filename)
{
    struct stat sb;

    lstat(filename, &sb);
    return sb.st_size;
}

void set_data_column_types(dataframe_t *data, int column_counter)
{
    data->column_types = malloc(sizeof(column_type_t) * (column_counter));
    if (data->column_types == NULL)
        return;
    for (int i = 0; i < column_counter; i++)
        (data->column_types)[i] = UNDEFINED;
}

file_t *create_file_struct(FILE *fp, int file_size,
    const char *separator, char *buffer)
{
    file_t *myfile = malloc(sizeof(file_t));

    myfile->fp = fp;
    myfile->file_size = file_size;
    myfile->separator = separator;
    myfile->buffer = buffer;
    return myfile;
}

void clean_all(FILE *fp, char *buffer, file_t *myfile)
{
    fclose(fp);
    free(buffer);
    free(myfile);
}

void my_rev_list(linked_list_t **begin)
{
    linked_list_t *now = *begin;
    linked_list_t *before = NULL;
    linked_list_t *next;

    while (now != NULL){
        next = now->next;
        now->next = before;
        before = now;
        now = next;
    }
    *begin = before;
}
