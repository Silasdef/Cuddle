🐼 Cuddle – A DataFrame Library in C
📌 Project Overview

Cuddle is a C-based project that re-implements core features of Python’s pandas library. It enables reading, manipulating, analyzing, and transforming tabular data in a dataframe_t structure. This project is an excellent opportunity to practice data structure design, algorithm implementation, and memory management in C.
🧠 What You Will Learn

    Parsing CSV files into structured memory

    Implementing core dataframe operations (filtering, sorting, grouping, etc.)

    Managing types dynamically (e.g., string, int, float)

    Performing statistical analysis (mean, std, etc.)

    Working with function pointers and memory allocation

    Designing modular and testable C code

⚙️ Features
✅ Basic Operations

    df_read_csv / df_write_csv: Read and write CSV files

    df_info: Display column names and types

    df_describe: Print basic statistics for numeric columns

🔍 Data Manipulation

    df_filter: Filter rows based on a condition

    df_sort: Sort rows by column using a comparison function

    df_groupby: Group by column and aggregate numeric values

    df_apply: Transform a column using a user-defined function

    df_to_type: Convert column types (e.g., string to int)

🧰 Utilities

    df_get_value: Get a single value at a given row and column

    df_get_values: Get all values in a column

    df_get_unique_values: Get all unique values from a column

    df_free: Free the entire dataframe from memory

📁 Data Types

Supported column types (displayed in lowercase):

    bool

    int

    unsigned int

    float

    string

🧪 Example Use Cases

    Load and inspect a dataset:

dataframe_t *df = df_read_csv("data.csv", NULL);
df_info(df);

Get basic stats:

df_describe(df);

Filter and save:

dataframe_t *filtered = df_filter(df, "age", my_filter);
df_write_csv(filtered, "filtered.csv");

Sort by a column:

dataframe_t *sorted = df_sort(df, "age", my_sort_func);

Group by and aggregate:

dataframe_t *grouped = df_groupby(df, "city", (const char*[]){"age", NULL}, my_agg_func);

Apply a transformation:

    dataframe_t *new_df = df_apply(df, "age", my_apply_func);

📦 Compilation

Make sure your program compiles via a Makefile, and your main binary (e.g., cuddle) is executable:

make
./cuddle

✅ Requirements

    All mandatory functions must be implemented

    Output should match the format shown in the examples

    No bonus required, but code should be clean and modular

❗ Tips

    Start with df_read_csv and df_write_csv, as they’re required by all other functions

    Use dynamic memory carefully and free everything with df_free

    Use function pointers for flexible filtering, sorting, and applying

    Write unit tests for each module
