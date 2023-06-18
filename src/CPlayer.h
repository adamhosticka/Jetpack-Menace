#pragma once

#include <memory>
#include <map>

#include "CEntity.h"
#include "EDirection.h"

class CCord;
class CMap;

class CPlayer : public CEntity {
    protected:
        static const int m_MaxArmor = 100;
        static const int m_BaseArmor = 30;
        int m_Armor;
        bool m_Falling;
        std::map<char, EDirection> m_Controls;

        CPlayer ();
        CPlayer (char c, int armor = m_BaseArmor) {
            m_Char = c;
            m_Armor = armor;
            m_Falling = false;
        }
        
    public:
        virtual bool Move (std::shared_ptr<CMap> & map, EDirection direction) = 0;
        virtual bool Fight (CPlayer * enemy) = 0;

        /**
         * @brief Player falls until hits not passable object
         * 
         * @param map 
         */
        virtual void Fall (std::shared_ptr<CMap> & map) = 0;

        /**
         * @brief Find direction for player based on input and players controls
         * 
         * @param input 
         * @return EDirection
         */
        EDirection FindDirection (const char input) const;
        virtual void KilledAttacker () = 0;
        virtual int GetKills () const = 0;
        virtual std::string GetInfo () const = 0;

        void RemoveFromCord ();
        void UpdateArmor (int value);
        bool IsAlive () const;
        int GetArmor () const;
        bool IsFalling () const;
};
