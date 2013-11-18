/*
** Thread.cpp for Thread in /home/leroy_v/Perso/Thread
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Mon Oct 07 15:47:33 2013 vincent leroy
** Last update Wed Oct 30 16:50:03 2013 vincent leroy
*/

#ifdef WIN32
# undef __STRICT_ANSI__
#elif defined(LINUX) || defined(OSX)
# include <unistd.h>
#endif

#include <iostream>

#include "Thread.hpp"

FOR_UNIX(static void* run(void *data))
FOR_WIN(static DWORD WINAPI run(void *data))
{
    Thread *th = static_cast<Thread*>(data);

    (*th)();
    return NULL;
}

Thread::Thread() :
    _running(false),
    FOR_UNIX(_threadId())
    FOR_WIN(_hThread())
{
}

Thread::~Thread()
{
    _stop();
}

bool Thread::_run()
{
    //std::cout << "creating thread" << std::endl;
    FOR_UNIX(if (pthread_create(&_threadId, NULL, &run, this) != 0))
    FOR_WIN(if ((_hThread = CreateThread(NULL, 0, &run, this, 0, NULL)) == NULL))
        return false;

    _running = true;
    return true;
}

void Thread::_stop()
{
    if (!_running)
        return ;

    //std::cout << "stopping thread" << std::endl;
#if defined(LINUX) || defined(OSX)
    pthread_cancel(_threadId);
#else
    TerminateThread(_hThread, 0);
#endif /* OS_UNIX */
    _running = false;
    //std::cout << "thread destroy" << std::endl;
}

void Thread::_join()
{
    if (!_running)
        return;

#if defined(LINUX) || defined(OSX)
    pthread_join(_threadId, NULL);
#else
    WaitForSingleObject(_hThread, INFINITE);
    CloseHandle(_hThread);
#endif /* OS_UNIX */
}

void Thread::Sleep(uint32 mstime)
{
#if defined(LINUX) || defined(OSX)
    usleep(mstime * IN_MILLISECONDS);
#else
    ::Sleep(mstime);
#endif
}
