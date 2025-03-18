#pragma once
#include "Monk.h"
#include "Dungeon.h"
#include "Combat.h"
#include <memory>

class Game
{
private:
    std::shared_ptr<Monk> player;
    std::shared_ptr<Dungeon> dungeon;
    bool gameOver;
    bool playerWon;

public:
    Game();
    void initialize();
    void run();
    void enterRoom(std::shared_ptr<Room> room);
    void handleEmptyRoom();
    void handleMonsterRoom(std::shared_ptr<MonsterRoom> room);
    void handleUpgradeRoom(std::shared_ptr<UpgradeRoom> room);
    void handleTreasureRoom();
    void displayRoomOptions() const;
    bool isGameOver() const;
    bool hasPlayerWon() const;
};
