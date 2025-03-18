#include "../include/Monster.h"
#include <iostream>
#include <random>

Monster::Monster(const std::string &name, int hp, int ap) : Entity(name, hp, ap) {}

void Monster::attack(std::shared_ptr<Entity> target)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    if (dis(gen) == 1)
    { // 50% chance of success
        std::cout << name << " attacks and hits for " << attackPoints << " damage!" << std::endl;
        target->addHealth(-attackPoints);
    }
    else
    {
        std::cout << name << " attacks but misses!" << std::endl;
    }
}

Goblin::Goblin() : Monster("Goblin", 10, 2) {}
