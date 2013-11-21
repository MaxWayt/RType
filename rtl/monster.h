/*
** monster.h for rtl in /home/leroy_v/rtl
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Thu Nov 21 14:26:13 2013 vincent leroy
** Last update Thu Nov 21 18:27:50 2013 vincent leroy
*/

#ifndef MONSTER_H_
# define MONSTER_H_

#define NB_MAX_MONSTER_PER_LEVEL    20

#include "SharedDefines.h"

struct Monster
{
    uint32 id;
    uint32 type;
    uint8 health;
    uint8 fire;
    float x;
    float y;

};

struct QueenMonster
{
    uint32 nb;
    uint16 pregnancy_time;
    uint16 timer;
    struct Monster monster;
};

#endif /* !MONSTER_H_ */
