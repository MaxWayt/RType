/*
** create.c for rtl in /home/leroy_v/rtl
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Thu Nov 21 15:33:37 2013 vincent leroy
** Last update Thu Nov 21 17:44:33 2013 vincent leroy
*/

#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

#include "rtl.h"

int create_level(int ac, char **avi)
{
    FILE* fd;

    if (ac < 1)
        return -1;

	if ((fd = fopen(avi[0], "r")) != NULL)
	{
		fprintf(stderr, "Level '%s' already created\n", avi[0]);
		fclose(fd);
		return 1;
	}
    if ((fd = fopen(avi[0], "w")) == NULL)
    {
        fprintf(stderr, "Unable to create level '%s': %m\n", avi[0]);
        return 1;
    }
    fclose(fd);

    return 0;
}
