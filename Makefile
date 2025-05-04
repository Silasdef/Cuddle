##
## EPITECH PROJECT, 2024
## bscuddle
## File description:
## Makefile
##

SRC		=	src/types/check_types.c						    \
			src/types/types.c						        \
			src/utilities/my_str_to_word_array.c			\
			src/utilities/utilities.c					    \
			src/df_functions/df_read_csv.c			    	\
			src/df_functions/df_shape.c					    \
			src/df_functions/df_infos.c					    \
			src/df_functions/df_describe.c			    	\
			src/df_functions/df_write_csv.c			    	\
			src/df_functions/df_free.c					    \
			src/df_functions/df_head.c					    \
			src/df_functions/df_sort.c					    \
			src/df_functions/df_tail.c					    \
			src/df_functions/df_filter.c				    \
			src/utilities/dup_data.c						\
			src/utilities/type_utils.c						\
			src/df_functions/df_apply.c						\
			src/utilities/dup_functions.c					\
			src/df_functions/df_get_value.c					\
			src/df_functions/df_to_type.c					\
			src/types/type_conversion_num.c					\
			src/types/type_conversion_str.c					\
			src/df_functions/df_get_values.c				\
			src/df_functions/df_get_unique_values.c			\


NAME	=	libcuddle.a

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Iinclude -lm

all:		$(OBJ)
			@ar rc $(NAME) $(OBJ)
			@echo "Compilation done"

clean:
			@rm -f $(OBJ)
			@echo "Cleaning done"

fclean:		clean
			@rm -f $(NAME)
			@echo "Full cleaning done."

re:			fclean all
