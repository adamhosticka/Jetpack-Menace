#include "CPlayer.h"
#include "CObjectTree.h"

using namespace std;

bool CObjectTree::Collision ( shared_ptr<CMap> & map,CPlayer * player) {
    return m_Passable;
}