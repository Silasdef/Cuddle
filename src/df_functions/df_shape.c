/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_shape.c
*/

#include "dataframe.h"

dataframe_shape_t df_shape(dataframe_t *dataframe)
{
    dataframe_shape_t shape = {0};

    shape.nb_columns = dataframe->nb_cols;
    shape.nb_rows = dataframe->nb_rows;
    return shape;
}
