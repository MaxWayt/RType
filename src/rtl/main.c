/*
** main.c for rtl in /home/leroy_v/rtl
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Thu Nov 21 14:21:39 2013 vincent leroy
** Last update Thu Nov 21 19:49:10 2013 vincent leroy
*/

#include <string.h>
#include <stdio.h>

#include "rtl.h"

struct s_function
{
    char *key;
    int (*function)(int, char**);
};

static int usage()
{
    fprintf(stderr, "Usage: rtl\n");
    fprintf(stderr, "\trtl create _level_\n");
    fprintf(stderr, "\trtl list _level_\n");
    fprintf(stderr, "\trtl add _level_ [value]\n");
    fprintf(stderr, "\trtl remove _level_ [line]\n");
    fprintf(stderr, "\trtl edit _level_ line [param]\n\n");

    fprintf(stderr, "\t_level_ is the file you want edit\n");
    fprintf(stderr, "\tvalue is (in this order): nb pregnancy_time timer id type health fire x y\n");
    fprintf(stderr, "\tline is the line number you want modify in the file (between 1 and 20 include)\n");
    return 1;
}

int main(int ac, char **av)
{
    static struct s_function pointer[] = {
        {"create", &create_level},
        {"list", &list_level},
        {"add", &add_monster},
        {"remove", &remove_monster},
        {"edit", &edit_monster},
        {NULL, NULL}
    };
    int i;

    if (ac < 2)
        return usage();

    for (i = 0; pointer[i].function != NULL; ++i)
        if (strcmp(av[1], pointer[i].key) == 0)
        {
            int ret = pointer[i].function(ac - 2, av + 2);
            if (ret == -1)
                return usage();
            return ret;
        }

    fprintf(stderr, "Unknow command '%s'\n", av[1]);
    return usage();
}
