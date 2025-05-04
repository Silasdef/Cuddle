/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_to_type
*/

#include "dataframe.h"

static int both_type_num(column_type_t current, column_type_t new)
{
    return (current == INT || current == UINT || current == FLOAT) &&
        (new == INT || new == UINT || new == FLOAT);
}

static int convert_between_num(linked_list_t *current, int i,
    column_type_t downcast, dataframe_t *new)
{
    double val = get_right_type(current->data[i], new, i);

    free(current->data[i]);
    switch (downcast) {
        case INT:
            return num_to_int(current, i, val);
        case UINT:
            return num_to_uint(current, i, val);
        case FLOAT:
            return num_to_float(current, i, val);
        default:
            return 0;
    }
    return 0;
}

static void handle_type_conversion(void *elem, column_type_t cur_type,
    double type_num, char *tmp)
{
    switch (cur_type) {
        case INT:
            tmp = int_to_string((int) type_num);
            free(elem);
            elem = (void *) tmp;
            break;
        case UINT:
            tmp = uint_to_string((unsigned int) type_num);
            free(elem);
            elem = (void *) tmp;
            break;
        case FLOAT:
            tmp = float_to_string((float) type_num);
            free(elem);
            elem = (void *) tmp;
            break;
        default:
            break;
    }
}

static void convert_num_to_string(linked_list_t *current,
    int i, column_type_t cur_type, dataframe_t *new)
{
    double type_num = get_right_type(current->data[i], new, i);
    char *tmp = NULL;

    handle_type_conversion(current->data[i], cur_type,
        type_num, tmp);
}

static int convert_string_to_num(linked_list_t *current, int i,
    column_type_t downcast)
{
    if (!my_str_isnum((char *) current->data[i]))
        return 0;
    switch (downcast) {
        case INT:
            convert_string_to_int(current, i);
            break;
        case UINT:
            convert_string_to_uint(current, i);
            break;
        case FLOAT:
            convert_string_to_float(current, i);
            break;
        default:
            break;
    }
    return 1;
}

static int convert_to_bool(linked_list_t *current, int i,
    column_type_t current_type, dataframe_t *new)
{
    double value = get_right_type(current->data[i], new, i);

    if (current_type == INT || current_type == UINT ||
        current_type == FLOAT) {
        current->data[i] = (value == 0) ? strdup("false") : strdup("true");
    }
    if (current_type == STRING)
        current->data[i] = (strcmp((char *) current->data[i], "\0") == 0)
        ? strdup("false") : strdup("true");
    return 1;
}

static int handle_numeric_conversion(linked_list_t *current, int i,
    column_type_t downcast, dataframe_t *new)
{
    if (both_type_num(new->column_types[i], downcast))
        return convert_between_num(current, i, downcast, new);
    if (downcast == STRING) {
        convert_num_to_string(current, i, new->column_types[i], new);
        return 1;
    }
    if (downcast == INT || downcast == UINT || downcast == FLOAT)
        return convert_string_to_num(current, i, downcast);
    return convert_to_bool(current, i, new->column_types[i], new);
}

static int convert_type(dataframe_t *new, int i, column_type_t downcast)
{
    linked_list_t *current = *new->storage;

    while (current != NULL) {
        if (downcast != new->column_types[i] &&
            !handle_numeric_conversion(current, i, downcast, new))
            return 0;
        current = current->next;
    }
    new->column_types[i] = downcast;
    return 1;
}

static dataframe_t *compare_column(dataframe_t *new, int i,
    const char *column, column_type_t downcast)
{
    if (strcmp(new->column_names[i], column) == 0) {
        if (!convert_type(new, i, downcast)) {
            return NULL;
        }
    }
    return new;
}

dataframe_t *df_to_type(dataframe_t *dataframe,
    const char *column, column_type_t downcast)
{
    dataframe_t *new = NULL;

    if (dataframe == NULL || check_column(dataframe, column) == 0)
        return NULL;
    new = dup_data(dataframe);
    for (int i = 0; i < new->nb_cols; i++) {
        new = compare_column(new, i, column, downcast);
        if (!new) {
            df_free(new);
            return NULL;
        }
    }
    return new;
}
