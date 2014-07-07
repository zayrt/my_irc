/*
** serveur.c for serveur in /home/zellou_i/rendu/PSU_2013_myirc
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Sat Apr 19 21:33:02 2014 ilyas zelloufi
** Last update Sun Apr 27 18:54:41 2014 Jean Luc TANG
*/

#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<sys/time.h>
#include	<unistd.h>
#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	"serveur.h"

void			server_read(t_env *e, int s)
{
  int			cs;
  struct sockaddr_in	client_sin;
  int			client_sin_len;

  client_sin_len = sizeof(client_sin);
  cs = accept(s, (struct sockaddr *)&client_sin, &client_sin_len);
  if (cs == -1)
    return ;
  puts("New client");
  add_elem_fd(&e->list, cs, FD_CLIENT, client_read);
}

void			add_server(t_env *e)
{
  int			s;
  struct sockaddr_in	sin;
  int			pos;
  char			*name;
  t_chan		*tmp;

  pos = 1;
  if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    my_exit("Socket() fail.");
  sin.sin_family = AF_INET;
  sin.sin_port = htons(e->port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(s, (struct sockaddr*)&sin, sizeof(sin)) == -1)
    my_exit("Bind() fail.");
  if (listen(s, 42) == -1)
    my_exit("Listen() fail.");
  add_elem_fd(&e->list, s, FD_SERVER, server_read);
  if ((name = malloc(sizeof(char) * 2)) == NULL)
    my_exit("Malloc fail.");
  while (pos <= 10)
    {
      sprintf(name, "%d", pos);
      add_elem_chan(&e->chan, strdup(name));
      pos++;
    }
}

int			my_server(t_env *e)
{
  t_server		*tmp;

  FD_ZERO(&e->fd_read);
  FD_ZERO(&e->fd_write);
  e->fd_max = 0;
  tmp = e->list;
  while (tmp != NULL)
    {
      if (tmp->type != FD_FREE)
	{
	  FD_SET(tmp->fd, &e->fd_read);
	  FD_SET(tmp->fd, &e->fd_write);
	  e->fd_max = tmp->fd;
	}
      tmp = tmp->next;
    }
  if (select(e->fd_max + 1, &e->fd_read, &e->fd_write, NULL, NULL) == -1)
    return (-1);
  tmp = e->list;
  while (tmp != NULL)
    {
      if (FD_ISSET(tmp->fd, &e->fd_read))
	tmp->fct_read(e, tmp->fd);
      tmp = tmp->next;
    }
}

int			main(int argc, char **argv)
{
  t_env			e;

  if (argc != 2 || atoi(argv[1]) < 1025)
    {
      puts("[USAGE] ./server port");
      return (EXIT_FAILURE);
    }
  e.port = atoi(argv[1]);
  e.list = NULL;
  e.chan = NULL;
  add_server(&e);
  while (1)
    my_server(&e);
  return (0);
}
