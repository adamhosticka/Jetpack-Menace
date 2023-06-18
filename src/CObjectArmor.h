#pragma once

#include "CObject.h"

#include <memory>

class CObjectArmor : public CObject {
    private:
        const int m_Value = 10;

    public:
        CObjectArmor() : CObject('R') {m_Passable = true;}

        virtual void Update ( std::shared_ptr<CMap> & map ) override;

        /**
         * @brief Picks up object and increases player's armor 
         * 
         * @param map 
         * @param player 
         * @return true If object is passable
         * @return false If object isn't passable
         */
        virtual bool Collision ( std::shared_ptr<CMap> & map, CPlayer * player ) override;
};
