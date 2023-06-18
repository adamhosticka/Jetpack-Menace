#include <iostream>
#include <sstream>

#include "CMap.h"
#include "CPlayerAI.h"

using namespace std;

bool CPlayerAI::Move (shared_ptr<CMap> & map, EDirection direction) {
    //check surroundings
    for(int x = -m_Sight; x <= m_Sight; x++) {
        for(int y = -m_Sight; y <= m_Sight; y++) {
            if(x != 0 || y != 0) {
                shared_ptr<CCord> searchedCord = map->FindCord(m_Cord->m_X + x, m_Cord->m_Y + y, m_Cord->m_Chunk);
                if(searchedCord && searchedCord->m_Player) {
                    if(!Fight(searchedCord->m_Player))
                        return false;
                }
            }
        }
    }
    return false;
}

bool CPlayerAI::Fight (CPlayer * enemy) {
    if(enemy->GetArmor() >= 2*m_Armor) {
        m_Cord->m_Player = nullptr;
        UpdateArmor(-m_MaxArmor);
        enemy->KilledAttacker();
        return false;
    }
    return true;
}

void CPlayerAI::Fall (shared_ptr<CMap> & map) {}

void CPlayerAI::KilledAttacker () {}

int CPlayerAI::GetKills () const {
    return 0;
}

string CPlayerAI::GetInfo () const {
    stringstream info;
    info << m_Armor << "," << m_Sight << "," << m_Cord->m_X << "," << m_Cord->m_Y << "," << m_Cord->m_Chunk;
    return info.str();
}
