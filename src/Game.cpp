#include "../include/Game.h"
#include <iostream>
#include <limits>
#include <memory>

Game::Game() : gameOver(false), playerWon(false) {}

void Game::initialize()
{
    std::cout << "Welcome to Monk - The Dungeon RPG!" << std::endl;
    std::cout << "Enter your monk's name: ";
    std::string playerName;
    std::getline(std::cin, playerName);

    if (playerName.empty())
    {
        playerName = "Anonymous Monk";
    }

    player = std::make_shared<Monk>(playerName);
    dungeon = Dungeon::getInstance();

    dungeon->initialize(10);

    std::cout << "\nYou are " << player->getName() << ", a monk seeking ancient treasure." << std::endl;
    std::cout << "Your journey begins at the entrance of a mysterious dungeon." << std::endl;
    std::cout << "Find the treasure room to win, but beware of the monsters!" << std::endl;
    std::cout << "\n========================================\n"
              << std::endl;

    dungeon->setCurrentRoom(dungeon->getStartRoom());
    std::cout << dungeon->getCurrentRoom()->enter() << std::endl;
}

void Game::run()
{
    while (!gameOver)
    {
        auto currentRoom = dungeon->getCurrentRoom();
        displayRoomOptions();

        switch (currentRoom->getType())
        {
        case Room::Type::EMPTY:
            handleEmptyRoom();
            break;
        case Room::Type::MONSTER:
            handleMonsterRoom(std::dynamic_pointer_cast<MonsterRoom>(currentRoom));
            break;
        case Room::Type::UPGRADE:
            handleUpgradeRoom(std::dynamic_pointer_cast<UpgradeRoom>(currentRoom));
            break;
        case Room::Type::TREASURE:
            handleTreasureRoom();
            break;
        }

        if (gameOver)
            break;

        std::cout << "\nWhere would you like to go next?" << std::endl;
        auto connections = currentRoom->getConnections();
        for (size_t i = 0; i < connections.size(); ++i)
        {
            std::cout << i + 1 << ": Room " << connections[i]->getId() + 1 << std::endl;
        }

        int choice;
        while (true)
        {
            std::cout << "Choose a room (1-" << connections.size() << "): ";
            if (std::cin >> choice && choice >= 1 && choice <= static_cast<int>(connections.size()))
            {
                break;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid choice. Try again." << std::endl;
            }
        }

        enterRoom(connections[choice - 1]);
    }

    if (playerWon)
    {
        std::cout << "\n========================================" << std::endl;
        std::cout << "Congratulations! You've found the treasure and won the game!" << std::endl;
        std::cout << "========================================\n"
                  << std::endl;
    }
    else
    {
        std::cout << "\n========================================" << std::endl;
        std::cout << "Game Over! Your monk has fallen in the dungeon." << std::endl;
        std::cout << "========================================\n"
                  << std::endl;
    }
}

void Game::enterRoom(std::shared_ptr<Room> room)
{
    dungeon->setCurrentRoom(room);
    std::cout << "\n========================================" << std::endl;
    std::cout << room->enter() << std::endl;
}

void Game::handleEmptyRoom()
{
    std::cout << "Options:" << std::endl;
    std::cout << "1: Meditate (restore health)" << std::endl;
    std::cout << "2: Continue exploring" << std::endl;

    int choice;
    while (true)
    {
        std::cout << "What will you do? ";
        if (std::cin >> choice && choice >= 1 && choice <= 2)
        {
            break;
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Try again." << std::endl;
        }
    }

    if (choice == 1)
    {
        player->meditate();
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Game::handleMonsterRoom(std::shared_ptr<MonsterRoom> room)
{
    if (room->isDefeated())
    {
        std::cout << "The monster in this room has already been defeated." << std::endl;
        return;
    }

    std::cout << "A " << room->getMonster()->getName() << " attacks you!" << std::endl;

    Combat combat(player, room->getMonster());
    int turn = 0;

    while (!combat.isOver())
    {
        combat.displayStats();

        if (combat.isPlayerTurn(turn))
        {
            std::cout << "Your turn! Choose your action:" << std::endl;
            std::cout << "1: Attack" << std::endl;
            std::cout << "2: Guard" << std::endl;

            int choice;
            while (true)
            {
                std::cout << "What will you do? ";
                if (std::cin >> choice && choice >= 1 && choice <= 2)
                {
                    break;
                }
                else
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid choice. Try again." << std::endl;
                }
            }

            combat.playerAction(choice - 1);
        }
        else
        {
            combat.monsterAction();
        }

        turn++;

        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }

    if (combat.playerWon())
    {
        std::cout << "You defeated the " << room->getMonster()->getName() << "!" << std::endl;
        room->setDefeated(true);
    }
    else
    {
        std::cout << "You were defeated by the " << room->getMonster()->getName() << "!" << std::endl;
        gameOver = true;
    }
}

void Game::handleUpgradeRoom(std::shared_ptr<UpgradeRoom> room)
{
    if (room->isUsed())
    {
        std::cout << "You've already used the shrine in this room." << std::endl;
        return;
    }

    std::cout << "You find a mystical shrine. You can upgrade either your health or attack." << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "1: Upgrade Health (+5 HP)" << std::endl;
    std::cout << "2: Upgrade Attack (+2 attack points)" << std::endl;
    std::cout << "3: Skip upgrade" << std::endl;

    int choice;
    while (true)
    {
        std::cout << "What will you choose? ";
        if (std::cin >> choice && choice >= 1 && choice <= 3)
        {
            break;
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Try again." << std::endl;
        }
    }

    if (choice == 1)
    {
        player->upgradeHealth();
        room->setUsed(true);
    }
    else if (choice == 2)
    {
        player->upgradeAttack();
        room->setUsed(true);
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Game::handleTreasureRoom()
{
    std::cout << "Congratulations! You've found the legendary treasure!" << std::endl;
    gameOver = true;
    playerWon = true;
}

void Game::displayRoomOptions() const
{
    std::cout << "\nCurrent status:" << std::endl;
    std::cout << player->getName() << " - Health: " << player->getHealth() << ", Attack: " << player->getAttackPoints() << std::endl;

    auto currentRoom = dungeon->getCurrentRoom();
    std::cout << "You are in Room " << currentRoom->getId() + 1 << " (" << currentRoom->getDescription() << ")" << std::endl;
}

bool Game::isGameOver() const
{
    return gameOver;
}

bool Game::hasPlayerWon() const
{
    return playerWon;
}
