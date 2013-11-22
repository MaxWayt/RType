/*
** Mutex.hpp for Thread in /home/leroy_v/Perso/Thread
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Mon Oct 07 18:19:52 2013 vincent leroy
** Last update Mon Oct 07 18:39:46 2013 vincent leroy
*/

#ifndef MUTEX_H_
# define MUTEX_H_

#include "os.hpp"
#ifdef UNIX
#   include <pthread.h>
#else
#ifndef NOMINMAX
# define NOMINMAX
#endif
#   include <windows.h>
#endif /* OS_UNIX */

class Mutex
{
public:
    Mutex();
    virtual ~Mutex();

    bool lock();
    bool tryLock();
    bool unlock();

private:
    FOR_UNIX(pthread_mutex_t _mutex);
    FOR_WIN(HANDLE _handle);
};

class ScopLock
{
public:
    ScopLock(Mutex& mutex);
    virtual ~ScopLock();
private:
    Mutex& _mutex;
};

#endif /* !MUTEX_H_ */
