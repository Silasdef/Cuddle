/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_describe
*/

#include "dataframe.h"

double get_right_type(void *elem, dataframe_t *dataframe, int i)
{
    switch (dataframe->column_types[i]) {
        case INT:
            return (double) *(int *) elem;
        case UINT:
            return (double) *(unsigned int *) elem;
        case FLOAT:
            return (double) *(float *) elem;
        default:
            return 0;
    }
}

static double get_max(dataframe_t *dataframe, int i)
{
    linked_list_t *tmp = *dataframe->storage;
    double max = get_right_type(tmp->data[i], dataframe, i);

    for (; tmp != NULL; tmp = tmp->next) {
        if (get_right_type(tmp->data[i], dataframe, i) > max)
            max = get_right_type(tmp->data[i], dataframe, i);
    }
    return max;
}

static double get_min(dataframe_t *dataframe, int i)
{
    linked_list_t *tmp = *dataframe->storage;
    double min = get_right_type(tmp->data[i], dataframe, i);

    for (; tmp != NULL; tmp = tmp->next) {
        if (get_right_type(tmp->data[i], dataframe, i) < min)
            min = get_right_type(tmp->data[i], dataframe, i);
    }
    return min;
}

static double compute_std(dataframe_t *dataframe, int i, double mean)
{
    double std = 0;
    linked_list_t *tmp = *dataframe->storage;

    for (; tmp != NULL; tmp = tmp->next) {
        std += pow(get_right_type(tmp->data[i], dataframe, i) - mean, 2);
    }
    std = sqrt(std / dataframe->nb_rows);
    return std;
}

static double compute_mean(dataframe_t *dataframe, int i)
{
    double sum = 0;
    linked_list_t *tmp = *dataframe->storage;

    for (; tmp != NULL; tmp = tmp->next) {
        sum += get_right_type(tmp->data[i], dataframe, i);
    }
    return sum / dataframe->nb_rows;
}

static void display_column(dataframe_t *dataframe, int i)
{
    double mean = 0;

    printf("Column: %s\n", dataframe->column_names[i]);
    printf("Count: %i\n", dataframe->nb_rows);
    mean = compute_mean(dataframe, i);
    printf("Mean: %.2f\n", mean);
    printf("Std: %.2f\n", compute_std(dataframe, i, mean));
    printf("Min: %.2f\n", get_min(dataframe, i));
    printf("Max: %.2f\n", get_max(dataframe, i));
}

void df_describe(dataframe_t *dataframe)
{
    for (int i = 0; i < dataframe->nb_cols; i++) {
        if (dataframe->column_types[i] == INT ||
            dataframe->column_types[i] == UINT ||
            dataframe->column_types[i] == FLOAT) {
                display_column(dataframe, i);
        }
    }
}
