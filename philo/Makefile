# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/07 16:08:51 by tokazaki          #+#    #+#              #
#    Updated: 2023/10/27 14:15:04 by tokazaki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# Files & Command +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
SRCS_DIR = srcs
OBJS_DIR = objs

SRCS = $(addprefix srcs/, \
		check_args.c \
		end_of_philo.c \
		init.c \
		main.c \
		monitor.c \
		philo_eat.c \
		philo_sleep_think.c \
		routine_philo_life.c \
		use_mutex.c \
		util/philo_atoi.c \
		util/time.c \
		)

OBJS = $(SRCS:.c=.o)

CC	= cc
CFLAGS  = -Wall -Wextra -Werror -g -fsanitize=thread -D DEBUG=-10
INCLUDE = -I ./srsc -I ./includes
RM	= rm -rf

# Debug +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#

ifdef WITH_SANI
	CFLAGS += -O0 -fsanitize=address
endif

ifdef WITH_THRE
	CFLAGS += -fsanitize=thread -D DEBUG=-10
endif

ifdef WITH_DEBUG
	CFLAGS += -fsanitize=thread -D DEBUG=-10
endif

# Mandatory target ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
.PHONY: all clean fclean re 

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(INCLUDE) $(LDFLAGS) $(CFLAGS) -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# Other target ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
.PHONY: all clean fclean re debug
# for debug
debug:
	make WITH_DEBUG=1

# for debug
thre:
	make WITH_THRE=1

 # for malloc debug
malloc:
	make fclean
	make malloc -C $(LIBFT_DIR)
	make all

# for -fsanitize=address debug
sani:
	make WITH_SANI=1

# nonused variables
clang:
	clang --analyze $(SRCS) $(INCLUDE)

del:
	rm -rf .tmp*
	rm -rf out*
	rm -rf *.plist
	find . -name "*.o" -exec rm {} +
	find . -name "*.un~" -exec rm {} +
	find . -name "*.back" -exec rm {} +
	find . -name ".*.*.swp" -exec rm {} +

leaks:
	while [ 1 ]; do leaks -q philo; sleep 2; done

add:
	git add .
	git status
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
