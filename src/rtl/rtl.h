/*
** rtl.h for rtl in /home/leroy_v/rtl
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Thu Nov 21 15:34:24 2013 vincent leroy
** Last update Thu Nov 21 19:31:44 2013 vincent leroy
*/

#ifndef RTL_H_
# define RTL_H_

#include "monster.h"

int create_level(int ac, char **avi);
int list_level(int ac, char **avi);
void set_monster(struct QueenMonster *monster, int ac, char **avi);
int add_monster(int ac, char **avi);
int remove_monster(int ac, char **avi);
int edit_monster(int ac, char **avi);

#endif /* !RTL_H_ */
