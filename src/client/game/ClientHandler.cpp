#include "Client.h"
#include "Opcodes.h"
#include <iostream>

void Client::HandleGreeting(Packet* recvPkt)
{
    Packet pkt(CMSG_PLAYER_KEY);
    pkt << uint32(_clientKey);

    UDPSend(pkt);
}
