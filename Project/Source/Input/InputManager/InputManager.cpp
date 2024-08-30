#include "InputManager.h"
#include "../../Domains/World/World.h"
#include "../../Domains/Entities/Player.h"
#include "../Commands/MoveCommand.h"
#include <conio.h> // Windows-specific
#include <chrono>
#include <thread>

InputManager::InputManager(std::shared_ptr<World> world, std::shared_ptr<Player> player)
{
	this->world = world;
	this->player = player;
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
                command = new MoveCommand(0, -1); // Move up
            } break;
            case CommandKeys::MOVE_DOWN:
            {
                command = new MoveCommand(0, 1);  // Move down
            } break;
            case CommandKeys::MOVE_LEFT:
            {
                command = new MoveCommand(-1, 0); // Move left
            } break;
            case CommandKeys::MOVE_RIGHT:
            {
                command = new MoveCommand(1, 0);  // Move right
            } break;
            case CommandKeys::GAME_QUIT:
            {
                //TODO: Handle this better
                return; // Quit game loop
            } break;
        }

        if (command)
        {
            command->execute(world, player);
            delete command;

            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            //TODO: Move this somewhere else
            // Trigger enemy movement after player action
            //executeEnemyTurn(world);
        }
    }

    //while (true)
    //{
    //    //SPECIFICALLY FOR WINDOWS

    //    // Check if a key has been pressed
    //    if (_kbhit())
    //    {
    //        input = _getch(); // Capture single keypress without showing it in the console

    //        Command* command = nullptr;

    //        switch (input)
    //        {
    //        case CommandKeys::MOVE_UP:
    //        {
    //            command = new MoveCommand(0, -1); // Move up
    //        }break;
    //        case CommandKeys::MOVE_DOWN:
    //        {
    //            command = new MoveCommand(0, 1);  // Move down
    //        }break;
    //        case CommandKeys::MOVE_LEFT:
    //        {
    //            command = new MoveCommand(-1, 0); // Move left
    //        }break;
    //        case CommandKeys::MOVE_RIGHT:
    //        {
    //            command = new MoveCommand(1, 0);  // Move right
    //        }break;
    //        case CommandKeys::GAME_QUIT:
    //        {
    //            //TODO: Handle this better
    //            return; // Quit game loop
    //        }break;
    //        }

    //        if (command)
    //        {
    //            command->execute(world, player);
    //            delete command;

    //            //TODO: Move this somewhere else
    //            // Trigger enemy movement after player action
    //            //executeEnemyTurn(world);
    //        }
    //    }

    //    // Optionally, add a small delay to avoid CPU overuse
    //    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //}
}
