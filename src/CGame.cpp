#include <iostream>
#include <fstream>
#include <unistd.h>
#include <termios.h>
#include <thread>
#include <atomic>
#include <cstdlib>

#include "CPlayerAI.h"
#include "CPlayerHuman.h"
#include "CObjectLava.h"
#include "CObjectArmor.h"
#include "CObjectStorm.h"
#include "CObjectTree.h"
#include "CGameGenerator.h"
#include "CGameLoader.h"
#include "CGame.h"

using namespace std;

bool CGame::GenerateGame () {
    CGameGenerator gameGenerator;
    if(!gameGenerator.Run(m_MainPlayers, m_Players, m_Objects, m_Map) ||
        !m_Map->SpawnPlayersAndObjects(m_Players, m_Objects)) {
            return false;
        }
    return true;
}

bool CGame::LoadGame () {
    CGameLoader gameLoader(m_Name);
    if(!gameLoader.Run(m_MainPlayers, m_Players, m_Objects, m_Map) ||
        !m_Map->SpawnPlayersAndObjects(m_Players, m_Objects)) {
            return false;
        }
    return true;
}

// source: https://stackoverflow.com/a/912796 + https://stackoverflow.com/a/31500127
void CGame::GetChar (std::atomic<bool>& run, char & input) {
    while (run.load()) {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        input = buf;
    }
}

void CGame::RefreshOstream (ostream & os) {
    system ( "clear" );
    os << flush;
    int firstAlive = -1;
    for(size_t pos = 0; pos < m_MainPlayers.size(); pos++) {
        if(m_MainPlayers[pos].lock()) {
            if(firstAlive == - 1)
                firstAlive = pos;
            string controls = m_MainPlayers[pos].lock()->GetControls();
            if(controls.length() > 0)
                controls.pop_back();
            os << "Player " << pos + 1 << ": (" << controls << ")" << endl;
            os << "  Kills: " << m_MainPlayers[pos].lock()->GetKills() << endl;
            os << "  Armor: " << m_MainPlayers[pos].lock()->GetArmor() << endl;
        } else {
            os << "Player " << pos + 1 << ": (DEAD)" << endl;
        }
    }
    if(MainPlayersAlive()) {
        m_Map->Update(os, m_MainPlayers[firstAlive].lock()->GetCord()->m_Chunk);
        os << "Press q to quit or x to save game" << endl;
    } else {
        m_Map->Update(os);
    }
}

void CGame::Run (ostream & os) {
    char input = '\0';

    std::atomic<bool> run(true);
    std::thread cinThread(GetChar, std::ref(run), std::ref(input));

    while(1) {
        if(!MainPlayersAlive()) {
            os << "=====YOU DIED=====" << endl;
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(m_TickIsMs));
        if(input == m_SaveGame) {
            os << "=====Saving game=====" << endl;
            Save();
            input = '\0';
            continue;
        }
        if(input == m_QuitGame) {
            os << "=====Game exited by pressing " << m_QuitGame << "=====" << endl;
            break;
        }
        for(auto player_it = m_Players.begin(); player_it != m_Players.end(); player_it++) {
            if(!(*player_it)->IsAlive()) {
                m_Players.erase(player_it);
                player_it--;
                continue;
            }
            EDirection direction = (*player_it)->FindDirection(input);
            (*player_it)->Move(m_Map, direction);

            if(!(*player_it)->IsAlive()) {
                (*player_it)->RemoveFromCord();
                m_Players.erase(player_it);
                player_it--;
            }
        }

        for(auto object_it = m_Objects.begin(); object_it != m_Objects.end(); object_it++) {
            if((*object_it)->IsDissapeared()) {
                m_Objects.erase(object_it);
                object_it--;
                continue;
            }
            (*object_it)->Update(m_Map);
        }

        input = '\0';
        RefreshOstream(os);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(600));
    run.store(false);
    os << "Press any key to go back to menu" << endl;
    cinThread.join();
    system ( "clear" );
    os << flush;
}

void CGame::Save () const {
    ofstream saveFile("examples/" + m_Name);

    saveFile << "Players {" << endl;
    for(auto & player : m_Players) {
        saveFile << typeid(*player).name() << "," << player->GetInfo() << endl;
    }
    saveFile << "}" << endl;

    saveFile << "Objects {" << endl;
    for(auto & object : m_Objects) {
        saveFile << typeid(*object).name() << "," << object->GetInfo() << endl;
    }
    saveFile << "}" << endl;

    saveFile << "Map {" << endl;
    saveFile << m_Map->GetInfo() << endl;
    saveFile << "}" << endl;

    saveFile.close();
}

bool CGame::MainPlayersAlive () const {
    for(auto & mainPlayer : m_MainPlayers) {
        if(mainPlayer.lock()) {
            return true;
        }
    }
    return false;
}
