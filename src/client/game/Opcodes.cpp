#include "Opcodes.h"
#include "Client.h"
#include "Packet.hpp"

Opcode::OpcodeHandler const* Opcode::GetHandler(Opcodes op)
{
    static OpcodeHandler handlers[] = {
        { SMSG_GREETING, &Client::HandleGreeting            },
        { OPCODE_COUNT, NULL                                }

    };

    for (uint32 i = 0; handlers[i].op != OPCODE_COUNT; ++i)
        if (handlers[i].op == op)
            return &handlers[i];
    return NULL;
}
