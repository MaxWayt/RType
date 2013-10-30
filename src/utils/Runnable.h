/*
 * RType
 *
 */

#ifndef RUNNABLE_H_
# define RUNNABLE_H_

#include <pthread.h>

class Runnable
{
public:
    virtual ~Runnable() {}

    virtual void operator()() = 0;
protected:
    void _run();
    void _stop();
    bool _isStopped() const;
    int _join();

private:
    pthread_t _thread;
    bool m_stop;
};

#endif /* !RUNNABLE_H_ */
