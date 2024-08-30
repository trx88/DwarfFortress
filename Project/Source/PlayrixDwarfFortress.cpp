// PlayrixDwarfFortress.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.h"
#include "OutputLogger/OutputWindowLogger.h"

int main()
{
    Game game;
    game.Run();
    OutputWindowLogger::LogToOutput("Game started!");
}
