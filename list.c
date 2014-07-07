/*
** list.c for list in /home/zellou_i/rendu/PSU_2013_myirc
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Thu Apr 24 20:50:40 2014 ilyas zelloufi
** Last update Sat Apr 26 19:53:45 2014 ilyas zelloufi
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	"serveur.h"

int		check_fd(t_server **list, int fd)
{
  t_server	*tmp;

  tmp = *list;
  while (tmp != NULL)
    {
      if (tmp->fd == fd)
	{
	  tmp->type = FD_CLIENT;
	  return (1);
	}
      tmp = tmp->next;
    }
  return (0);
}
void		add_elem_fd(t_server **list, int fd, int type, fct fct_read)
{
  t_server	*new;
  t_server	*tmp;

  if (check_fd(list, fd))
    return ;
  if ((new = malloc(sizeof(*new))) == NULL)
    my_exit("Malloc() fail");
  new->fd = fd;
  new->type = type;
  new->fct_read = fct_read;
  new->nickname = NULL;
  new->next = NULL;
  if (*list == NULL)
    *list = new;
  else
    {
      tmp = *list;
      while (tmp->next != NULL)
	tmp = tmp->next;
      tmp->next = new;
    }
}

void		add_elem_chan(t_chan **list, char *name)
{
  t_chan	*new;
  t_chan	*tmp;

  if ((new = malloc(sizeof(*new))) == NULL)
    my_exit("Malloc() fail");
  if (name == NULL)
    my_exit("Malloc() fail");
  new->name = name;
  new->next = NULL;
  new->user = NULL;
  if (*list == NULL)
    *list = new;
  else
    {
      tmp = *list;
      while (tmp->next != NULL)
	tmp = tmp->next;
      tmp->next = new;
    }

}

void		show_list(t_server *list, int fd)
{
  t_server	*tmp;

  tmp = list;
  while (tmp != NULL)
    {
      dprintf(fd, "fd -> %d\n", tmp->fd);
      tmp = tmp->next;
    }
}

void		show_list_chan(t_chan *list, int fd)
{
  t_chan	*tmp;

  tmp = list;
  while (tmp != NULL)
    {
      dprintf(fd, "%s\n", tmp->name);
      tmp = tmp->next;
    }
}
