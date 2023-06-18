#include <random>

#include "CPlayerHuman.h"
#include "CPlayerAI.h"
#include "CObjectLava.h"
#include "CObjectStorm.h"
#include "CObjectArmor.h"
#include "CObjectTree.h"
#include "CCord.h"
#include "CMap.h"
#include "CGameGenerator.h"

using namespace std;

bool CGameGenerator::Run (vector<weak_ptr<CPlayerHuman>> & mainPlayers, vector<shared_ptr<CPlayer>> & players, 
            vector<shared_ptr<CObject>> & objects, shared_ptr<CMap> & map) const {
    
    shared_ptr<CPlayerHuman> p1 (new CPlayerHuman(50, 'w', 's', 'a', 'd'));
    mainPlayers.emplace_back(p1);
    players.emplace_back(mainPlayers.back());

    shared_ptr<CPlayerHuman> p2 (new CPlayerHuman(60, 't', 'g', 'f', 'h'));
    mainPlayers.emplace_back(p2);
    players.emplace_back(mainPlayers.back());

    shared_ptr<CPlayerHuman> p3 (new CPlayerHuman(50, 'i', 'k', 'j', 'l'));
    mainPlayers.emplace_back(p3);
    players.emplace_back(mainPlayers.back());

    // shared_ptr<CPlayerHuman> p4 (new CPlayerHuman(30));
    // mainPlayers.emplace_back(p4);
    // players.emplace_back(mainPlayers.back());

    int humanCnt = players.size();
    if(humanCnt > 10 || humanCnt > m_BaseWidth || m_BaseHeight < 1 || m_BaseWidth < 1 || m_BaseChunksCnt < 1 || 
            m_BaseCurrentChunk < 0 || m_BaseCurrentChunk > m_BaseChunksCnt - 1 || mainPlayers.size() == 0) {
        return false;
    }

    // source: https://stackoverflow.com/a/7560564
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(0, 50); // define the range

    for(int chunk = 0; chunk < m_BaseChunksCnt; chunk++) {
        for(int x = 0; x < m_BaseWidth; x++) {
            for(int y = 0; y < m_BaseHeight; y++) {
                if(chunk == m_BaseCurrentChunk && y == 0 && x >= (m_BaseWidth / 2) - (humanCnt / 2) 
                    && x < (m_BaseWidth / 2) - (humanCnt / 2) + humanCnt) {
                        shared_ptr<CCord> newCord (new CCord(x, y, chunk));
                        players[x - (m_BaseWidth / 2) + (humanCnt / 2)]->UpdateCord(newCord);;
                }
                else {
                    int random = distr(gen);
                    shared_ptr<CCord> newCord (new CCord(x, y, chunk));
                    if(random == 0) {
                        shared_ptr<CObjectLava> new_lava (new CObjectLava());
                        new_lava->UpdateCord(newCord);
                        objects.push_back(new_lava);
                    }
                    else if(random == 1) {
                        shared_ptr<CObjectArmor> new_armor (new CObjectArmor());
                        new_armor->UpdateCord(newCord);
                        objects.push_back(new_armor);
                    }
                    else if(random == 2 && y > 1) {
                        shared_ptr<CObjectStorm> new_storm (new CObjectStorm());
                        new_storm->UpdateCord(newCord);
                        objects.push_back(new_storm);
                    }
                    else if(random == 3) {
                        shared_ptr<CObjectTree> new_tree (new CObjectTree());
                        new_tree->UpdateCord(newCord);
                        objects.push_back(new_tree);
                    }
                    else if(random == 4) {
                        int random2 = (rand() % 49) + 1;
                        shared_ptr<CPlayerAI> new_ai (new CPlayerAI(random2 * 2, random2 % 5 + 1));
                        new_ai->UpdateCord(newCord);
                        players.push_back(new_ai);
                    }
                }
            }
        }
    }

    map = make_shared<CMap>(m_BaseWidth, m_BaseHeight, m_BaseChunksCnt, m_BaseCurrentChunk);
    return true;
}
