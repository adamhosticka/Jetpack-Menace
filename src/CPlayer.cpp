#include "CPlayer.h"
#include "CCord.h"

void CPlayer::RemoveFromCord () {
    m_Cord->m_Player = nullptr;
}

void CPlayer::UpdateArmor (int value) {
    m_Armor += value;
    if(m_Armor > m_MaxArmor)
        m_Armor = m_MaxArmor;
    else if(m_Armor < 0)
        m_Armor = 0;
}

bool CPlayer::IsAlive () const {
    if(m_Armor > 0)
        return true;
    return false;
}

int CPlayer::GetArmor () const {
    return m_Armor;
}

bool CPlayer::IsFalling () const {
    return m_Falling;
}

EDirection CPlayer::FindDirection (const char input) const {
    auto it = m_Controls.find(input);
    if(it != m_Controls.end())
        return it->second;
    return EDirection::none;
}
