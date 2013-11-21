/*
** create.c for rtl in /home/leroy_v/rtl
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Thu Nov 21 15:33:37 2013 vincent leroy
** Last update Thu Nov 21 17:44:33 2013 vincent leroy
*/

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

#include "rtl.h"

int create_level(int ac, char **avi)
{
    if (ac < 1)
        return -1;

    int fd;
    if ((fd = open(avi[0], O_WRONLY | O_CREAT | O_EXCL, 0644)) == -1)
    {
        if (errno == EEXIST)
            fprintf(stderr, "Level '%s' already created\n", avi[0]);
        else
            fprintf(stderr, "Unable to create level '%s': %m\n", avi[0]);
        return 1;
    }
    close(fd);

    return 0;
}
