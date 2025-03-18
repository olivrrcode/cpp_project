#include "../include/Room.h"
#include <sstream>

Room::Room(int id, const std::string &desc) : id(id), description(desc) {}

int Room::getId() const
{
    return id;
}

const std::string &Room::getDescription() const
{
    return description;
}

void Room::addConnection(RoomPtr room)
{

    bool found = false;
    for (const auto &r : connectedRooms)
    {
        if (r->getId() == room->getId())
        {
            found = true;
            break;
        }
    }

    if (!found)
    {
        connectedRooms.push_back(room);
        room->addConnection(std::shared_ptr<Room>(this, [](Room *) {}));
    }
}

const std::vector<RoomPtr> &Room::getConnections() const
{
    return connectedRooms;
}

EmptyRoom::EmptyRoom(int id) : Room(id, "An empty room. Perfect for meditation.") {}

Room::Type EmptyRoom::getType() const
{
    return Type::EMPTY;
}

std::string EmptyRoom::enter()
{
    return "You enter an empty room. It's quiet here. You can meditate to restore your health.";
}

MonsterRoom::MonsterRoom(int id)
    : Room(id, "A dark room with a monster lurking in the shadows."),
      monster(nullptr), defeated(false) {}

void MonsterRoom::setMonster(std::shared_ptr<Monster> m)
{
    monster = m;
}

std::shared_ptr<Monster> MonsterRoom::getMonster() const
{
    return monster;
}

bool MonsterRoom::isDefeated() const
{
    return defeated;
}

void MonsterRoom::setDefeated(bool value)
{
    defeated = value;
}

Room::Type MonsterRoom::getType() const
{
    return Type::MONSTER;
}

std::string MonsterRoom::enter()
{
    if (defeated)
    {
        return "You enter a room where you've already defeated a monster.";
    }
    else
    {
        std::stringstream ss;
        ss << "You enter a room with a " << monster->getName() << "! Prepare for combat!";
        return ss.str();
    }
}

UpgradeRoom::UpgradeRoom(int id)
    : Room(id, "A mystical room with an ancient shrine."), used(false) {}

bool UpgradeRoom::isUsed() const
{
    return used;
}

void UpgradeRoom::setUsed(bool value)
{
    used = value;
}

Room::Type UpgradeRoom::getType() const
{
    return Type::UPGRADE;
}

std::string UpgradeRoom::enter()
{
    if (used)
    {
        return "You enter an upgrade room. You've already used the shrine here.";
    }
    else
    {
        return "You enter a room with a mystical shrine. You can upgrade either your health or attack power.";
    }
}

TreasureRoom::TreasureRoom(int id)
    : Room(id, "A glittering treasure room filled with gold and artifacts.") {}

Room::Type TreasureRoom::getType() const
{
    return Type::TREASURE;
}

std::string TreasureRoom::enter()
{
    return "You've found the treasure room! Congratulations, you win the game!";
}
