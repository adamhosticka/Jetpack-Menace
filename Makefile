CXX=g++
CXXFLAGS=-Wall -pedantic -pthread

HEADERS = $(wildcard src/*.h)
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)

.PHONY: all
all: hostiada doc

.PHONY: run
run: compile
	./hostiada

.PHONY: compile
compile: hostiada

hostiada: build/main
	cp $< $@

build/main: $(OBJECTS)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@

build/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -c -o $@

doc: Doxyfile $(HEADERS)
	doxygen Doxyfile

.PHONY: clean
clean:
	rm -rf hostiada build/ doc/ 2>/dev/null


CChunk.o: src/CChunk.cpp src/CPlayerAI.h src/CPlayer.h src/CEntity.h \
 src/EDirection.h src/CChunk.h src/CCord.h
CCord.o: src/CCord.cpp src/CPlayer.h src/CEntity.h src/EDirection.h \
 src/CObject.h src/CCord.h
CEntity.o: src/CEntity.cpp src/CEntity.h src/CCord.h
CGame.o: src/CGame.cpp src/CPlayerAI.h src/CPlayer.h src/CEntity.h \
 src/EDirection.h src/CPlayerHuman.h src/CObjectLava.h src/CObject.h \
 src/CObjectArmor.h src/CObjectStorm.h src/CObjectTree.h \
 src/CGameGenerator.h src/CGameLoader.h src/CGame.h src/CMap.h \
 src/CChunk.h src/CCord.h
CGameGenerator.o: src/CGameGenerator.cpp src/CPlayerHuman.h src/CPlayer.h \
 src/CEntity.h src/EDirection.h src/CPlayerAI.h src/CObjectLava.h \
 src/CObject.h src/CObjectStorm.h src/CObjectArmor.h src/CObjectTree.h \
 src/CCord.h src/CMap.h src/CChunk.h src/CGameGenerator.h
CGameLoader.o: src/CGameLoader.cpp src/CPlayerHuman.h src/CPlayer.h \
 src/CEntity.h src/EDirection.h src/CPlayerAI.h src/CObjectLava.h \
 src/CObject.h src/CObjectStorm.h src/CObjectArmor.h src/CObjectTree.h \
 src/CCord.h src/CMap.h src/CChunk.h src/CGameLoader.h
CMap.o: src/CMap.cpp src/CCord.h src/CObject.h src/CEntity.h \
 src/CPlayer.h src/EDirection.h src/CMap.h src/CChunk.h
CMenu.o: src/CMenu.cpp src/CMenu.h src/CGame.h src/CPlayer.h \
 src/CEntity.h src/EDirection.h src/CObject.h src/CMap.h src/CChunk.h \
 src/CCord.h
CObjectArmor.o: src/CObjectArmor.cpp src/CPlayer.h src/CEntity.h \
 src/EDirection.h src/CMap.h src/CChunk.h src/CCord.h src/CObjectArmor.h \
 src/CObject.h
CObject.o: src/CObject.cpp src/CCord.h src/CObject.h src/CEntity.h
CObjectLava.o: src/CObjectLava.cpp src/CPlayer.h src/CEntity.h \
 src/EDirection.h src/CObjectLava.h src/CObject.h
CObjectStorm.o: src/CObjectStorm.cpp src/CPlayer.h src/CEntity.h \
 src/EDirection.h src/CObjectStorm.h src/CObject.h
CObjectTree.o: src/CObjectTree.cpp src/CPlayer.h src/CEntity.h \
 src/EDirection.h src/CObjectTree.h src/CObject.h
CPlayerAI.o: src/CPlayerAI.cpp src/CMap.h src/CChunk.h src/CCord.h \
 src/CPlayerAI.h src/CPlayer.h src/CEntity.h src/EDirection.h
CPlayer.o: src/CPlayer.cpp src/CPlayer.h src/CEntity.h src/EDirection.h \
 src/CCord.h
CPlayerHuman.o: src/CPlayerHuman.cpp src/CCord.h src/CMap.h src/CChunk.h \
 src/CObject.h src/CEntity.h src/CPlayerHuman.h src/CPlayer.h \
 src/EDirection.h
main.o: src/main.cpp src/CMenu.h src/CGame.h src/CPlayer.h src/CEntity.h \
 src/EDirection.h src/CObject.h src/CMap.h src/CChunk.h src/CCord.h
