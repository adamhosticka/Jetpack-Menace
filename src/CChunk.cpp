#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

#include "CPlayerAI.h"
#include "CChunk.h"

using namespace std;

CChunk::CChunk (unsigned int chunk, int width, int height) {
    m_Area.resize(width);
    for(int x = 0; x < width; x++) {
        m_Area[x].resize(height);
        for(int y = 0; y < height; y++) {
            m_Area[x][y] = shared_ptr<CCord> (new CCord(x, y, chunk));
        }
    }
}

void CChunk::DrawChunk (ostream & os, int width, int height, bool leftHardWall, bool rightHardWall) {
    char leftWall = m_softWall, rightWall = m_softWall;
    if(leftHardWall)
        leftWall = m_hardWall;
    if(rightHardWall)
        rightWall = m_hardWall;
    
    os << setw(width+2) << setfill(m_hardWall) << "" << setfill(' ') << setw(0) << endl;
    for(int y = height-1; y >= 0; y--) {
        os << leftWall;
        for(int x = 0; x < width; x++) {
            os << m_Area[x][y]->Display();
        }
        os << rightWall << endl;
    }
    os << setw(width+2) << setfill(m_hardWall) << "" << setfill(' ') << setw(0) << endl;
}

shared_ptr<CCord> CChunk::FindCordInChunk (unsigned int x, unsigned int y) const {
    return m_Area[x][y];
}
