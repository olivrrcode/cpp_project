#pragma once
#include "Entity.h"
#include <memory>

class Monk : public Entity
{
public:
    Monk(const std::string &name);
    void attack(std::shared_ptr<Entity> target) override;
    void guard();
    void meditate();      // Restore full health
    bool upgradeHealth(); // Increase max HP by 5
    bool upgradeAttack(); // Increase attack by 2
};
