#ifndef OPCODES_H_
# define OPCODES_H_

enum Opcodes
{
    SMSG_GREETING               = 0,
    CMSG_PLAYER_KEY             = 1,
    CMSG_PLAYER_POSITION        = 2,
    OPCODE_COUNT

};

class Client;
class Packet;

class Opcode
{
public:
    struct OpcodeHandler
    {
        Opcodes op;
        void (Client::*handler)(Packet*);
    };
    static OpcodeHandler const* GetHandler(Opcodes op);
};

#endif /* !OPCODES_H_ */
