#pragma once
#include "Entity.h"
#include <memory>

class Monster : public Entity
{
public:
    Monster(const std::string &name, int hp, int ap);
    void attack(std::shared_ptr<Entity> target) override;
};

class Goblin : public Monster
{
public:
    Goblin();
};
