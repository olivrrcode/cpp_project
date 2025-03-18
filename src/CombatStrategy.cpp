#include "../include/CombatStrategy.h"
#include "../include/Monk.h"
#include <iostream>

void AttackStrategy::execute(std::shared_ptr<Entity> actor, std::shared_ptr<Entity> target)
{
    actor->attack(target);
}

void GuardStrategy::execute(std::shared_ptr<Entity> actor, std::shared_ptr<Entity> target)
{
    // Only Monks can guard
    auto monk = std::dynamic_pointer_cast<Monk>(actor);
    if (monk)
    {
        monk->guard();
    }
    else
    {
        std::cout << actor->getName() << " doesn't know how to guard!" << std::endl;
    }
}
