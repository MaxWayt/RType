/*
 * RType
 *
 */

#ifndef SINGLETON_H_
# define SINGLETON_H_

#ifndef NULL
# define NULL 0x0
#endif

template<class T>
class Singleton
{
public:
    static T* instance()
    {
        static T* instance = NULL;
        if (!instance)
            instance = new T();
        return instance;
    }
};

#endif /* !SINGLETON_H_ */
