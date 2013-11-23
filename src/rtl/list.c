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
#include <fcntl.h>

#include "rtl.h"

int list_level(int ac, char **avi)
{
    FILE* fd;
    struct QueenMonster monster;

    if (ac < 1)
        return -1;

    if ((fd = fopen(avi[0], "r")) == NULL)
    {
        fprintf(stderr, "Unable to open file '%s': %m\n", avi[0]);
        return 1;
    }

    while (fread(&monster, sizeof(struct QueenMonster), 1, fd) > 0)
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

    fclose(fd);

    return 0;
}
