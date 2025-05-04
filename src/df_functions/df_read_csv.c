/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_read_csv_2
*/

#include "dataframe.h"

static int compute_columns(file_t *myfile)
{
    int counter = 1;
    char *token = NULL;

    fseek(myfile->fp, 0, SEEK_SET);
    fgets(myfile->buffer, myfile->file_size, myfile->fp);
    if (myfile->buffer[strlen(myfile->buffer) - 1] == '\n')
        myfile->buffer[strlen(myfile->buffer) - 1] = 0;
    myfile->buffer = strtok(myfile->buffer, myfile->separator);
    if (myfile->buffer == NULL)
        return 0;
    while (1) {
        token = strtok(NULL, myfile->separator);
        if (token == NULL)
            break;
        counter++;
    }
    return counter;
}

static char **get_names(dataframe_t *data, file_t *myfile)
{
    char **names = malloc(sizeof(char *) * (data->nb_cols + 1));
    char *token = NULL;

    if (names == NULL)
        return NULL;
    fseek(myfile->fp, 0, SEEK_SET);
    fgets(myfile->buffer, myfile->file_size, myfile->fp);
    if (myfile->buffer[strlen(myfile->buffer) - 1] == '\n')
        myfile->buffer[strlen(myfile->buffer) - 1] = 0;
    token = strtok(myfile->buffer, myfile->separator);
    if (token == NULL)
        return NULL;
    names[0] = strdup(token);
    for (int i = 1; i < data->nb_cols; i++) {
        token = strtok(NULL, myfile->separator);
        names[i] = strdup(token);
    }
    return names;
}

static void get_types(dataframe_t *data, file_t *myfile)
{
    data->column_types = malloc(sizeof(column_type_t) * data->nb_cols);
    if (data->column_types == NULL)
        return;
    for (int i = 0; i < data->nb_cols; i++)
        data->column_types[i] = UNDEFINED;
    fseek(myfile->fp, 0, SEEK_SET);
    fgets(myfile->buffer, myfile->file_size, myfile->fp);
    if (myfile->buffer[strlen(myfile->buffer) - 1] == '\n')
        myfile->buffer[strlen(myfile->buffer) - 1] = 0;
    while (fgets(myfile->buffer, myfile->file_size, myfile->fp) != NULL) {
        if (myfile->buffer[strlen(myfile->buffer) - 1] == '\n')
            myfile->buffer[strlen(myfile->buffer) - 1] = 0;
        activate_types(data, myfile);
    }
}

static void *convert_type(char *token, column_type_t type, file_t *myfile)
{
    switch (type) {
        case INT:
            myfile->value_int = malloc(sizeof(int));
            *(myfile->value_int) = atoi(token);
            return (void *) (myfile->value_int);
        case UINT:
            myfile->value_uint = malloc(sizeof(unsigned int));
            *(myfile->value_uint) = strtoul(token, NULL, 10);
            return (void *) (myfile->value_uint);
        case FLOAT:
            myfile->value_float = malloc(sizeof(float));
            *(myfile->value_float) = atof(token);
            return (void *) (myfile->value_float);
        case STRING:
            return (void *) strdup(token);
        case BOOL:
            return (void *) strdup(token);
        default:
            return NULL;
    }
}

static void get_elem_from_type(dataframe_t *data, file_t *myfile,
    char *token, int i)
{
    column_type_t type = data->column_types[i];
    void *result = convert_type(token, type, myfile);

    myfile->data_tab[i] = result;
}

static void create_tab(dataframe_t *data, file_t *myfile)
{
    char *token = strtok(myfile->buffer, myfile->separator);
    int i = 0;

    myfile->data_tab = malloc(sizeof(void *) * (data->nb_cols + 1));
    get_elem_from_type(data, myfile, token, i);
    while (1) {
        token = strtok(NULL, myfile->separator);
        if (token == NULL)
            break;
        i++;
        get_elem_from_type(data, myfile, token, i);
    }
}

void add_node(dataframe_t *data, linked_list_t *node)
{
    linked_list_t *current = *(data->storage);

    if (*(data->storage) == NULL) {
        *(data->storage) = node;
        return;
    }
    for (; current->next != NULL; current = current->next);
    current->next = node;
}

static void get_storage(dataframe_t *data, file_t *myfile)
{
    linked_list_t *node = NULL;

    fseek(myfile->fp, 0, SEEK_SET);
    fgets(myfile->buffer, myfile->file_size, myfile->fp);
    while (fgets(myfile->buffer, myfile->file_size, myfile->fp) != NULL) {
        if (myfile->buffer[strlen(myfile->buffer) - 1] == '\n')
            myfile->buffer[strlen(myfile->buffer) - 1] = 0;
        create_tab(data, myfile);
        node = malloc(sizeof(linked_list_t));
        node->data = myfile->data_tab;
        node->next = NULL;
        add_node(data, node);
    }
}

static void fill_structure(file_t *myfile, dataframe_t *data)
{
    int line_counter = 0;

    for (; fgets(myfile->buffer, myfile->file_size,
        myfile->fp) != NULL; line_counter++);
    data->nb_rows = line_counter;
    data->separator = strdup(myfile->separator);
    data->nb_cols = compute_columns(myfile);
    data->column_names = get_names(data, myfile);
    get_types(data, myfile);
    get_storage(data, myfile);
}

dataframe_t *df_read_csv(const char *filename, const char *separator)
{
    dataframe_t *data = malloc(sizeof(dataframe_t));
    FILE *fp = fopen(filename, "r");
    int file_size = get_size(filename);
    char *buffer = malloc(sizeof(char) * (file_size + 1));
    const char *my_separator = (separator == NULL) ? "," : separator;
    file_t *myfile = create_file_struct(fp, file_size, my_separator, buffer);

    data->storage = malloc(sizeof(linked_list_t *));
    *(data->storage) = NULL;
    if (fp == NULL || data == NULL || buffer == NULL)
        return NULL;
    fgets(myfile->buffer, myfile->file_size, myfile->fp);
    if (strlen(myfile->buffer) == 0) {
        free(myfile->buffer);
        return NULL;
    }
    fill_structure(myfile, data);
    clean_all(fp, buffer, myfile);
    return data;
}
