#include "../include/Monk.h"
#include <iostream>
#include <random>

Monk::Monk(const std::string &name) : Entity(name, 15, 3) {}

void Monk::attack(std::shared_ptr<Entity> target)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    if (dis(gen) == 1)
    {
        std::cout << name << " attacks and hits for " << attackPoints << " damage!" << std::endl;
        target->addHealth(-attackPoints);
    }
    else
    {
        std::cout << name << " attacks but misses!" << std::endl;
    }
}

void Monk::guard()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    if (dis(gen) == 1)
    {
        addHealth(1);
        std::cout << name << " guards successfully and recovers 1 HP!" << std::endl;
    }
    else
    {
        std::cout << name << " tries to guard but fails!" << std::endl;
    }
}

void Monk::meditate()
{
    std::cout << name << " meditates and fully restores health!" << std::endl;
    setHealth(15);
}

bool Monk::upgradeHealth()
{
    addHealth(5);
    std::cout << name << " increases maximum health by 5. New health: " << getHealth() << std::endl;
    return true;
}

bool Monk::upgradeAttack()
{
    addAttackPoints(2);
    std::cout << name << " increases attack power by 2. New attack: " << getAttackPoints() << std::endl;
    return true;
}
