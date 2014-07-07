/*
** cmd.c for cmd in /home/zellou_i/rendu/PSU_2013_myirc
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Sat Apr 26 02:44:10 2014 ilyas zelloufi
** Last update Sun Apr 27 14:50:26 2014 ilyas zelloufi
*/

#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	"serveur.h"

t_cmd		g_tab[] =
  {
    {"/list", &my_list_chan},
    {"/join", &my_join_chan},
    {"/part", &my_part_chan},
    {"/nick", &my_nick},
    {"/users", &my_users},
    {"/msg", &my_msg},
    {"/create_chan", &my_create_chan},
    {NULL, NULL},
  };

int		get_cmd(t_env *e, char *buff, int fd)
{
  char		**cmd;
  int		i;

  i = -1;
  if (buff[0] != '\0')
    {
      cmd = my_str_to_wordtab(buff, ' ');
      if (cmd[0] == NULL)
	return (0);
      while (g_tab[++i].cmd != NULL && strcmp(cmd[0], g_tab[i].cmd));
      if (g_tab[i].cmd == NULL)
	return (0);
      else
	g_tab[i].fptr(e, cmd, fd);
      show_all_user(e->chan);
      return (1);
    }
  return (0);
}

int		my_list_chan(t_env *e, char **cmd, int fd)
{
  t_chan	*tmp;

  if (tablen(cmd) == 1)
    show_list_chan(e->chan, fd);
  else if (tablen(cmd) == 2)
    {
      tmp = e->chan;
      while (tmp)
	{
	  if (!strncmp(tmp->name, cmd[1], strlen(cmd[1])))
	    dprintf(fd, "%s\n", tmp->name);
	  tmp = tmp->next;
	}
    }
  else
    dprintf(fd, "list : error arguments.\n");
  return (0);
}

int		disconnect_part(t_server *list, int fd)
{
  t_server	*user;

  user = list;
  while (user)
    {
      if (user->fd == fd && user->type == FD_CLIENT)
	{
	  user->type = FD_FREE;
	  user->nickname = NULL;
	  return (0);
	}
      user = user->next;
    }
  dprintf(fd, "part : error client doesn't exist in this chan.\n");
}

int		my_part_chan(t_env *e, char **cmd, int fd)
{
  t_chan	*tmp;

  tmp = e->chan;
  if (tablen(cmd) != 2)
    {
      dprintf(fd, "part : error arguments.\n");
      return (0);
    }
  while (tmp)
    {
      if (!strcmp(tmp->name, cmd[1]))
	{
	  disconnect_part(tmp->user, fd);
	  return (0);
	}
      tmp = tmp->next;
    }
  dprintf(fd, "part : error chan doesn't exist.\n");
}

int		my_nick(t_env *e, char **cmd, int fd)
{
  t_chan	*current_chan;
  t_server	*tmp;

  if (tablen(cmd) != 2)
    {
      dprintf(fd, "nick : error arguments.\n");
      return (0);
    }
  if ((current_chan = get_current_chan(e->chan, fd)) != NULL)
    {
      tmp = current_chan->user;
      while (tmp)
	{
	  if (tmp->fd == fd && tmp->type == FD_CLIENT)
	    {
	      tmp->nickname = strdup(cmd[1]);
	      return (0);
	    }
	  tmp = tmp->next;
	}
    }
  dprintf(fd, "nick : error join a chan before.\n");
}
