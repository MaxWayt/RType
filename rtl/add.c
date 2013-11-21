/*
** add.c for rtl in /home/leroy_v/rtl
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Thu Nov 21 17:40:39 2013 vincent leroy
** Last update Thu Nov 21 19:33:00 2013 vincent leroy
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rtl.h"

void set_monster(struct QueenMonster *monster, int ac, char **avi)
{
    monster->nb = ac >= 1 ? (uint32)atoi(avi[0]) : monster->nb;
    monster->pregnancy_time = ac >= 2 ? (uint16)atoi(avi[1]) : monster->pregnancy_time;
    monster->timer = ac >= 3 ? (uint16)atoi(avi[2]) : monster->timer;
    monster->monster.id = ac >= 4 ? (uint32)atoi(avi[3]) : monster->monster.id;
    monster->monster.type = ac >= 5 ? (uint32)atoi(avi[4]) : monster->monster.type;
    monster->monster.health = ac >= 6 ? (uint8)atoi(avi[5]) : monster->monster.health;
    monster->monster.fire = ac >= 7 ? (uint8)atoi(avi[6]) : monster->monster.fire;
    monster->monster.x = ac >= 8 ? (float)atof(avi[7]) : monster->monster.x;
    monster->monster.y = ac >= 9 ? (float)atof(avi[8]) : monster->monster.y;
}

int add_monster(int ac, char **avi)
{
    if (ac < 1)
        return -1;

    int fd;
    if ((fd = open(avi[0], O_RDWR)) == -1)
    {
        fprintf(stderr, "Unable to open file '%s': %m\n", avi[0]);
        return 1;
    }

    struct QueenMonster monster;
    int i = 0;

    while (read(fd, &monster, sizeof(struct QueenMonster)) > 0)
        ++i;

    if (i >= NB_MAX_MONSTER_PER_LEVEL)
    {
        fprintf(stderr, "Too much monster in this level. Canno't add\n");
        return 1;
    }

    memset(&monster, 0, sizeof(struct QueenMonster));
    set_monster(&monster, ac - 1, avi + 1);

    write(fd, &monster, sizeof(struct QueenMonster));

    close(fd);

    return 0;
}
