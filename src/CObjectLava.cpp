#include "CPlayer.h"
#include "CObjectLava.h"

using namespace std;

bool CObjectLava::Collision ( shared_ptr<CMap> & map, CPlayer * player ) {
    player->UpdateArmor(-m_Damage);
    return m_Passable;
}