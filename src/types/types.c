/*
** EPITECH PROJECT, 2025
** bscuddle
** File description:
** types
*/

#include "dataframe.h"

char *display_type(column_type_t type)
{
    switch (type) {
        case INT:
        return "int";
        case UINT:
        return "unsigned int";
        case FLOAT:
        return "float";
        case BOOL:
        return "bool";
        case STRING:
        return "string";
        default:
        return "undefined";
    }
}

static int set_bool_uint(char *element, dataframe_t *data, int i)
{
    if (is_bool(element) && (data->column_types[i] == BOOL ||
        data->column_types[i] == UNDEFINED)) {
        data->column_types[i] = BOOL;
        return 1;
    }
    if (is_uint(element) && data->column_types[i] != INT &&
        data->column_types[i] != FLOAT &&
        data->column_types[i] != STRING) {
        data->column_types[i] = UINT;
        return 1;
    }
    return 0;
}

static int set_int_float(char *element, dataframe_t *data, int i)
{
    if (is_int(element) && data->column_types[i] != FLOAT &&
            data->column_types[i] != STRING) {
            data->column_types[i] = INT;
            return 1;
        }
    if (is_float(element) && data->column_types[i] != STRING) {
        data->column_types[i] = FLOAT;
        return 1;
    }
    return 0;
}

void activate_types(dataframe_t *data, file_t *myfile)
{
    char *token = strtok(myfile->buffer, myfile->separator);
    int i = 0;
    int result = 0;

    result = set_bool_uint(token, data, i);
    if (!result)
        result = set_int_float(token, data, i);
    if (!result)
        data->column_types[i] = STRING;
    while (1) {
        token = strtok(NULL, myfile->separator);
        if (token == NULL)
            break;
        i++;
        if (set_bool_uint(token, data, i))
            continue;
        if (set_int_float(token, data, i))
            continue;
        data->column_types[i] = STRING;
    }
}
