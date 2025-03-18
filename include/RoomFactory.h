#pragma once
#include "Room.h"
#include <memory>

class RoomFactory
{
public:
    static std::shared_ptr<Room> createRoom(Room::Type type, int id);
};
