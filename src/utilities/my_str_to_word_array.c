/*
** EPITECH PROJECT, 2025
** libmy
** File description:
** my_str_to_word_array
*/

#include "dataframe.h"

static int is_delimiter(char c, char delimiter, int *inquote)
{
    *inquote = (c == '"' || c == '\'') ? !(*inquote) : *inquote;
    return (c == delimiter || c == '\t' || c == '\n') && !(*inquote);
}

static int count_total_words(char const *str, char delimiter, int *inquote)
{
    int counter = 0;
    int is_delim = 0;

    for (int i = 0; i < (int) strlen(str); i++) {
        is_delim = is_delimiter(str[i], delimiter, inquote);
        counter = (is_delim && !(*inquote)) ? counter + 1 : counter;
    }
    return counter;
}

static char *insert_word(char const **str_adress, char delimiter, int *inquote)
{
    char const *str = *str_adress;
    char const *begin;
    int size = 0;
    char *new_word = NULL;

    for (; is_delimiter(*str, delimiter, inquote); str++);
    begin = str;
    str++;
    for (; !is_delimiter(*str, delimiter, inquote); str++);
    size = str - begin;
    new_word = malloc(sizeof(char) * (size + 1));
    if (new_word == NULL)
        return NULL;
    strncpy(new_word, begin, size);
    new_word[size] = 0;
    *str_adress = str;
    return new_word;
}

static void clean_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++) {
        if (strlen(tab[i]) == 0) {
            free(tab[i]);
            tab[i] = NULL;
        }
    }
}

char **my_str_to_word_array(char const *str, char delimiter)
{
    int inquote = 0;
    int word_counter = count_total_words(str, delimiter, &inquote);
    char **tab = malloc(sizeof(char *) * (word_counter + 1));
    char *tmp_word = NULL;

    if (tab == NULL) {
        free(tab);
        return NULL;
    }
    for (int i = 0; i < word_counter; i++) {
        tmp_word = insert_word(&str, delimiter, &inquote);
        tab[i] = tmp_word;
    }
    tab[word_counter] = NULL;
    clean_tab(tab);
    return tab;
}
