#pragma once

#include "CObject.h"

#include <memory>

class CObjectStorm : public CObject {
    private:
        static const int m_Damage = 4;
    public:
        CObjectStorm() : CObject('@') {m_Passable = true;}

        virtual void Update ( std::shared_ptr<CMap> & map ) override {}

        /**
         * @brief Player falls and his armor is reduced
         * 
         * @param map 
         * @param player
         * @return true If object is passable
         * @return false If object isn't passable
         */
        virtual bool Collision ( std::shared_ptr<CMap> & map, CPlayer * player ) override;
};
