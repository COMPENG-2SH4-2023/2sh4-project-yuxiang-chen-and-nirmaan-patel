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
    
    // initialization of food
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

    // initialization of food
    foodPos.setObjPos(-1, -1, 'o');
}


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

void GameMechs::clearInput()
{
    input=0;
}

void GameMechs::incrementScore()
{
    score++;
}


void GameMechs::generateFood(objPosArrayList* blockOff)  // food generation function
{       
        srand(time(NULL));           // for random no. generation
        int xRange = boardSizeX;     // dimensions of board
        int yRange = boardSizeY;
        
        bool flagy=true;    // setting boolean value

        objPos tempBody;
        while (flagy)
        {
            
            int myRandomX = (rand() % (xRange-2)) + 1;   // generating random no.'s
            int myRandomY = (rand() % (yRange-2)) + 1;

            // checking for position of snake to avoid printing food at same location

            for (int k = 0; k < blockOff->getSize(); k++)  
            {
                blockOff->getElement(tempBody,k);
                if (tempBody.x == myRandomX && tempBody.y == myRandomY)
                {
                    flagy=true;     // assigning boolean value according to conditions
                    
                    break;
                }

                flagy=false;
                 
            }
            if (flagy == false)    // assigning food position if no instersection is found
            {
                foodPos.x = myRandomX;
                foodPos.y = myRandomY;
                
            }
        }
        
}

// function to obtain position of food

void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}
