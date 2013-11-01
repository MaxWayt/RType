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

#include "SharedDefines.h"
#include "os.hpp"
#if defined(LINUX) || defined(OSX)
#   include <pthread.h>
#else
#   include <windows.h>
#endif

class Thread
{
public:
    Thread();
    virtual ~Thread();

    bool _run();
    void _stop();
    void _join();

    inline bool _isStopped() const { return !_running; }

    virtual void operator()() = 0;

    static void Sleep(uint32 mstime);
private:
    bool _running;
    FOR_UNIX(pthread_t _threadId);
    FOR_WIN(HANDLE _hThread);
};

#endif /* !THREAD_H_ */
