#pragma once

#include <memory>

#include "CPlayer.h"

class CPlayerAI : public CPlayer {
    private:
        static const int m_BaseSight = 3;
        int m_Sight = m_BaseSight;
        
    public:
        CPlayerAI() : CPlayer('E') {}
        CPlayerAI(int armor, int sight = m_BaseSight) : CPlayer('E', armor) {
            m_Sight = sight;
        }

        /**
         * @brief Fights enemies in the area based on his sight
         * 
         * @param map The map
         * @param direction The direction
         * @return true If player moved
         * @return false If player didn't move
         */
        virtual bool Move (std::shared_ptr<CMap> & map, EDirection direction) override;

        /**
         * @brief Dies if the enemy is much stronger
         * 
         * @param enemy The enemy
         * @return true If player is still alive
         * @return false If player died
         */
        virtual bool Fight (CPlayer * enemy) override;
        virtual void Fall (std::shared_ptr<CMap> & map) override;
        virtual void KilledAttacker () override;
        virtual int GetKills () const override;
        virtual std::string GetInfo () const override;
};
