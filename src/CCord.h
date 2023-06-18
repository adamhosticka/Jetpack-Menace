#pragma once

#include <memory>

class CPlayer;
class CObject;

struct CCord {
    unsigned int m_X;
    unsigned int m_Y;
    unsigned int m_Chunk;
    CPlayer * m_Player = nullptr;
    CObject * m_Object = nullptr;

    CCord ();
    CCord (unsigned int x, unsigned int y, unsigned int chunk);

    /**
     * @brief Returns char depending on if there is an object, player or if the coordinate is empty
     * 
     * @return char 
     */
    char Display () const;
};
