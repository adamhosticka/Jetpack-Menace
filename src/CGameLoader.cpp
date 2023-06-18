#include <iostream>
#include <sstream>

#include "CPlayerHuman.h"
#include "CPlayerAI.h"
#include "CObjectLava.h"
#include "CObjectStorm.h"
#include "CObjectArmor.h"
#include "CObjectTree.h"
#include "CCord.h"
#include "CMap.h"
#include "CGameLoader.h"

using namespace std;

bool CGameLoader::Run (vector<weak_ptr<CPlayerHuman>> & mainPlayers, vector<shared_ptr<CPlayer>> & players, 
                        vector<shared_ptr<CObject>> & objects, shared_ptr<CMap> & map) {

    string line;
    bool loaded[3] = {false, false, false};

    try {
        while(getline(m_File, line)) {
            if(line == "Players {") {
                if(!LoadPlayers(mainPlayers, players)) {
                    m_File.close();
                    return false;
                }
                loaded[0] = true;
            } 
            else if(line == "Objects {") {
                if(!LoadObjects(objects)) {
                    m_File.close();
                    return false;
                }
                loaded[1] = true;
            } 
            else if(line == "Map {") {
                if(!LoadMap(map)) {
                    m_File.close();
                    return false;   
                }
                loaded[2] = true;
            } 
            else if (line.length() == 0) {
                continue;
            } else {
                m_File.close();
                return false;
            }
        }
    } catch ( ... ) {
        m_File.close();
        return false;
    } 

    if(mainPlayers.size() == 0 || loaded[0] == false || loaded[1] == false || loaded[2] == false) {
        m_File.close();
        return false;
    }

    m_File.close();
    return true;
}

bool CGameLoader::LoadPlayers (vector<weak_ptr<CPlayerHuman>> & mainPlayers, vector<shared_ptr<CPlayer>> & players) {
    string line, word;
    vector<string> words;

    while(getline(m_File, line)) {
        if(line == "}")
            break;

        istringstream issLine(line);
        while(getline(issLine, word, ',')) {
            words.push_back(word);
        }

        if (words.size() == 0) {
            continue;
        } 
        else if(words[0] == typeid(CPlayerHuman).name()) {
            if(words.size() < 10)
                continue;

            shared_ptr<CPlayerHuman> p1 (new CPlayerHuman(stoi(words[1]), words[2].c_str()[0], words[3].c_str()[0], 
                words[4].c_str()[0], words[5].c_str()[0], stoi(words[6])));
            mainPlayers.push_back(p1);
            players.push_back(p1);
            shared_ptr<CCord> newCord (new CCord(stoi(words[7]), stoi(words[8]), stoi(words[9])));
            players.back()->UpdateCord(newCord);
            words.erase(words.begin(), words.begin() + 10);
        } 
        else if(words[0] == typeid(CPlayerAI).name()) {
            if(words.size() < 6)
                continue;

            players.emplace_back(make_shared<CPlayerAI> (stoi(words[1]), stoi(words[2])));
            shared_ptr<CCord> newCord (new CCord(stoi(words[3]), stoi(words[4]), stoi(words[5])));
            players.back()->UpdateCord(newCord); 
            words.erase(words.begin(), words.begin() + 6);
        } 
        else {
            return false;
        }
    }

    if(words.size() != 0)
        return false;
    return true;
}

bool CGameLoader::LoadObjects (vector<shared_ptr<CObject>> & objects) {
    string line, word;
    vector<string> words;

    while(getline(m_File, line)) {
        if(line == "}")
            break;

        istringstream issLine(line);
        while(getline(issLine, word, ',')) {
            words.push_back(word);
        }

        if(words.size() < 4)
            continue;

        shared_ptr<CCord> newCord (new CCord(stoi(words[1]), stoi(words[2]), stoi(words[3])));
        if(words[0] == typeid(CObjectLava).name())
            objects.emplace_back(make_shared<CObjectLava> ());
        else if(words[0] == typeid(CObjectArmor).name())
            objects.emplace_back(make_shared<CObjectArmor> ());
        else if(words[0] == typeid(CObjectStorm).name())
            objects.emplace_back(make_shared<CObjectStorm> ());
        else if(words[0] == typeid(CObjectTree).name())
            objects.emplace_back(make_shared<CObjectTree> ());
        else
            return false;
        objects.back()->UpdateCord(newCord);
        words.erase(words.begin(), words.begin() + 4);
    }

    if(words.size() != 0)
        return false;
    return true;
}

bool CGameLoader::LoadMap (shared_ptr<CMap> & map) {
    string line, word;
    vector<string> words;
    bool endBracket = false;

    while(getline(m_File, line)) {
        if(line == "}") {
            endBracket = true;
            break;
        }

        istringstream issLine(line);
        while(getline(issLine, word, ',')) {
            words.push_back(word);
        }
        if(words.size() < 4)
            continue;
        
        map = make_shared<CMap>(stoi(words[0]), stoi(words[1]), stoi(words[2]), stoi(words[3]));
        words.erase(words.begin(), words.begin() + 4);
    }

    if(words.size() != 0 || !endBracket)
        return false;
    return true;
}