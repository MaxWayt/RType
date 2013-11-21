/*
** list.c for rtl in /home/leroy_v/rtl
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Thu Nov 21 16:44:09 2013 vincent leroy
** Last update Thu Nov 21 19:33:10 2013 vincent leroy
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "rtl.h"

int list_level(int ac, char **avi)
{
    if (ac < 1)
        return -1;

    int fd;
    struct QueenMonster monster;

    if ((fd = open(avi[0], O_RDONLY)) == -1)
    {
        fprintf(stderr, "Unable to open file '%s': %m\n", avi[0]);
        return 1;
    }

    while (read(fd, &monster, sizeof(struct QueenMonster)) > 0)
    {
        printf("nb = %d\n", monster.nb);
        printf("pregnancy_time = %d\n", monster.pregnancy_time);
        printf("timer = %d\n", monster.timer);
        printf("id = %d\n", monster.monster.id);
        printf("type = %d\n", monster.monster.type);
        printf("health = %d\n", monster.monster.health);
        printf("fire = %d\n", monster.monster.fire);
        printf("x = %.2f\n", monster.monster.x);
        printf("y = %.2f\n\n", monster.monster.y);
    }

    close(fd);

    return 0;
}
