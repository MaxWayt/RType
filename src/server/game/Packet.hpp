#ifndef PACKET_H_
# define PACKET_H_

#include "SharedDefines.h"
#include "Opcodes.h"
#include <cstddef>
#include <string>

#define PACKET_SIZE 256

namespace Game
{

inline bool my_is_big_endian()
{
    int32 i = 1;
    int8* ptr = (int8*)&i;
    return *ptr == 1 ? false : true;
}

template<class T>
T swap_endian(T u)
{
    if (my_is_big_endian())
        return u;

    union
    {
        T u;
        int8 u8[sizeof(T)];
    } src, dest;

    src.u = u;

    for (size_t i = 0; i < sizeof(T); ++i)
        dest.u8[i] = src.u8[sizeof(T) - i - 1];

    return dest.u;
}

class Packet
{
public:
    Packet(char buff[]);
    Packet(Opcodes op);

    char const* data() const { return _buff; }
    size_t size() const { return PACKET_SIZE; }

    uint16 GetOpcode() const;


    Packet& operator<<(uint8 value);
    Packet& operator<<(bool value);
    Packet& operator<<(uint16 value);
    Packet& operator<<(uint32 value);
    Packet& operator<<(uint64 value);
    Packet& operator<<(int8 value);
    Packet& operator<<(int16 value);
    Packet& operator<<(int32 value);
    Packet& operator<<(int64 value);
    Packet& operator<<(float value);
    Packet& operator<<(double value);
    Packet& operator<<(std::string const& value);
    Packet& operator>>(std::string& value);
    Packet& operator>>(uint8& value);
    Packet& operator>>(bool& value);
    Packet& operator>>(uint16& value);
    Packet& operator>>(uint32& value);
    Packet& operator>>(uint64& value);
    Packet& operator>>(int8& value);
    Packet& operator>>(int16& value);
    Packet& operator>>(int32& value);
    Packet& operator>>(int64& value);
    Packet& operator>>(float& value);
    Packet& operator>>(double& value);

private:
    template<class T>
    void append(T value)
    {
        append((char*)&value, sizeof(value));
    }

    template<class T>
    T read()
    {
        T val = read<T>(_rpos);
        _rpos += sizeof(T);
        return val;
    }

    template<class T>
    T read(uint32 pos) const
    {
        T val = *((T const*)&_buff[pos]);
        return swap_endian(val);
    }

    void append(const char* data, uint32 size);

    char _buff[PACKET_SIZE];
    uint16 _wpos;
    uint16 _rpos;
};

}

#endif /* !PACKET_H_ */
