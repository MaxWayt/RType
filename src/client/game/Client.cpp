#include "Client.h"
#include "Utils.hpp"
#include "Opcodes.h"

#include <iostream>

Client::Client() : _service(), _udpSocket(this, _service), _clientKey(0),
    _recvQueue()
{}

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

void Client::Start()
{
    _service.Start();
    _run();
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
    UpdateIncomingPackets();

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

void Client::UDPHandleReceive(Packet* recvPkt)
{
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
