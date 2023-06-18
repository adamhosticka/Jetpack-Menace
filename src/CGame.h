#pragma once

#include <vector>

#include "CPlayer.h"
#include "CObject.h"
#include "CMap.h"

class CPlayerHuman;

class CGame {
    private:
        const int m_TickIsMs = 100;
        const char m_QuitGame = 'q';
        const char m_SaveGame = 'x';

        std::string m_Name;
        std::shared_ptr<CMap> m_Map;
        std::vector<std::weak_ptr<CPlayerHuman>> m_MainPlayers;
        std::vector<std::shared_ptr<CPlayer>> m_Players;
        std::vector<std::shared_ptr<CObject>> m_Objects;

    public:
        CGame();
        CGame(std::string name) : m_Name(name) {}
        CGame & operator= (const CGame&) = delete;
        CGame (const CGame&) = delete;
        ~CGame() = default;

        /**
         * @brief Method generates players and objects at random coordinations
         * 
         * @return true Generating success
         * @return false Generating fail
         */
        bool GenerateGame ();

        /**
         * @brief Method loads players and objects from given file
         * 
         * @return true Loading success
         * @return false Loading fail
         */
        bool LoadGame ();

        /**
         * @brief On every key detect (GetChar) move all players and RefreshOstream
         * 
         * @param os Output stream
         */
        void Run (std::ostream & os);

        /**
         * @brief Clears ostream, prints m_MainPlayers info and updates m_Map
         * 
         * @param os Output stream
         */
        void RefreshOstream (std::ostream & os);

        /**
         * @brief Detects pressed key and saves it to input
         * 
         * @param run Atomic type, determines if the asynch reading from input is still required
         * @param input Key pressed
         */
        static void GetChar (std::atomic<bool>& run, char & input);

        /**
         * @brief Saves the game to a file in examples/ named m_Name
         * 
         */
        void Save () const;

        /**
         * @brief Checks if atleast one main player is alive
         * 
         * @return true If atleast one main player is alive
         * @return false If all main players are dead
         */
        bool MainPlayersAlive () const;
};
