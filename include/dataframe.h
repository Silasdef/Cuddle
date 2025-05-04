/*
** EPITECH PROJECT, 2025
** bscuddle
** File description:
** dataframe
*/

#ifndef DATAFRAME_H_
    #define DATAFRAME_H_
    #include <stdio.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/types.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <math.h>
    #include <stdbool.h>
    #include <ctype.h>

typedef enum {
    BOOL,
    INT,
    UINT,
    FLOAT,
    STRING,
    UNDEFINED
} column_type_t;

typedef struct linked_list_s {
    void **data;
    struct linked_list_s *next;
} linked_list_t;

typedef struct {
    int nb_rows;
    int nb_cols;
    char **column_names;
    char *separator;
    column_type_t *column_types;
    linked_list_t **storage;
} dataframe_t;

typedef struct {
    FILE *fp;
    int file_size;
    const char *separator;
    char *buffer;
    void **data_tab;
    float *value_float;
    unsigned int *value_uint;
    int *value_int;
} file_t;

typedef struct dataframe_shape_s {
    int nb_rows;
    int nb_columns;
} dataframe_shape_t;

dataframe_t *df_read_csv(const char *filename, const char *separator);
int df_write_csv(dataframe_t *dataframe, const char *filename);
dataframe_t *df_head(dataframe_t *dataframe, int nb_rows);
dataframe_t *df_tail(dataframe_t *dataframe, int nb_rows);
dataframe_shape_t df_shape(dataframe_t *dataframe);
void df_info(dataframe_t *dataframe);
void df_describe(dataframe_t *dataframe);
dataframe_t *df_filter(dataframe_t *dataframe,
    const char *column, bool(*filter_func)(void *value));
void df_free(dataframe_t *dataframe);
dataframe_t *df_sort(dataframe_t *dataframe, const char *column,
    bool (*sort_func)(void *value1, void *value_2));
void *df_get_value(dataframe_t *dataframe, int row, const char *column);
void **df_get_values(dataframe_t *dataframe, const char *column);
void **df_get_unique_values(dataframe_t *dataframe, const char *column);

char **my_str_to_word_array(char const *str, char delimiter);
int get_size(const char *filename);
void set_data_column_types(dataframe_t *data, int column_counter);
file_t *create_file_struct(FILE *fp, int file_size,
    const char *separator, char *buffer);
char **get_column_names(dataframe_t *dataframe);
double get_right_type(void *elem, dataframe_t *dataframe, int i);
void **dup_array(dataframe_t *data, void **array);
void *dup_type(dataframe_t *data, int i, void **array);
void *dup_float_uint_bool(dataframe_t *data,
    int i, void **array, void *new_data);
void *dup_int_string(dataframe_t *data,
    int i, void **array, void *new_data);
column_type_t *get_type(dataframe_t *dataframe);
int check_column(dataframe_t *data, const char *column);

int is_int(char *str);
int is_uint(char *str);
int is_float(char *str);
int is_bool(char *str);

char *display_type(column_type_t);
void activate_types(dataframe_t *data, file_t *myfile);

char *float_to_string(float num);
char *uint_to_string(unsigned int num);
char *int_to_string(int num);

void convert_string_to_float(linked_list_t *current, int i);
void convert_string_to_uint(linked_list_t *current, int i);
void convert_string_to_int(linked_list_t *current, int i);

dataframe_t *df_to_type(dataframe_t *dataframe,
    const char *column, column_type_t downcast);

void clean_all(FILE *fp, char *buffer, file_t *myfile);
void my_rev_list(linked_list_t **begin);
void add_node(dataframe_t *data, linked_list_t *node);
dataframe_t *dup_data(dataframe_t *dataframe);
void dup_storage(dataframe_t *dataframe, dataframe_t *new);
dataframe_t *df_apply(dataframe_t *dataframe, const char *column,
    void *(*apply_func)(void *value));

// TYPE UTILS
int my_str_isnum(char *str);
int num_to_int(linked_list_t *current, int i, double val);
int num_to_float(linked_list_t *current, int i, double val);
int num_to_uint(linked_list_t *current, int i, double val);


#endif /* !DATAFRAME_H_ */
