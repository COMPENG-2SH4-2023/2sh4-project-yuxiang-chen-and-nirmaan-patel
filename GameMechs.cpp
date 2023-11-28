#include "GameMechs.h"
#include "MacUILib.h"//new_CFO
GameMechs::GameMechs()
{
    input=0; 
    exitFlag=false;
    loseFlag=false;
    score=0;
    boardSizeX=30;
    boardSizeY=15;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input=0; 
    exitFlag=false;
    loseFlag=false;
    score=0;
    boardSizeX=boardX;
    boardSizeY=boardY;
}

// do you need a destructor?_CFO



bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

char GameMechs::getInput()
{
    if (MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }
    
    return input;
}

char GameMechs::getScore()
{
    return score;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag=true;
}

void GameMechs::setExitFalse()
{
    exitFlag=false;
}

void GameMechs::setLoseFlag()
{
    loseFlag=true;
}

void GameMechs::setInput(char this_input)
{
    input=this_input;
}

void GameMechs::clearInput()//_CFO
{
    input=0;
}

void GameMechs::incrementScore()
{
    score++;
}

