#ifndef OPCODES_H_
# define OPCODES_H_

#include "Packet.hpp"

namespace Game
{

enum Opcodes
{
    SMSG_GREETING               = 0,
    CMSG_PLAYER_KEY             = 1,
    SMSG_CONNECT_RESULT         = 2,
    CMSG_PLAYER_POSITION        = 3,
    SMSG_PLAYER_POSITION        = 4,
    SMSG_ADD_PLAYER             = 5,
    SMSG_PING                   = 6,
    CMSG_PONG                   = 7,
    SMSG_REMOVE_PLAYER          = 8,
    CMSG_SHOT                   = 9,
    SMSG_SHOT                   = 10,
    OPCODE_COUNT

};

enum ConnectResults
{
    CONNECT_OK                  = 0,
    CONNECT_FAIL                = 1,
};

class Player;

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
