#pragma once
#include <memory>

class Entity;

class CombatStrategy
{
public:
    virtual ~CombatStrategy() = default;
    virtual void execute(std::shared_ptr<Entity> actor, std::shared_ptr<Entity> target) = 0;
};

class AttackStrategy : public CombatStrategy
{
public:
    void execute(std::shared_ptr<Entity> actor, std::shared_ptr<Entity> target) override;
};

class GuardStrategy : public CombatStrategy
{
public:
    void execute(std::shared_ptr<Entity> actor, std::shared_ptr<Entity> target) override;
};
