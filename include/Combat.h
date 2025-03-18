#pragma once
#include "Entity.h"
#include "CombatStrategy.h"
#include <memory>
#include <vector>

class Combat
{
private:
    std::shared_ptr<Entity> player;
    std::shared_ptr<Entity> monster;
    std::vector<std::shared_ptr<CombatStrategy>> strategies;

public:
    Combat(std::shared_ptr<Entity> player, std::shared_ptr<Entity> monster);
    bool isPlayerTurn(int turn) const;
    bool isOver() const;
    bool playerWon() const;
    void playerAction(int choice);
    void monsterAction();
    void displayStats() const;
};
