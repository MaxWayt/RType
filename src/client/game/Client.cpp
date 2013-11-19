#include "Client.h"
#include "Utils.hpp"
#include "Opcodes.h"

#include <iostream>

Client::Client(int32 width, int32 height, bool fullscreen) : _service(), _udpSocket(this, _service), _clientKey(0),
    _recvQueue(), _display(this, width, height, fullscreen)
{
}

Client::~Client()
{
}

void Client::operator()()
{
    uint32 prevTime = GetMSTime();
    uint32 currTime = 0;
    uint32 prevSleep = 0;
    uint32 sleepTime = DEFAULT_SLEEP_TIME;
    while (!_isStopped())
    {
        currTime = GetMSTime();
        uint32 diff = GetMSTimeDiff(prevTime, currTime);

        Update(diff);
        prevTime = currTime;

        if (diff <= sleepTime + prevSleep)
        {
            prevSleep = sleepTime + prevSleep - diff;
            Thread::Sleep(prevSleep);
        }
        else
            prevSleep = 0;
    }
}

void Client::Start(uint32 clientId)
{
    _service.Start();
    _run();
    InitializeGame(clientId, "127.0.0.1", "5000"); 
    _display.Start(MODE_GAME); // Bloquant !
}

void Client::Stop()
{
    _service.Stop();
    _stop();
}

void Client::Wait()
{
    _service.Wait();
    _join();
}

void Client::Update(uint32 const diff)
{
    //client.InitializeGame(1, "127.0.0.1", "5000");
    UpdateIncomingPackets();
    UpdatePlayerPosition();

}

void Client::UpdateIncomingPackets()
{
    uint32 size = _recvQueue.size();
    for (uint32 i = 0; i < size && !_recvQueue.empty(); ++i)
    {
        Packet* pkt = _recvQueue.get();
        if (!pkt)
            continue;

        Opcode::OpcodeHandler const* opcodehandler = Opcode::GetHandler((Opcodes)pkt->GetOpcode());
        if (!opcodehandler)
        {
            std::cerr << "Error: receiv an unknow opcode : " << pkt->GetOpcode() << std::endl;
            delete pkt;
            continue;
        }
        if (opcodehandler->handler)
            (this->*(opcodehandler->handler))(pkt);

        delete pkt;
    }
}

void Client::UDPHandleReceive(Packet const* recvPkt)
{
    if (recvPkt->GetOpcode() == SMSG_PING)
    {
        Packet pkt(CMSG_PONG);
        UDPSend(pkt);
        return;
    }
    Packet* recv = new Packet(*recvPkt);
    _recvQueue.add(recv);
}

bool Client::InitializeGame(uint32 clientKey, std::string const& addr, std::string const& port)
{
    if (!_udpSocket.Connect(addr, port))
        return false;

    _clientKey = clientKey;
    return true;
}

void Client::UDPSend(Packet const& pkt)
{
    _udpSocket.Send(pkt.data(), pkt.size());
}

void Client::UpdatePlayerPosition()
{
    static sf::Vector2f pos(0.0f, 0.0f);

    if (DamnCute::APlayer const* player = _display.GetPlayer(_clientKey))
    {
        sf::Sprite const& sprite = player->getPlayer();
        sf::Vector2f const& newPos = sprite.getPosition();
        if (newPos != pos)
        {
            pos = newPos;
            Packet pkt(CMSG_PLAYER_POSITION);
            pkt << pos.x;
            pkt << pos.y;
            UDPSend(pkt);
        }
    }
}
