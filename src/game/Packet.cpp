#include "Packet.hpp"

namespace Game
{

Packet::Packet(char buff[]) :
    _buff(), _wpos(2), _rpos(2)
{
    ::memcpy(_buff, buff, PACKET_SIZE);
}

Packet::Packet(Opcodes op) :
    _buff(), _wpos(0), _rpos(2)
{
    ::memset(_buff, 0, PACKET_SIZE);
    *this << uint16(op);
}

Packet& Packet::operator<<(uint8 value)
{
    append<uint8>(value);
    return *this;
}

Packet& Packet::operator<<(bool value)
{
    uint8 val = value ? 1 : 0;
    append<uint8>(val);
    return *this;
}

Packet& Packet::operator<<(uint16 value)
{
    append<uint16>(swap_endian(value));
    return *this;
}

Packet& Packet::operator<<(uint32 value)
{
    append<uint32>(swap_endian(value));
    return *this;
}

Packet& Packet::operator<<(uint64 value)
{
    append<uint64>(swap_endian(value));
    return *this;
}

Packet& Packet::operator<<(int8 value)
{
    append<int8>(value);
    return *this;
}

Packet& Packet::operator<<(int16 value)
{
    append<int16>(swap_endian(value));
    return *this;
}

Packet& Packet::operator<<(int32 value)
{
    append<int32>(swap_endian(value));
    return *this;
}

Packet& Packet::operator<<(int64 value)
{
    append<int64>(swap_endian(value));
    return *this;
}

Packet& Packet::operator<<(float value)
{
    append<float>(swap_endian(value));
    return *this;
}

Packet& Packet::operator<<(double value)
{
    append<double>(swap_endian(value));
    return *this;
}

Packet& Packet::operator<<(std::string const& value)
{
    append((char const*)value.c_str(), value.length());
    append((char)0);
    return *this;
}

Packet& Packet::operator>>(std::string& value)
{
    value.clear();
    while (_rpos < size())
    {
        char c = read<char>();
        if (c == 0)
            break;
        value += c;
    }
    return *this;
}

Packet& Packet::operator>>(uint8& value)
{
    value = read<uint8>();
    return *this;
}

Packet& Packet::operator>>(bool& value)
{
    uint8 val = read<uint8>();
    value = (val == 0 ? false : true);
    return *this;
}

Packet& Packet::operator>>(uint16& value)
{
    value = read<uint16>();
    return *this;
}

Packet& Packet::operator>>(uint32& value)
{
    value = read<uint32>();
    return *this;
}

Packet& Packet::operator>>(uint64& value)
{
    value = read<uint64>();
    return *this;
}

Packet& Packet::operator>>(int8& value)
{
    value = read<int8>();
    return *this;
}

Packet& Packet::operator>>(int16& value)
{
    value = read<int16>();
    return *this;
}

Packet& Packet::operator>>(int32& value)
{
    value = read<int32>();
    return *this;
}

Packet& Packet::operator>>(int64& value)
{
    value = read<int64>();
    return *this;
}

Packet& Packet::operator>>(float& value)
{
    value = read<float>();
    return *this;
}

Packet& Packet::operator>>(double& value)
{
    value = read<double>();
    return *this;
}

uint16 Packet::GetOpcode() const
{
    return read<uint16>(2);
}


void Packet::append(const char* data, uint32 size)
{
    if (PACKET_SIZE < _wpos + size)
        return;
    memcpy(&_buff[_wpos], data, size);
    _wpos += size;
}

}
