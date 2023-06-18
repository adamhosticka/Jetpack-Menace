#include <iomanip>
#include <stdexcept>

#include "CCord.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMap.h"

using namespace std;

CMap::CMap (int width, int height, int chunksCnt, int currentChunk) {
    m_Width = width;
    m_Height = height;
    m_ChunkCnt = chunksCnt;
    m_currentChunk = currentChunk;
    for(int i = 0; i < m_ChunkCnt; i++) {
        m_Chunks.push_back(new CChunk(i, m_Width, m_Height));
    }
}

CMap::~CMap () {
    for(int i = 0; i < m_ChunkCnt; i++) {
        delete m_Chunks[i];
    }
}

bool CMap::SpawnPlayersAndObjects (std::vector<std::shared_ptr<CPlayer>> & players, std::vector<std::shared_ptr<CObject>> & objects) {
    for(auto & object : objects) {
        shared_ptr<CCord> oldCord = object->GetCord();
        shared_ptr<CCord> searchedCord = m_Chunks[oldCord->m_Chunk]->FindCordInChunk(oldCord->m_X, oldCord->m_Y);
        object->UpdateCord(searchedCord);
        searchedCord->m_Object = object.get();
    }
    for(auto & player : players) {
        shared_ptr<CCord> oldCord = player->GetCord();
        shared_ptr<CCord> searchedCord = m_Chunks[oldCord->m_Chunk]->FindCordInChunk(oldCord->m_X, oldCord->m_Y);
        player->UpdateCord(searchedCord);
        if(searchedCord->m_Player) {
            return false;
        }
        searchedCord->m_Player = player.get();
    }
    return true;
}

void CMap::LoadChunk ( unsigned int chunkNr ) {
    m_currentChunk = chunkNr;
}

void CMap::Update (ostream & os) {
    m_Chunks[m_currentChunk]->DrawChunk(os, m_Width, m_Height, (m_currentChunk==0), (int(m_currentChunk) == m_ChunkCnt - 1));
}

void CMap::Update (ostream & os, unsigned int chunk) {
    LoadChunk(chunk);
    m_Chunks[m_currentChunk]->DrawChunk(os, m_Width, m_Height, (m_currentChunk==0), (int(m_currentChunk) == m_ChunkCnt - 1));
}

shared_ptr<CCord> CMap::FindCord (int x, int y, int chunk) const {
    if(y >= m_Height || y < 0)
        return nullptr;
    if(x >= m_Width) {
        if(chunk == m_ChunkCnt - 1)
            return nullptr;
        return FindCord(x - m_Width, y, chunk + 1);
    }
    if(x < 0) {
        if(chunk == 0)
            return nullptr;
        return FindCord(x + m_Width, y, chunk - 1);
    }

    return m_Chunks[chunk]->FindCordInChunk(x, y);
}

string CMap::GetInfo () const {
    stringstream info;
    info << m_Width << "," << m_Height << "," << m_ChunkCnt << "," << m_currentChunk;
    return info.str();
}
