/*
** other_cmd.c for other_cmd in /home/zellou_i/rendu/PSU_2013_myirc
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Sat Apr 26 23:16:46 2014 ilyas zelloufi
** Last update Sun Apr 27 15:11:31 2014 ilyas zelloufi
*/

#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	"serveur.h"

int		my_users(t_env *e, char **cmd, int fd)
{
  t_chan	*current_chan;
  t_server	*tmp;

  if (tablen(cmd) != 1)
    {
      dprintf(fd, "user : error arguments.\n");
      return (0);
    }
  if ((current_chan = get_current_chan(e->chan, fd)) != NULL)
    {
      tmp = current_chan->user;
      while (tmp)
	{
	  if (tmp->nickname)
	    dprintf(fd, "%s\n", tmp->nickname);
	  else if (!tmp->nickname && tmp->type == FD_CLIENT)
	    dprintf(fd, "unknown\n");
	  tmp = tmp->next;
	}
    }
  else
    dprintf(fd, "user : error join a chan before.\n");
}

void		send_msg_to_user(t_server *c_user, t_server *user, char **msg)
{
  int		i;
  char		*tmp;

  i = 2;
  tmp = NULL;
  while (msg[i])
    tmp = my_strcat(tmp, msg[i++]);
  if (c_user != NULL && c_user->nickname)
    dprintf(user->fd, "%s: %s\n", c_user->nickname, tmp);
  else if (c_user != NULL && !c_user->nickname)
    dprintf(user->fd, "unknown: %s\n", tmp);
}

int		my_msg(t_env *e, char **cmd, int fd)
{
  t_chan	*current_chan;
  t_server	*user;
  t_server	*current_user;

  if (tablen(cmd) < 3)
    dprintf(fd, "msg : error arguments.\n");
  else if ((current_chan = get_current_chan(e->chan, fd)) != NULL)
    {
      user = current_chan->user;
      current_user = (!user) ? NULL : get_current_user(user, fd);
      while (user)
	{
	  if (user->nickname && !strcmp(user->nickname, cmd[1]) && fd != user->fd)
	    {
	      send_msg_to_user(current_user, user, cmd);
	      return (1);
	    }
	  user = user->next;
	}
      dprintf(fd, "msg : error the receiver's nickname doesn't exist.\n");
    }
  else
    dprintf(fd, "msg : error join a chan before.\n");
}

int		my_create_chan(t_env *e, char **cmd, int fd)
{
  t_chan	*tmp;

  if (tablen(cmd) != 2)
    {
      dprintf(fd, "create_chan : error arguments.\n");
      return (0);
    }
  tmp = e->chan;
  while (tmp)
    {
      if (!strcmp(tmp->name, cmd[1]))
	{
	  dprintf(fd, "create_chan : this chan already exist.\n");
	  return (0);
	}
      tmp = tmp->next;
    }
  add_elem_chan(&e->chan, cmd[1]);
  dprintf(fd, "The chan %s has been created.\n", cmd[1]);
}
