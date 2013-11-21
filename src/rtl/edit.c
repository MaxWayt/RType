/*
** edit.c for rtl in /home/leroy_v/rtl
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Thu Nov 21 18:19:41 2013 vincent leroy
** Last update Thu Nov 21 19:39:24 2013 vincent leroy
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "rtl.h"

int edit_monster(int ac, char **avi)
{
    if (ac < 2)
        return -1;

    int line = atoi(avi[1]);
    if (line > NB_MAX_MONSTER_PER_LEVEL)
    {
        fprintf(stderr, "Line number is too high: max %d\n", NB_MAX_MONSTER_PER_LEVEL);
        return 1;
    }
    else if (line <= 0)
    {
        fprintf(stderr, "Line number must be greater than 0\n");
        return 1;
    }
    --line;

    int fd;
    if ((fd = open(avi[0], O_RDONLY)) == -1)
    {
        fprintf(stderr, "Unable to open file '%s': %m\n", avi[0]);
        return 1;
    }

    struct QueenMonster monster[NB_MAX_MONSTER_PER_LEVEL];
    int i;
    for (i = 0; i < line; ++i)
    {
        if (read(fd, &monster[i], sizeof(struct QueenMonster)) <= 0)
        {
            fprintf(stderr, "The file '%s' has only %d line%c\n", avi[0], i + 1, i > 0 ? 's' : '\0');
            close(fd);
            return 1;
        }
    }

    if (read(fd, &monster[i], sizeof(struct QueenMonster)) > 0)
    {
        set_monster(&monster[i], ac - 2, avi + 2);
        for (++i; read(fd, &monster[i], sizeof(struct QueenMonster)) > 0; ++i);
    }
    else
    {
        fprintf(stderr, "The file '%s' has only %d line%c\n", avi[0], i, i > 0 ? 's' : '\0');
        close(fd);
        return 1;
    }

    close(fd);
    if ((fd = open(avi[0], O_WRONLY | O_TRUNC)) == -1)
    {
        fprintf(stderr, "Unable to open file '%s': %m\n", avi[0]);
        return 1;
    }

    int j;
    for (j = 0; j < i; ++j)
        write(fd, &monster[j], sizeof(struct QueenMonster));

    close(fd);

    return 0;
}
