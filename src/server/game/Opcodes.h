#ifndef OPCODES_H_
# define OPCODES_H_

namespace Game
{

enum Opcodes
{
    SMSG_GREETING               = 0,
    CMSG_PLAYER_KEY             = 1,
    CMSG_PLAYER_POSITION        = 2,
    OPCODE_COUNT

};

class Player;
class Packet;

class Opcode
{
public:
    struct OpcodeHandler
    {
        Opcodes op;
        void (Player::*handler)(Packet*);
    };
    static OpcodeHandler const* GetHandler(Opcodes op);
};

}

#endif /* !OPCODES_H_ */
