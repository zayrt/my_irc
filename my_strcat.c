/*
** my_strcat.c for strcat in /home/zellou_i/rendu/PSU_2013_myirc
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Sun Apr 27 13:58:34 2014 ilyas zelloufi
** Last update Sun Apr 27 15:21:33 2014 ilyas zelloufi
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<string.h>
#include	"serveur.h"

char		*my_strcat(char *s1, char *s2)
{
  int		i;
  char		*fusion;
  int		len;
  int		len2;
  int		i2;

  i = 0;
  if (s1 == NULL)
    return (s2);
  if (s2 == NULL)
    return (s1);
  len = strlen(s1);
  len2 = strlen(s2);
  if ((fusion = malloc(sizeof(char) * (len + len2 + 1))) == NULL)
    my_exit("Malloc() fail");
  while (s1[i])
    fusion[i] = s1[i++];
  fusion[i++] = ' ';
  i2 = 0;
  while (s2[i2])
    fusion[i++] = s2[i2++];
  fusion[i] = '\0';
  return (fusion);
}
