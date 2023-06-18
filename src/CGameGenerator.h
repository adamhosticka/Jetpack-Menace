#pragma once

#include <vector>
#include <memory>

class CPlayer;
class CPlayerHuman;
class CObject;
class CMap;

class CGameGenerator {
    private:
        const int m_BaseWidth = 40;
        const int m_BaseHeight = 10;
        const int m_BaseChunksCnt = 5;
        const int m_BaseCurrentChunk = 2;

    public:
        /**
         * @brief Generates players, objects and map
         * 
         * @param mainPlayers 
         * @param players 
         * @param objects 
         * @param map 
         * @return true Successful generating
         * @return false Unsuccessful generating
         */
        bool Run (std::vector<std::weak_ptr<CPlayerHuman>> & mainPlayers, std::vector<std::shared_ptr<CPlayer>> & players, 
            std::vector<std::shared_ptr<CObject>> & objects, std::shared_ptr<CMap> & map) const;
};