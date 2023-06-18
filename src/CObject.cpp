#include <sstream>

#include "CCord.h"
#include "CObject.h"

using namespace std;

bool CObject::IsDissapeared () const {
    return m_Cord->m_Object == nullptr;
}

string CObject::GetInfo () const {
    stringstream info;
    info << m_Cord->m_X << "," << m_Cord->m_Y << "," << m_Cord->m_Chunk;
    return info.str();
}
