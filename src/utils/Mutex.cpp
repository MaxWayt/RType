/*
** Mutex.cpp for Thread in /home/leroy_v/Perso/Thread
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Mon Oct 07 18:19:45 2013 vincent leroy
** Last update Mon Oct 07 18:53:37 2013 vincent leroy
*/

#include "Mutex.hpp"

Mutex::Mutex() :
    FOR_UNIX(_mutex())
    FOR_WIN(_handle())
{
    FOR_UNIX(pthread_mutex_init(&_mutex, NULL));
    FOR_WIN(_handle = CreateMutex(NULL, false, NULL));
}

Mutex::~Mutex()
{
    FOR_UNIX(pthread_mutex_destroy(&_mutex));
    FOR_WIN(CloseHandle(_handle));
}

bool Mutex::lock()
{
    FOR_UNIX(return pthread_mutex_lock(&_mutex) == 0);
    FOR_WIN(return WaitForSingleObject(_handle, INFINITE) == WAIT_OBJECT_0);
}

bool Mutex::tryLock()
{
    FOR_UNIX(return pthread_mutex_trylock(&_mutex) == 0);
    FOR_WIN(return WaitForSingleObject(_handle, 0) == WAIT_OBJECT_0);
}

bool Mutex::unlock()
{
    FOR_UNIX(return pthread_mutex_unlock(&_mutex) == 0);
    FOR_WIN(return ReleaseMutex(_handle));
}
