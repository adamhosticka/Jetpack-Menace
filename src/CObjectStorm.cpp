#include "CPlayer.h"
#include "CObjectStorm.h"

using namespace std;

bool CObjectStorm::Collision ( shared_ptr<CMap> & map, CPlayer * player ) {
    if(!player->IsFalling()) {
        player->UpdateArmor(-m_Damage);
        player->Fall(map);
    }
    return m_Passable;
}