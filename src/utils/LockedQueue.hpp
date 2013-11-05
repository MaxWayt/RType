
#ifndef LOCKEDQUEUE_H_
# define LOCKEDQUEUE_H_

#include <queue>
#include "Mutex.hpp"

template<class T>
class LockedQueue
{
public:
    void add(T* data)
    {
        ScopLock lock(_mutex);
        _queue.push(data);
    }

    T* get()
    {
        ScopLock lock(_mutex);
        if (_queue.empty())
            return NULL;
        T* data = _queue.front();
        _queue.pop();
        return data;
    }

    uint32 size() const
    {
        return _queue.size();
    }

    bool empty() const
    {
        return _queue.empty();
    }

private:
    Mutex _mutex;
    std::queue<T*> _queue;
};

#endif /* !LOCKEDQUEUE_H_ */
