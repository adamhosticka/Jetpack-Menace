#pragma once

#include <vector>
#include <memory>

#include "CChunk.h"

class CCord;
class CPlayer;
class CObject;

class CMap {
    private:
        int m_Width;
        int m_Height;
        int m_ChunkCnt;
        unsigned int m_currentChunk;
        std::vector<CChunk *> m_Chunks;

    public:
        CMap ();
        CMap (int width, int height, int chunksCnt, int currentChunk);
        CMap & operator= (const CMap&) = delete;
        CMap (const CMap&) = delete;
        ~CMap ();
        
        /**
         * @brief Assigns players and objects to coordinates in areas in chunks
         * 
         * @param players The players
         * @param objects The objects
         * @return true Success
         * @return false If two players share same coordinate
         */
        bool SpawnPlayersAndObjects (std::vector<std::shared_ptr<CPlayer>> & players, std::vector<std::shared_ptr<CObject>> & objects);
        
        /**
         * @brief Calls DrawChunk
         * 
         * @param os Output stream
         */
        void Update (std::ostream & os);
        
        /**
         * @brief Loads chunk and calls DrawChunk
         * 
         * @param os Output stream
         * @param chunk Chunk number
         */
        void Update (std::ostream & os, unsigned int chunk);
        void LoadChunk ( unsigned int chunkNr );
        std::string GetInfo () const;

        /**
         * @brief Returns shared pointer to a CCord with coordinates x, y, chunk if exists
         * 
         * @param x 
         * @param y 
         * @param chunk 
         * @return std::shared_ptr<CCord> 
         */
        std::shared_ptr<CCord> FindCord ( int x, int y, int chunk) const;
};
