#include "InputManager.h"
#include "../../Domains/World/World.h"
#include "../../Domains/Entities/Player.h"
#include "../Commands/MoveCommand.h"
#include "../Commands/UseCommand.h"
#include "../Commands/SaveCommand.h"
#include "../Commands/LoadCommand.h"
#include <conio.h> // Windows-specific
#include <chrono>
#include <thread>

InputManager::InputManager(std::shared_ptr<World> world)
{
	this->world = world;
    this->player = world->GetPlayer();
}

InputManager::~InputManager()
{
}

void InputManager::ProcessInput()
{
    char input;

    //SPECIFICALLY FOR WINDOWS OS
    //Check if a key has been pressed
    if (_kbhit())
    {
        input = _getch(); //Capture single keypress without showing it in the console

        Command* command = nullptr;

        switch (input)
        {
            case CommandKeys::MOVE_UP:
            {
                command = new MoveCommand(0, -1);
            } break;
            case CommandKeys::MOVE_DOWN:
            {
                command = new MoveCommand(0, 1);
            } break;
            case CommandKeys::MOVE_LEFT:
            {
                command = new MoveCommand(-1, 0);
            } break;
            case CommandKeys::MOVE_RIGHT:
            {
                command = new MoveCommand(1, 0);
            } break;
            case CommandKeys::INVENTORY_POTION:
            {
                command = new UseCommand(ItemType::Potion);
            } break;
            case CommandKeys::INVENTORY_WEAPON:
            {
                command = new UseCommand(ItemType::Weapon);
            } break;
            case CommandKeys::INVENTORY_ARMOR:
            {
                command = new UseCommand(ItemType::Armor);
            } break;
            case CommandKeys::GAME_SAVE:
            {
                command = new SaveCommand();
            } break;
            case CommandKeys::GAME_LOAD:
            {
                command = new LoadCommand();
            } break;
            case CommandKeys::GAME_QUIT:
            {
                exit(0);
            } break;
        }

        if (command)
        {
            if (command->Execute(world, player))
            {
                //End player's turn only when move command has been executed.
                if (dynamic_cast<MoveCommand*>(command))
                {
                    onPlayerMoveEnded(player);
                }
                if (dynamic_cast<LoadCommand*>(command))
                {
                    onReloadGame();
                }
            }
            delete command;

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}
