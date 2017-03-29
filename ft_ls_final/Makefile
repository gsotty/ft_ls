# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsotty <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 15:44:40 by gsotty            #+#    #+#              #
#    Updated: 2017/03/29 17:45:10 by gsotty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = gcc

FLAG = -Wall -Wextra -Werror

LIBFT = ./libft

FT_PRINTF = ./ft_printf

INCLUDE = ./ft_ls.h

SRC = check_flag_ls.c files_is_dir.c ft_len_dir.c ft_ls.c ft_while_ls.c \
	  orber.c orber_no_t_no_r.c orber_no_t_r.c orber_t_no_r.c orber_t_r.c \
	  permision_l.c printf_l_lnk.c printf_l_nlnk.c printf_l_lnk_tsix.c \
	  printf_l_nlnk_tsix.c recursive_r_maj_files_ls.c \
	  verif_len.c write_buf_ls.c write_struc_ls.c files_is_files.c \
	  order_dir_t_no_r.c order_dir_t_r.c verif_argv_null.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -s -C $(LIBFT) re
	make -s -C $(FT_PRINTF) re
	$(CC) $(FLAG) $(SRC) ./libft/libft.a ./ft_printf/libftprintf.a -o $(NAME)

debug: $(OBJ)
	make -s -C $(LIBFT) re
	make -s -C $(FT_PRINTF) re
	$(CC) -g $(FLAG) $(SRC) ./libft/libft.a ./ft_printf/libftprintf.a -o \
		$(NAME)
	make -s -C $(LIBFT) clean
	make -s -C $(FT_PRINTF) clean
	rm -Rf $(OBJ)

%.o : %.c
	$(CC) $(FLAG) -g -c $<

clean:
	make -C $(LIBFT) clean
	make -C $(FT_PRINTF) clean
	rm -Rf $(OBJ)

declean:
	make -C $(LIBFT) fclean
	make -C $(FT_PRINTF) fclean
	rm -Rf $(NAME).dSYM
	rm -Rf $(NAME)


fclean: clean
	make -C $(LIBFT) fclean
	make -C $(FT_PRINTF) fclean
	rm -Rf $(NAME)

re: fclean all
