/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_infos.c
*/

#include "dataframe.h"

void df_info(dataframe_t *dataframe)
{
    if (dataframe == NULL)
        return;
    printf("%i columns:\n", dataframe->nb_cols);
    for (int i = 0; i < dataframe->nb_cols; i++) {
        printf("- %s: %s\n", dataframe->column_names[i],
            display_type(dataframe->column_types[i]));
    }
}
