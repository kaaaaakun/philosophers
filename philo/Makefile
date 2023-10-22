# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/07 16:08:51 by tokazaki          #+#    #+#              #
#    Updated: 2023/10/19 20:55:41 by tokazaki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# Files & Command +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
SRCS_DIR = srcs
OBJS_DIR = objs

SRCS = $(addprefix srcs/, \
		main.c \
		check_args.c \
		init.c \
		routine_philo_life.c \
		monitor_in_panopticon.c \
		gettimeofday.c \
		end_of_philo.c \
		philo_atoi.c \
		debug.c \
		)

OBJS = $(SRCS:.c=.o)

CC		= cc
CFLAGS  = -Wall -Wextra -Werror -g
INCLUDE = -I ./srsc -I ./includes
RM		= rm -rf

# Debug +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#

ifdef WITH_CRASH
	CFLAGS += -O0 -fsanitize=address
endif

ifndef WITH_CRASH
	CFLAGS += -fsanitize=thread
endif

ifdef WITH_DEBUG
	CFLAGS += -fsanitize=thread -D DEBUG=1
endif

# Mandatory target ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
.PHONY: all clean fclean re debug

all: re $(NAME)

.c.o:
	@ $(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(INCLUDE) $(LDFLAGS) $(CFLAGS) -o $@

clean:
	@ $(RM) $(OBJS)

fclean: clean
	@ $(RM) $(NAME)

re: fclean all

# Other target ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
# for debug
debug:
	make WITH_DEBUG=0

# # for malloc debug
# malloc:
# 	make fclean
# 	make malloc -C $(LIBFT_DIR)
# 	make all

# for -fsanitize=address debug
crash:
	make WITH_CRASH=1

# # nonused variables
# clang:
# 	clang --analyze $(SRCS) $(INCLUDE)

del:
	rm -rf .tmp*
	rm -rf out*
	rm -rf *.plist
	find . -name "*.o" -exec rm {} +
	find . -name "*.un~" -exec rm {} +
	find . -name "*.back" -exec rm {} +

# leaks:
# 	while [ 1 ]; do leaks -q philo; sleep 2; done
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
