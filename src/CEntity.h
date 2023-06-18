#pragma once

class CCord;

class CEntity {
    protected:
        char m_Char;
        std::shared_ptr<CCord> m_Cord;
        
        CEntity() = default;

    public:
        virtual std::string GetInfo () const = 0;

        void UpdateCord ( std::shared_ptr<CCord> & newCord);
        char GetChar () const;
        std::shared_ptr<CCord> GetCord () const;
};
