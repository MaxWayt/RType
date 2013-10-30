/*
** Thread.hpp for Thread in /home/leroy_v/Perso/Thread
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Mon Oct 07 15:47:33 2013 vincent leroy
** Last update Mon Oct 07 18:20:47 2013 vincent leroy
*/

#ifndef THREAD_H_
# define THREAD_H_

#include "os.hpp"
#ifdef OS_UNIX
#   include <pthread.h>
#else
#   include <windows.h>
#endif

class Thread
{
public:
    Thread();
    virtual ~Thread();

    bool start();
    void stop();

    inline bool isStopped() const { return !_running; }

    virtual void operator()() = 0;

private:
    bool _running;
    FOR_UNIX(pthread_t _threadId);
    FOR_WIN(HANDLE _hThread);
};

#endif /* !THREAD_H_ */
