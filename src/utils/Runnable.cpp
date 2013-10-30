/*
 * RType
 *
 */

#include "Runnable.h"

static void* runnable(void* data)
{
    (*((Runnable*)data))();
    return NULL;
}

void Runnable::_run()
{
    m_stop = false;
    pthread_create(&_thread, NULL, runnable, this);
}

void Runnable::_stop()
{
    m_stop = true;
}

bool Runnable::_isStopped() const
{
    return m_stop;
}


int Runnable::_join()
{
    return pthread_join(_thread, NULL);
}

