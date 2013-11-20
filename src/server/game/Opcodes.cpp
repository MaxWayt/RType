#include "Opcodes.h"
#include "Player.h"
#include "Packet.hpp"

namespace Game
{

Opcode::OpcodeHandler const* Opcode::GetHandler(Opcodes op)
{
    static OpcodeHandler handlers[] = {
        { SMSG_GREETING, NULL                               },
        { CMSG_PLAYER_KEY, NULL                             },
        { CMSG_PLAYER_POSITION, &Player::HandlePosition     },
        { CMSG_SHOT, &Player::HandleShot                    },
        { OPCODE_COUNT, NULL                                }

    };

    for (uint32 i = 0; handlers[i].op != OPCODE_COUNT; ++i)
        if (handlers[i].op == op)
            return &handlers[i];
    return NULL;
}

}
