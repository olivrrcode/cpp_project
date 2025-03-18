#pragma once
#include "Room.h"
#include <memory>

// Factory pattern for creating different room types
class RoomFactory
{
public:
    static std::shared_ptr<Room> createRoom(Room::Type type, int id);
};
