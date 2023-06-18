#include <chrono>
#include <thread>
#include <sstream>

#include <iostream>

#include "CCord.h"
#include "CMap.h"
#include "CObject.h"
#include "CPlayerHuman.h"

using namespace std;

bool CPlayerHuman::Move (shared_ptr<CMap> & map, EDirection direction) {
    shared_ptr<CCord> newCord = nullptr;
    m_TicksAfterMove++;
    if(m_TicksAfterMove >= m_TicksBeforeFall && direction == EDirection::none)
        direction = EDirection::down;
    switch(direction) {
        case EDirection::up :
            newCord = map->FindCord(m_Cord->m_X, m_Cord->m_Y + 1, m_Cord->m_Chunk);
            break;
        case EDirection::down :
            newCord = map->FindCord(m_Cord->m_X, m_Cord->m_Y - 1, m_Cord->m_Chunk);
            break;
        case EDirection::left :
            newCord = map->FindCord(m_Cord->m_X - 1, m_Cord->m_Y, m_Cord->m_Chunk);
            break;
        case EDirection::right :
            newCord = map->FindCord(m_Cord->m_X + 1, m_Cord->m_Y, m_Cord->m_Chunk);
            break;
        default:
            break;
    }
    if(!newCord) {
        if(m_Cord->m_Object && m_TicksAfterMove % m_TicksBeforeFall == 0)
            m_Cord->m_Object->Collision(map, m_Cord->m_Player);
        return false;
    }

    m_TicksAfterMove = 0;

    if(newCord->m_Object) {
        if(!newCord->m_Object->Collision(map, m_Cord->m_Player)) {
            if(m_Cord->m_Object)
                m_Cord->m_Object->Collision(map, m_Cord->m_Player);
            return false;
        }
        if(!IsAlive() || newCord->m_Y > m_Cord-> m_Y + 1) // ochrana proti zpetnemu vraceni pri padu bourkou
            return false;
    }
    if(newCord->m_Player && newCord->m_Player != this) {
        int armorBeforeFight = m_Armor;
        if(!Fight(newCord->m_Player)) {
            m_Cord->m_Player = nullptr;
            return false;
        }
        if(m_Armor < armorBeforeFight) {
            if(m_Cord->m_Object)
                m_Cord->m_Object->Collision(map, m_Cord->m_Player);
            return false;
        }
    }
    m_Cord->m_Player = nullptr;
    newCord->m_Player = this;
    m_Cord = newCord;
    
    return true;
}

bool CPlayerHuman::Fight (CPlayer * enemy) {
    if(m_Armor > enemy->GetArmor()) {
        UpdateArmor(m_ArmorGainAfterFight);
        m_Kills++;
        enemy->RemoveFromCord();
        enemy->UpdateArmor(-m_MaxArmor);
        return true;
    }
    
    UpdateArmor(-m_FightDamage);
    if(!IsAlive()) {
        enemy->KilledAttacker();
        return false;
    }
    return true;
}

void CPlayerHuman::Fall (shared_ptr<CMap> & map) {
    int fallDistance = 0;
    m_Falling = true;
    while(Move(map, EDirection::down)) {
        fallDistance++;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    m_Falling = false;
    UpdateArmor(-fallDistance*m_FallDamage);
    if(!IsAlive())
        m_Cord->m_Player = nullptr;
}

void CPlayerHuman::KilledAttacker () {
    m_Kills++;
}

int CPlayerHuman::GetKills () const {
    return m_Kills;
}

string CPlayerHuman::GetInfo () const {
    stringstream info;
    info << m_Armor << "," << GetControls() << m_Kills << ","   
        << m_Cord->m_X << "," << m_Cord->m_Y << "," << m_Cord->m_Chunk;
    return info.str();
}

string CPlayerHuman::GetControls () const {
    stringstream controlsInfo;
    EDirection dirs[4] = {EDirection::up, EDirection::down, EDirection::left, EDirection::right};
    for(size_t i = 0; i < m_Controls.size(); i++) {
        for(auto it = m_Controls.begin(); it != m_Controls.end(); it++) {
            if((*it).second == dirs[i])
                controlsInfo << (*it).first << ",";
        }
    }
    return controlsInfo.str();
}
