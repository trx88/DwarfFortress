#include "InputManager.h"
#include "../../Domains/World/World.h"
#include "../../Domains/Entities/Player.h"
#include "../Commands/MoveCommand.h"
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

    //SPECIFICALLY FOR WINDOWS
    // Check if a key has been pressed
    if (_kbhit())
    {
        input = _getch(); // Capture single keypress without showing it in the console

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
            case CommandKeys::GAME_QUIT:
            {
                //TODO: Handle this better
                return; // Quit game loop
            } break;
        }

        if (command)
        {
            if (command->execute(world, player))
            {
                onPlayerTurnEnded(player);
            }
            delete command;

            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            //TODO: Move this somewhere else
            // Trigger enemy movement after player action
            //executeEnemyTurn(world);
        }
    }
}
