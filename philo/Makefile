# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chunpark <chunpark@student.42gyeongsan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/14 17:13:16 by chunpark          #+#    #+#              #
#    Updated: 2024/06/28 18:34:24 by chunpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

NAME = philo
SRCS = check.c \
	  free.c \
	  handle_thread.c \
	  main.c \
	  preprocess.c \
	  print_msg.c \
	  routine.c \
	  time.c \
	  utils.c \
	  validate.c

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
		   @echo "              ./philo [number_of_philos] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_must_eat]"
		   @echo "                                                                                      \033[0;31m~~~~~~~~~~~~~~~~~~\033[0m"
		   @echo "                                                                                           \033[0;32mnot must\033[0m"
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
