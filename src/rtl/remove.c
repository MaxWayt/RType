/*
** remove.c for rtl in /home/leroy_v/rtl
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Thu Nov 21 18:19:41 2013 vincent leroy
** Last update Thu Nov 21 19:33:25 2013 vincent leroy
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "rtl.h"

int remove_monster(int ac, char **avi)
{    
	int line;
    FILE* fd;
    struct QueenMonster monster[NB_MAX_MONSTER_PER_LEVEL];
    int i;
    struct QueenMonster dumy;
    int j;

    if (ac < 1)
        return -1;

    if (ac == 1)
    {
        char resp;

        printf("Do you really want delete this file [y/N]: ");
        fflush(stdout);
		resp = getchar();
        if (resp == 'y')
            unlink(avi[0]);

        return 0;
    }

	line = atoi(avi[1]);
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

    if ((fd = fopen(avi[0], "r")) == NULL)
    {
        fprintf(stderr, "Unable to open file '%s': %m\n", avi[0]);
        return 1;
    }

    for (i = 0; i < line; ++i)
    {
        if (fread(&monster[i], sizeof(struct QueenMonster), 1, fd) <= 0)
        {
            fprintf(stderr, "The file '%s' has only %d line%c\n", avi[0], i + 1, i > 0 ? 's' : '\0');
            fclose(fd);
            return 1;
        }
    }

    if (fread(&dumy, sizeof(struct QueenMonster), 1, fd) > 0)
    {
        while (fread(&monster[i], sizeof(struct QueenMonster), 1, fd) > 0)
            ++i;
    }
    else
    {
        fprintf(stderr, "The file '%s' has only %d line%c\n", avi[0], i, i > 0 ? 's' : '\0');
        fclose(fd);
        return 1;
    }

    fclose(fd);
    if ((fd = fopen(avi[0], "w")) == NULL)
    {
        fprintf(stderr, "Unable to open file '%s': %m\n", avi[0]);
        return 1;
    }

    for (j = 0; j < i; ++j)
        fwrite(&monster[j], sizeof(struct QueenMonster), 1, fd);

    fclose(fd);

    return 0;
}
