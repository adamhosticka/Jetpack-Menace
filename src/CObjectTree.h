#pragma once

#include "CObject.h"

#include <memory>

class CObjectTree : public CObject {
    public:
        CObjectTree() : CObject('Y') {m_Passable = false;}

        virtual void Update ( std::shared_ptr<CMap> & map ) override {}

        /**
         * @brief Nothing happens
         * 
         * @param map 
         * @param player
         * @return true If object is passable
         * @return false If object isn't passable
         */
        virtual bool Collision ( std::shared_ptr<CMap> & map, CPlayer * player ) override;
};
