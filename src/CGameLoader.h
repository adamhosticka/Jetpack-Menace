#pragma once

#include <vector>
#include <memory>
#include <fstream>

class CPlayer;
class CPlayerHuman;
class CObject;
class CMap;

class CGameLoader {
    private:
        std::ifstream m_File;

    public:
        CGameLoader() = default;
        CGameLoader(std::string & fileName) : m_File(std::ifstream("examples/" + fileName)) {}

        /**
         * @brief Loads players, objects and map from file
         * 
         * @param mainPlayers 
         * @param players 
         * @param objects 
         * @param map 
         * @return true Successful loading
         * @return false Unsuccessful loading
         */
        bool Run (std::vector<std::weak_ptr<CPlayerHuman>> & mainPlayers, std::vector<std::shared_ptr<CPlayer>> & players, 
            std::vector<std::shared_ptr<CObject>> & objects, std::shared_ptr<CMap> & map);
        bool LoadPlayers (std::vector<std::weak_ptr<CPlayerHuman>> & mainPlayers, std::vector<std::shared_ptr<CPlayer>> & players);
        bool LoadObjects (std::vector<std::shared_ptr<CObject>> & objects);
        bool LoadMap (std::shared_ptr<CMap> & map);
};
