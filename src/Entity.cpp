#include "../include/Entity.h"

Entity::Entity(const std::string &name, int hp, int ap)
    : name(name), healthPoints(hp), attackPoints(ap) {}

int Entity::getHealth() const
{
    return healthPoints;
}

void Entity::setHealth(int hp)
{
    healthPoints = hp;
}

void Entity::addHealth(int hp)
{
    healthPoints += hp;
}

int Entity::getAttackPoints() const
{
    return attackPoints;
}

void Entity::setAttackPoints(int ap)
{
    attackPoints = ap;
}

void Entity::addAttackPoints(int ap)
{
    attackPoints += ap;
}

const std::string &Entity::getName() const
{
    return name;
}
