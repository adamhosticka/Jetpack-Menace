#include "CPlayer.h"
#include "CObject.h"
#include "CCord.h"

using namespace std;

CCord::CCord () {}

CCord::CCord (unsigned int x, unsigned int y, unsigned int chunk) {
    m_X = x;
    m_Y = y;
    m_Chunk = chunk;
}

char CCord::Display () const {
    if(m_Object)
        return m_Object->GetChar();
    if(m_Player)
        return m_Player->GetChar();
    return ' ';
}
