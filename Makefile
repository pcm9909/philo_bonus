# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/22 20:26:42 by chunpark          #+#    #+#              #
#    Updated: 2024/06/22 20:28:33 by chunpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
#ADDRESS = -g -fsanitize=address
#THREAD = -g -fsanitize=thread

NAME = philo_bonus
SRCS =	check.c \
		fork.c \
		preprocess.c \
		print_msg.c \
		routine.c \
		time.c \
		utils.c \
		validate.c \
		main.c

OBJS = $(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: print $(NAME)

$(NAME): $(OBJS)
		   @$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
		   @echo ""
		   @echo ""
		   @echo "           Done compiling...! "
		   @echo ""
		   @echo ""
		   @echo "              ./philo_bonus [number_of_philos] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_must_eat]"
		   @echo "                                                                                            \033[0;31m~~~~~~~~~~~~~~~~~~\033[0m"
		   @echo "                                                                                                 \033[0;32mnot must\033[0m"
		   @echo ""

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

thread: fclean $(OBJS)
	$(CC) $(CFLAGS) $(ADDRESS) -o $(NAME) $(OBJS)

address: fclean $(OBJS)
	$(CC) $(CFLAGS) $(THREAD) -o $(NAME) $(OBJS)

print:
	clear
	@bash philo.sh


.PHONY: all clean fclean re print
