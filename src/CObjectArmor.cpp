#include "CPlayer.h"
#include "CMap.h"
#include "CCord.h"
#include "CObjectArmor.h"

using namespace std;

void CObjectArmor::Update ( shared_ptr<CMap> & map ) {
    m_TicksAfterUpdate++;
    if(m_TicksAfterUpdate > 40 && (rand() % 300) == 0) {
        shared_ptr<CCord> newCord = map->FindCord(m_Cord->m_X + (rand() % 20 - 5), m_Cord->m_Y + (rand() % 10 - 5), m_Cord->m_Chunk);
        if(newCord && !newCord->m_Player && !newCord->m_Object) {
            newCord->m_Object = m_Cord->m_Object;
            m_Cord->m_Object = nullptr;
            m_Cord = newCord;
            m_TicksAfterUpdate = 0;
        }
    }
}

bool CObjectArmor::Collision ( shared_ptr<CMap> & map, CPlayer * player ) {
    player->UpdateArmor(m_Value);
    m_Cord->m_Object = nullptr;
    return m_Passable;
}
