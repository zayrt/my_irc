/*
** list2.c for list2 in /home/zellou_i/rendu/PSU_2013_myirc
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Sat Apr 26 19:52:41 2014 ilyas zelloufi
** Last update Sun Apr 27 15:16:24 2014 ilyas zelloufi
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	"serveur.h"

void		show_all_user(t_chan *list)
{
  t_chan	*tmp;
  t_server	*tmp_user;

  tmp = list;
  while (tmp)
    {
      printf("chan %s -> \n", tmp->name);
      tmp_user = tmp->user;
      while (tmp_user)
	{
	  if (tmp_user->type != FD_FREE)
	    {
	      if (tmp_user->nickname)
		printf("fd -> %d : nickname -> %s\n", tmp_user->fd,
		       tmp_user->nickname);
	      else
		printf("fd -> %d : nickname -> unknown\n", tmp_user->fd);
	    }
	  tmp_user = tmp_user->next;
	}
      tmp = tmp->next;
    }
  printf("\n\n");
}
