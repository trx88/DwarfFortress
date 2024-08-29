// PlayrixDwarfFortress.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Source/Game.h"
#include "Source/OutputLogger/OutputWindowLogger.h"

int main()
{
    std::cout << "Hello World!\n";
    OutputWindowLogger::LogToOutput("Game started!");
}
