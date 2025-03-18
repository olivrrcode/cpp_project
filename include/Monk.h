#pragma once
#include "Entity.h"
#include <memory>

class Monk : public Entity
{
public:
    Monk(const std::string &name);
    void attack(std::shared_ptr<Entity> target) override;
    void guard();
    void meditate();
    bool upgradeHealth();
    bool upgradeAttack();
};
