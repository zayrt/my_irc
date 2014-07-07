/*
** serveur.h for serveur in /home/zellou_i/rendu/PSU_2013_myirc
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Wed Apr 23 02:17:36 2014 ilyas zelloufi
** Last update Sun Apr 27 14:56:59 2014 ilyas zelloufi
*/

#ifndef		SERVEUR_H__
# define	SERVEUR_H__

# define	FD_FREE		0
# define	FD_CLIENT	1
# define	FD_SERVER	2
# define	MAX_FD		255
# define	BUFF_SIZE	3000

typedef				void(*fct)();

typedef struct			s_server
{
  char				*nickname;
  int				fd;
  int				type;
  fct				fct_read;
  struct s_server		*next;
}				t_server;

typedef struct			s_chan
{
  char				*name;
  t_server			*user;
  int				pos;
  struct s_chan			*next;
}				t_chan;

typedef struct			s_env
{
  int				port;
  fd_set			fd_write;
  fd_set			fd_read;
  int				fd_max;
  t_server			*list;
  t_chan			*chan;
}				t_env;

typedef struct			s_cmd
{
  char				*cmd;
  int				(*fptr)(t_env *, char **, int);
}				t_cmd;

char				**my_str_to_wordtab(char *, char);
void				client_read(t_env *, int);
int				check_fd(t_server **, int);
void				add_elem_fd(t_server **, int, int, fct);
void				add_elem_chan(t_chan **, char *);
void				show_list_chan(t_chan *, int);
int				get_cmd(t_env *, char *, int);
int				my_list_chan(t_env *, char **, int);
int				my_join_chan(t_env *, char **, int);
int				my_part_chan(t_env *, char **, int);
int				my_nick(t_env *, char **, int);
t_chan				*get_current_chan(t_chan *list, int fd);
int				my_users(t_env *, char **, int);
int				my_msg(t_env *, char **, int);
int				my_create_chan(t_env *, char **, int);
t_chan				*get_current_chan(t_chan *, int);
t_server			*get_current_user(t_server *, int);
char				*my_strcat(char *, char *);

#endif				/* SERVEUR_H__ */
