##
## Makefile for client in /home/zellou_i/rendu/PSU_2013_myirc
##
## Made by ilyas zelloufi
## Login   <zellou_i@epitech.net>
##
## Started on  Wed Apr 23 02:30:21 2014 ilyas zelloufi
## Last update Sun Apr 27 14:12:57 2014 ilyas zelloufi
##

CC =		gcc

RM =		rm -f

CFLAGS +=

LDFLAGS =

NAME_SERVER =	serveur

NAME_CLIENT =	client

SRCS_SERVER =	serveur.c \
		list.c \
		list2.c \
		get_cmd.c \
		other_cmd.c \
		my_join_chan.c \
		client_read.c \
		my_strcat.c \
		my_str_to_wordtab.c

SRCS_CLIENT =	client.c \
		lib_client.c \
		my_str_to_wordtab.c

OBJS_SERVER =	$(SRCS_SERVER:.c=.o)

OBJS_CLIENT =	$(SRCS_CLIENT:.c=.o)

all:		$(NAME_SERVER) $(NAME_CLIENT)

server:		$(NAME_SERVER)

client:		$(NAME_CLIENT)

$(NAME_SERVER):	$(OBJS_SERVER)
		$(CC) $(OBJS_SERVER) -o $(NAME_SERVER) $(LDFLAGS)

$(NAME_CLIENT):	$(OBJS_CLIENT)
		$(CC) $(OBJS_CLIENT) -o $(NAME_CLIENT) $(LDFLAGS)

clean:
		$(RM) $(OBJS_SERVER)
		$(RM) $(OBJS_CLIENT)

fclean:		clean
		$(RM) $(NAME_SERVER)
		$(RM) $(NAME_CLIENT)

re:		fclean all

.PHONY:		all clean fclean re
