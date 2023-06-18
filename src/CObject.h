#pragma once

#include <vector>
#include <memory>

#include "CEntity.h"

class CPlayer;
class CCord;
class CMap;

class CObject : public CEntity {
    protected:
        bool m_Passable;
        unsigned long long int m_TicksAfterUpdate = 0;
        
        CObject ();
        CObject (char c) {m_Char = c;}

    public:
        virtual void Update ( std::shared_ptr<CMap> & map ) = 0;

        /**
         * @brief Collision efect depending on object
         * 
         * @param map 
         * @param player
         * @return true If object is passable
         * @return false If object isn't passable
         */
        virtual bool Collision ( std::shared_ptr<CMap> & map, CPlayer * player ) = 0;
        virtual std::string GetInfo () const override;
        
        bool IsDissapeared () const;
};
