#include "Monster.h"
#include "Client.h"
#include "Opcodes.h"

Monster::Monster(uint32 id, int x, int y) : DamnCute::APhysics(x, y, true),
    _id(id), _fire(false), _shootPattern(NULL), _health(5), _sprite()
{
    _sprite.setPosition(x, y);
}

void Monster::collisionHandler(DamnCute::APhysics* other) {

    // 5 == player bullets
    if (other->getType() == 5) {
        DamnCute::Bullet* bullet = (DamnCute::Bullet*)other;
        if (bullet->getOwnerId() == sClient->GetPlayerId())
        {
            Packet pkt(CMSG_PLAYER_HIT_MONSTER);
            pkt << GetId();
            sClient->UDPSend(pkt);
        }
        bullet->setLife(0);
    }
}

void Monster::SetFire(bool fire)
{
    _fire = fire;
    if (!_shootPattern)
        return;
    if (!fire)
    {
        _shootPattern->setStatusGen(false);
    }
    else
    {
        UpdateFirePosition();
        _shootPattern->setStatusGen(true);
    }
}

void Monster::UpdateFirePosition()
{
    if (!_shootPattern)
        return;
    _shootPattern->moveOrigin(convertVec(_sprite.getPosition()));
}
