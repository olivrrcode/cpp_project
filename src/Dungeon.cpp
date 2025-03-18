#include "../include/Dungeon.h"
#include "../include/RoomFactory.h"
#include <algorithm>
#include <iostream>

std::shared_ptr<Dungeon> Dungeon::instance = nullptr;

Dungeon::Dungeon()
{
    std::random_device rd;
    rng = std::mt19937(rd());
}

std::shared_ptr<Dungeon> Dungeon::getInstance()
{
    if (!instance)
    {
        instance = std::shared_ptr<Dungeon>(new Dungeon());
    }
    return instance;
}

void Dungeon::initialize(int numRooms)
{
    rooms.clear();
    generateDungeon(numRooms);
    startRoom = rooms[0];
    currentRoom = startRoom;
}

void Dungeon::generateDungeon(int numRooms)
{
    if (numRooms < 5)
        numRooms = 5; // Minimum 5 rooms

    // Create different room types
    // First room is always empty (starting room)
    rooms.push_back(RoomFactory::createRoom(Room::Type::EMPTY, 0));

    // Last room is always treasure
    std::shared_ptr<Room> treasureRoom = RoomFactory::createRoom(Room::Type::TREASURE, numRooms - 1);

    // Create remaining rooms with different types
    for (int i = 1; i < numRooms - 1; ++i)
    {
        Room::Type type;
        std::uniform_int_distribution<> typeDist(0, 2);
        int randomType = typeDist(rng);

        switch (randomType)
        {
        case 0:
            type = Room::Type::EMPTY;
            break;
        case 1:
            type = Room::Type::MONSTER;
            break;
        case 2:
            type = Room::Type::UPGRADE;
            break;
        default:
            type = Room::Type::EMPTY;
        }

        rooms.push_back(RoomFactory::createRoom(type, i));
    }

    // Add treasure room last
    rooms.push_back(treasureRoom);

    // Connect the rooms
    connectRooms();
}

void Dungeon::connectRooms()
{
    // Simple algorithm: create a path from start to treasure, then add some random connections

    // First, create a direct path from start to treasure
    for (size_t i = 0; i < rooms.size() - 1; ++i)
    {
        rooms[i]->addConnection(rooms[i + 1]);
    }

    // Add some random connections to make it more interesting
    std::uniform_int_distribution<> dis(0, rooms.size() - 1);
    int numExtraConnections = rooms.size() / 2;

    for (int i = 0; i < numExtraConnections; ++i)
    {
        int from = dis(rng);
        int to = dis(rng);

        // Avoid self-connections and duplicate connections
        if (from != to && from < to - 1)
        { // Avoid short-circuiting the path too early
            rooms[from]->addConnection(rooms[to]);
        }
    }
}

std::shared_ptr<Room> Dungeon::getStartRoom() const
{
    return startRoom;
}

std::shared_ptr<Room> Dungeon::getCurrentRoom() const
{
    return currentRoom;
}

void Dungeon::setCurrentRoom(std::shared_ptr<Room> room)
{
    currentRoom = room;
}

std::vector<std::shared_ptr<Room>> Dungeon::getRooms() const
{
    return rooms;
}
