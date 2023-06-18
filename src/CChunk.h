#pragma once

#include "CCord.h"

class CPlayer;
class CPlayerAI;

class CChunk {
    private:
        const char m_hardWall = '#';
        const char m_softWall = '|';
        std::vector<std::vector<std::shared_ptr<CCord>>> m_Area;

    public:
        CChunk ();
        CChunk (unsigned int chunk, int width, int height);

        /**
         * @brief Prints chunk to ostream
         * 
         * @param os Output stream
         * @param width 
         * @param height 
         * @param leftHardWall If left wall is not passable
         * @param rightHardWall If right wall is not passable
         */
        void DrawChunk(std::ostream & os, int width, int height, bool leftHardWall, bool rightHardWall);
        std::shared_ptr<CCord> FindCordInChunk (unsigned int x, unsigned int y) const;
};