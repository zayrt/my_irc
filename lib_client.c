/*
** lib_client.c for lib_client in /home/zellou_i/rendu/PSU_2013_myirc
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Sun Apr 27 09:02:58 2014 ilyas zelloufi
** Last update Sun Apr 27 18:35:17 2014 Jean Luc TANG
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	"client.h"

int		get_first_cmd()
{
  char		buff[BUFF_SIZE];
  char		**tmp;
  char		**tmp2;
  int		i;

  while (42)
    {
      write(1, "$> ", 3);
      i = read(0, buff, BUFF_SIZE);
      if (i > 0)
	{
	  buff[i] = '\0';
	  tmp = my_str_to_wordtab(buff, ' ');
	  if (tablen(tmp) == 2 && strcmp(tmp[0], "/server") == 0)
	    {
	      tmp2 = my_str_to_wordtab(tmp[1], ':');
	      if ((i = my_connect(tmp2)) != -1)
		return (i);
	    }
	  else
	    printf("Use the command server for specify a host and a port\n");
	}
      else
	my_exit("exit");
    }
}
