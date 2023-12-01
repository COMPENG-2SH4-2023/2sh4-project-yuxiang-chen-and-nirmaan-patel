#include "GameMechs.h"
#include "MacUILib.h"//new_CFO
GameMechs::GameMechs()
{
    input=0; 
    exitFlag=false;
    loseFlag=false;
    score=0;
    boardSizeX=20;
    boardSizeY=10;

    foodPos.setObjPos(-1, -1, 'o');
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input=0; 
    exitFlag=false;
    loseFlag=false;
    score=0;
    boardSizeX=boardX;
    boardSizeY=boardY;

    foodPos.setObjPos(-1, -1, 'o');
}

// do you need a destruct or?_CFO



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

int GameMechs::getScore()
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

void GameMechs::generateFood(objPosArrayList* blockOff)
{       
        srand(time(NULL));
        int xRange = boardSizeX;
        int yRange = boardSizeY;
        // int flag;
        // flag = 0;
        // int count = 0;
        bool flagy=true;
        objPos tempBody;
        while (flagy)
        {
            // srand(time(NULL));
            int myRandomX = (rand() % (xRange-2)) + 1;
            int myRandomY = (rand() % (yRange-2)) + 1;
            for (int k = 0; k < blockOff->getSize(); k++)
            {
                blockOff->getElement(tempBody,k);
                if (tempBody.x==myRandomX&&tempBody.y==myRandomY)
                {
                    flagy=true;
                    // int myRandomX = (rand() % (xRange-2)) + 1;
                    // int myRandomY = (rand() % (yRange-2)) + 1;
                    // flagy=true; 
                    break;
                } 
                flagy=false;
                 
            }
            if (flagy==false)
            {
                foodPos.x = myRandomX;
                foodPos.y = myRandomY;
                
            }
        }
        
}

void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}
