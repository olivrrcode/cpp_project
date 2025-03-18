#include "../include/Combat.h"
#include <iostream>
#include <random>

Combat::Combat(std::shared_ptr<Entity> player, std::shared_ptr<Entity> monster)
    : player(player), monster(monster)
{

    strategies.push_back(std::make_shared<AttackStrategy>());
    strategies.push_back(std::make_shared<GuardStrategy>());
}

bool Combat::isPlayerTurn(int turn) const
{
    return turn % 2 == 0;
}

bool Combat::isOver() const
{
    return player->getHealth() <= 0 || monster->getHealth() <= 0;
}

bool Combat::playerWon() const
{
    return monster->getHealth() <= 0;
}

void Combat::playerAction(int choice)
{
    if (choice == 0)
    {
        strategies[0]->execute(player, monster);
    }
    else if (choice == 1)
    {
        strategies[1]->execute(player, monster);
    }
}

void Combat::monsterAction()
{

    strategies[0]->execute(monster, player);
}

void Combat::displayStats() const
{
    std::cout << "=== Combat Status ===" << std::endl;
    std::cout << player->getName() << ": " << player->getHealth() << " HP" << std::endl;
    std::cout << monster->getName() << ": " << monster->getHealth() << " HP" << std::endl;
    std::cout << "====================" << std::endl;
}
