#pragma once
#include <string>
#include <memory>

class Entity
{
protected:
    int healthPoints;
    int attackPoints;
    std::string name;

public:
    Entity(const std::string &name, int hp, int ap);
    virtual ~Entity() = default;

    int getHealth() const;
    void setHealth(int hp);
    void addHealth(int hp);
    int getAttackPoints() const;
    void setAttackPoints(int ap);
    void addAttackPoints(int ap);
    const std::string &getName() const;

    virtual void attack(std::shared_ptr<Entity> target) = 0;
};
