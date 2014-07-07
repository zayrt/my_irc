/*
** client.c for client in /home/zellou_i/rendu/PSU_2013_myirc
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Sun Apr 20 11:55:31 2014 ilyas zelloufi
** Last update Sun Apr 27 18:39:32 2014 Jean Luc TANG
*/

#include		<sys/types.h>
#include		<sys/socket.h>
#include		<unistd.h>
#include		<stdlib.h>
#include		<stdio.h>
#include		<netdb.h>
#include		<string.h>
#include		<netinet/in.h>
#include		<arpa/inet.h>
#include		<fcntl.h>
#include		<sys/stat.h>
#include		"client.h"

void			get_input(int s)
{
  char			buff[BUFF_SIZE];
  int			r;

  bzero(buff, BUFF_SIZE);
  r = read(0, buff, BUFF_SIZE);
  if (r > 0)
    {
      buff[r] = '\0';
      write(s, buff, r);
    }
  else
    {
      puts("exit");
      exit(0);
    }
}

void			get_msg(int s)
{
  char			buff[BUFF_SIZE];
  int			r;

  bzero(buff, BUFF_SIZE);
  r = recv(s, buff, BUFF_SIZE, 0);
  if (r > 0)
    {
      buff[r] = '\0';
      write(1, buff, r);
    }
  else
    {
      printf("Connection closed\n");
      exit(0);
    }
}

int			my_client(int s)
{
  int			r;
  fd_set		fd_read;

  while (42)
    {
      write(1, "$> ", 3);
      FD_ZERO(&fd_read);
      FD_SET(0, &fd_read);
      FD_SET(s, &fd_read);
      if (select(s + 1, &fd_read, NULL, NULL, NULL) == -1)
	perror("select");
      if (FD_ISSET(0, &fd_read))
	get_input(s);
      if (FD_ISSET(s, &fd_read))
	get_msg(s);
    }
}

int			my_connect(char **cmd)
{
  struct protoent	*pe;
  struct sockaddr_in	sin;
  int			s;
  int			port;

  if (cmd[1] != NULL)
    port = atoi(cmd[1]);
  pe = getprotobyname("TCP");
  if (pe == NULL)
    my_exit("Getprotobyname() fail");
  s = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (s == -1)
    my_exit("Socket() fail.");
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(cmd[0]);
  if (connect(s, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
      perror("Error");
      return (-1);
    }
  free_tab(cmd);
  return (s);
}

int			main()
{
  int			s;

  s = get_first_cmd();
  if (my_client(s) == 0)
    return (0);
}
