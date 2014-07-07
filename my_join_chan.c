/*
** other_cmd.c for other_cmd in /home/zellou_i/rendu/PSU_2013_myirc
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Sat Apr 26 21:11:30 2014 ilyas zelloufi
** Last update Sun Apr 27 15:28:22 2014 ilyas zelloufi
*/

#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	"serveur.h"

void		change_chan(t_chan *list, char *name_chan, int fd)
{
  t_chan	*tmp;
  t_server	*user;

  tmp = list;
  while (tmp)
    {
      if (strcmp(tmp->name, name_chan))
	{
	  user = tmp->user;
	  while (user)
	    {
	      if (user->fd == fd && user->type == FD_CLIENT)
		user->type = FD_FREE;
	      user = user->next;
	    }
	}
      tmp = tmp->next;
    }
}

int		check_user_in_chan(t_server *user, int fd)
{
  t_server	*tmp;

  tmp = user;
  while (tmp)
    {
      if (tmp->fd == fd && tmp->type == FD_CLIENT)
	{
	  dprintf(fd, "join : error you already exist in this chan.\n");
	  return (1);
	}
      else if (tmp->fd == fd)
	{
	  tmp->type = FD_CLIENT;
	  return (1);
	}
      tmp = tmp->next;
    }
  return (0);
}

int		my_join_chan(t_env *e, char **cmd, int fd)
{
  t_chan	*tmp;

  tmp = e->chan;
  if (tablen(cmd) != 2)
    {
      dprintf(fd, "join : error arguments.\n");
      return (0);
    }
  else
    while (tmp)
      {
	if (!strcmp(tmp->name, cmd[1]))
	  {
	    change_chan(e->chan, cmd[1], fd);
	    if (!check_user_in_chan(tmp->user, fd))
	      {
		add_elem_fd(&tmp->user, fd, FD_CLIENT, client_read);
		return (1);
	      }
	    else
	      return (0);
	  }
	tmp = tmp->next;
      }
  dprintf(fd, "join : error chan doesn't exist.\n");
}
