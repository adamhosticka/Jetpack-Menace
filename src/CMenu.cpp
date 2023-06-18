#include <fstream>

#include "CMenu.h"

using namespace std;

CMenu::CMenu (istream & is, ostream & os) : m_In (is), m_Out (os), m_Quit(false) {
    m_Commands = {
        {"start", 0},
        {"load", 1},
        {"help", 2},
        {"quit", 3},
    };
}

void CMenu::ProcessInput (const string & command) {
    auto it = m_Commands.find(command);
    if(it == m_Commands.end()) {
        m_Out << "> Unknown command" << endl;
    } else {
        switch(it->second) {
            case 0:
                StartGame();
                break;
            case 1:
                LoadGame();
                break;
            case 2:
                PromptHelp();
                break;
            case 3:
                QuitMenu();
                break;
            default:
                m_Out << "> Unknown command" << endl;
                break;
        }
    }
}

void CMenu::Run () {
    while(!m_Quit) {
        m_Out << "> " << "Enter a command [\"help\" for command info]:" << endl;
        string command;
        m_In >> command;
        if(m_In.eof())
            m_Quit = true;

        ProcessInput(command);
    }
}

void CMenu::StartGame () {
    m_Out << "> Name this game!" << endl;
    string name;
    m_In >> name;


    try {
        CGame game(name);
        if(!game.GenerateGame()) {
            m_Out << "> There has been an error creating a new game, try again..." << endl;
            return;
        }
        game.Run(m_Out);
    } catch (const exception& e) {
        m_Out << "!!!" << e.what() << "!!!" << endl;
    }
}

void CMenu::LoadGame () {
    string gameName;
    m_Out << "> Which game you want to load?" << endl;
    m_In >> gameName;
    ifstream gameFile( "examples/" + gameName );
    if(!gameFile.good()) {
        m_Out << "> This game doesn't exist..." << endl;
        return;
    }
    gameFile.close();

    try {
        CGame game(gameName);
        if(!game.LoadGame()) {
            m_Out << "> Couldn't load the game from this file..." << endl;
            return;
        }
        game.Run(m_Out);
    } catch (const exception& e) {
        m_Out << "!!!" << e.what() << "!!!" << endl;
    }
}

void CMenu::PromptHelp () {
    map<int, string> orderedCommands;
    for(auto & command : m_Commands) {
        orderedCommands[command.second] = command.first;
    }
    for(auto & command : orderedCommands) {
        m_Out << "\t> " << command.second << endl;
    }
}

void CMenu::QuitMenu () {
    m_Quit = true;
    m_Out << "Thank you for playing" << endl;
}
