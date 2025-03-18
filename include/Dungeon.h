#pragma once
#include "Room.h"
#include <memory>
#include <vector>
#include <map>
#include <random>

class Dungeon
{
private:
    static std::shared_ptr<Dungeon> instance;
    std::vector<std::shared_ptr<Room>> rooms;
    std::shared_ptr<Room> startRoom;
    std::shared_ptr<Room> currentRoom;
    std::mt19937 rng;

    Dungeon();
    void generateDungeon(int numRooms);
    void connectRooms();

public:
    static std::shared_ptr<Dungeon> getInstance();

    void initialize(int numRooms);
    std::shared_ptr<Room> getStartRoom() const;
    std::shared_ptr<Room> getCurrentRoom() const;
    void setCurrentRoom(std::shared_ptr<Room> room);
    std::vector<std::shared_ptr<Room>> getRooms() const;
};
