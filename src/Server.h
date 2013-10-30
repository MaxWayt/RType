/*
 * RType
 *
 */

#ifndef SERVER_H_
# define SERVER_H_

#include "Thread.hpp"
#include "SharedDefines.h"

#define SERVER_SLEEP_TIME 50

class Server : public Thread
{
public:
    Server();

    void operator()();

    void Start();
    void Stop();
    void Wait();

    void Update(uint32 const diff);
};

#endif
