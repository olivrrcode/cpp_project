#include "../include/RoomFactory.h"
#include "../include/Monster.h"

std::shared_ptr<Room> RoomFactory::createRoom(Room::Type type, int id)
{
    switch (type)
    {
    case Room::Type::EMPTY:
        return std::make_shared<EmptyRoom>(id);

    case Room::Type::MONSTER:
    {
        auto room = std::make_shared<MonsterRoom>(id);
        room->setMonster(std::make_shared<Goblin>());
        return room;
    }

    case Room::Type::UPGRADE:
        return std::make_shared<UpgradeRoom>(id);

    case Room::Type::TREASURE:
        return std::make_shared<TreasureRoom>(id);

    default:
        return nullptr;
    }
}
