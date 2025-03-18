#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Monster.h"

class Room;
using RoomPtr = std::shared_ptr<Room>;

class Room
{
protected:
    int id;
    std::string description;
    std::vector<RoomPtr> connectedRooms;

public:
    enum class Type
    {
        EMPTY,
        MONSTER,
        UPGRADE,
        TREASURE
    };

    Room(int id, const std::string &desc);
    virtual ~Room() = default;

    int getId() const;
    const std::string &getDescription() const;

    void addConnection(RoomPtr room);
    const std::vector<RoomPtr> &getConnections() const;

    virtual Type getType() const = 0;
    virtual std::string enter() = 0; // Player enters room
};

class EmptyRoom : public Room
{
public:
    EmptyRoom(int id);
    Type getType() const override;
    std::string enter() override;
};

class MonsterRoom : public Room
{
private:
    std::shared_ptr<Monster> monster;
    bool defeated;

public:
    MonsterRoom(int id);
    void setMonster(std::shared_ptr<Monster> m);
    std::shared_ptr<Monster> getMonster() const;
    bool isDefeated() const;
    void setDefeated(bool value);
    Type getType() const override;
    std::string enter() override;
};

class UpgradeRoom : public Room
{
private:
    bool used;

public:
    UpgradeRoom(int id);
    bool isUsed() const;
    void setUsed(bool value);
    Type getType() const override;
    std::string enter() override;
};

class TreasureRoom : public Room
{
public:
    TreasureRoom(int id);
    Type getType() const override;
    std::string enter() override;
};
