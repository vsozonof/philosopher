# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/03 08:53:01 by vsozonof          #+#    #+#              #
#    Updated: 2023/11/15 04:03:02 by vsozonof         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -g3 #-fsanitize=thread
RM = rm -rf

COLOUR_GREEN =\033[0;32m
COLOUR_END =\033[0m

SRCS = main.c \
	   utils/ft_atol.c \
	   utils/ft_int_overflow_checker.c \
	   utils/ft_strlen.c \
	   utils/ft_error_writer.c \
	   utils/ft_get_time.c \
	   utils/ft_usleep.c \
	   utils/ft_strcmp.c \
	   parsing/verify_arguments.c \
	   src/initializer.c \
	   src/end_program.c \
	   src/actions.c \
	   src/simulation.c \
	   src/forks.c \
	   
all: $(NAME)

$(NAME): $(SRCS)
	@echo "$(COLOUR_GREEN)******    CREATING BINARY    ******$(COLOUR_END)"
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
		@echo "$(COLOUR_GREEN)****** INITIATING CLEAN  ******$(COLOUR_END)"
		@echo "$(COLOUR_GREEN)******   CLEAN COMPLETE  ******$(COLOUR_END)"

fclean: 
		@echo "$(COLOUR_GREEN)****** INITIATING FCLEAN ******$(COLOUR_END)"
		$(RM) $(NAME)
		@echo "$(COLOUR_GREEN)******  FCLEAN COMPLETE  ******$(COLOUR_END)"

re: fclean all

.PHONY: all clean fclean init re