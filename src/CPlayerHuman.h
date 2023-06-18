#pragma once

#include <memory>

#include "CPlayer.h"

class CPlayerHuman : public CPlayer {
    private:
        static const int m_BaseArmorPlayer = 30;
        static const int m_FallDamage = 4;
        static const int m_ArmorGainAfterFight = 10;
        static const int m_FightDamage = 20;
        static const int m_TicksBeforeFall = 7;

        int m_Kills;
        unsigned long long int m_TicksAfterMove = 0;

    public:
        CPlayerHuman() : CPlayer('O') {}
        CPlayerHuman(int armor = m_BaseArmorPlayer, char up = '1', char down = '2', char left = '3', char right = '4', int kills = 0) : CPlayer('O', armor) {
            m_Kills = kills;
            m_Controls[up] = EDirection::up;
            m_Controls[down] = EDirection::down;
            m_Controls[left] = EDirection::left;
            m_Controls[right] = EDirection::right;
        }

        /**
         * @brief Tries to move player one block in the direction and possibly collides with object or fights a player
         * 
         * @param map The map
         * @param direction The direction
         * @return true If player moved
         * @return false If player didn't move
         */
        virtual bool Move (std::shared_ptr<CMap> & map, EDirection direction) override;

        /**
         * @brief Either kills the enemy or armor is reduced
         * 
         * @param enemy The enemy
         * @return true If player is still alive
         * @return false If player died
         */
        virtual bool Fight (CPlayer * enemy) override;
        virtual void Fall (std::shared_ptr<CMap> & map) override;
        
        /**
         * @brief Increases m_Kills
         * 
         */
        virtual void KilledAttacker () override;
        virtual int GetKills () const override;
        virtual std::string GetInfo () const override;

        std::string GetControls () const;
};
