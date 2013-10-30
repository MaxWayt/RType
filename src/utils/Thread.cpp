/*
** Thread.cpp for Thread in /home/leroy_v/Perso/Thread
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Mon Oct 07 15:47:33 2013 vincent leroy
** Last update Mon Oct 07 18:49:47 2013 vincent leroy
*/

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
    stop();
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
#ifdef OS_UNIX
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

#ifdef OS_UNIX
    pthread_join(_threadId, NULL);
#else
    WaitForSingleObject(_hThread, INFINITE);
    CloseHandle(_hThread);
#endif /* OS_UNIX */
}
