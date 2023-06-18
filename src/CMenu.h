#pragma once

#include <map>

#include "CGame.h"

class CMenu {
    private:
        std::istream & m_In;    
        std::ostream & m_Out;
        std::map<std::string, int> m_Commands;
        bool m_Quit = false;

    public:
        CMenu (std::istream & is, std::ostream & os);
        
        /**
         * @brief Reading user input and passing it to ProccessInput while m_Quit is false
         * 
         */
        void Run ();

        /**
         * @brief Proccessing user input, calling suitable methods
         * 
         * @param command User input
         */
        void ProcessInput (const std::string & command);
        void StartGame ();
        void LoadGame ();
        void PromptHelp ();
        void QuitMenu ();
};
