/*
** os.hpp for Thread in /home/leroy_v/Perso/Thread
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Mon Oct 07 18:20:14 2013 vincent leroy
** Last update Mon Oct 07 18:20:36 2013 vincent leroy
*/

#ifndef OS_H_
# define OS_H_

#ifdef UNIX
#   define FOR_UNIX(...)    __VA_ARGS__
#   define FOR_WIN(...)
#   define OS_UNIX
#else
#   define FOR_UNIX(...)
#   define FOR_WIN(...)     __VA_ARGS__
#   define OS_WINDOWS
#endif /* __unix__ */

#endif /* !OS_H_ */
