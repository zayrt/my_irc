/*
** handle_client.c for handle_client in /home/zellou_i/rendu/PSU_2013_myirc
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Sat Apr 26 15:24:00 2014 ilyas zelloufi
** Last update Tue Jun 24 20:26:58 2014 ilyas zelloufi
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	"serveur.h"

t_chan		*get_current_chan(t_chan *list, int fd)
{
  t_chan	*tmp;
  t_server	*user;

  tmp = list;
  while (tmp)
    {
      user = tmp->user;
      while (user)
	{
	  if (user->fd == fd && user->type == FD_CLIENT)
	    return (tmp);
	  user = user->next;
	}
      tmp = tmp->next;
    }
  return (NULL);
}

t_server	*get_current_user(t_server *list, int fd)
{
  t_server	*tmp;

  tmp = list;
  while (tmp)
    {
      if (tmp->fd == fd && tmp->type == FD_CLIENT)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

void		my_disconnection(t_env *e, int fd)
{
  t_server	*tmp;
  t_chan	*current_chan;
  t_server	*tmp_user;

  tmp = e->list;
  close(fd);
  printf("%d: Connection closed\n", fd);
  while (tmp->fd != fd && tmp != NULL)
    tmp = tmp->next;
  if (tmp != NULL && tmp->fd == fd)
    tmp->type = FD_FREE;
  current_chan = get_current_chan(e->chan, fd);
  if (current_chan != NULL)
    {
      tmp_user = current_chan->user;
      while (tmp_user)
	{
	  if (tmp_user->fd == fd && tmp_user->type == FD_CLIENT)
	    {
	      tmp_user->type = FD_FREE;
	      tmp_user->nickname = NULL;
	    }
	  tmp_user = tmp_user->next;
	}
    }
}

void		send_msg_in_chan(t_env *e, int fd, char * buf)
{
  t_server	*user;
  t_chan	*current_chan;
  t_server	*current_user;

  current_chan = get_current_chan(e->chan, fd);
  user = (current_chan == NULL) ? NULL : current_chan->user;
  current_user = (!user) ? NULL : get_current_user(user, fd);
  if (!current_chan)
    dprintf(fd, "send msg: error join a chan before.\n");
  while (user)
    {
      if (FD_ISSET(user->fd, &e->fd_write) && fd != user->fd &&
	  user->type == FD_CLIENT)
	{
	  if (current_user != NULL && current_user->nickname)
	    dprintf(user->fd, "%s: %s\n", current_user->nickname, buf);
	  else if (current_user != NULL)
	    dprintf(user->fd, "unknown: %s\n", buf);
	}
      user = user->next;
    }
}

void		client_read(t_env *e, int fd)
{
  int		r;
  char		buf[BUFF_SIZE];

  r = read(fd, buf, BUFF_SIZE);
  if (r > 0)
    {
      buf[r - 1] = '\0';
      if (!get_cmd(e, buf, fd))
	send_msg_in_chan(e, fd, buf);
    }
  else
    my_disconnection(e, fd);
}
