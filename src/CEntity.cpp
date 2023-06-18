#include <memory>

#include "CEntity.h"
#include "CCord.h"

using namespace std;

void CEntity::UpdateCord ( std::shared_ptr<CCord> & newCord) {
    m_Cord = newCord;
}

char CEntity::GetChar () const {
    return m_Char;
}

shared_ptr<CCord> CEntity::GetCord () const {
    return m_Cord;
}