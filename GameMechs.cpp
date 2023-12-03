#include "GameMechs.h"
#include "MacUILib.h"

//We used the left hand side method from lab manual and integrated the multi-food arraylist with GameMechs.

GameMechs::GameMechs()   //This is the constructor
{
    input=0; 
    exitFlag=false;
    loseFlag=false;
    score=0;
    boardSizeX=20;
    boardSizeY=10;

    objPos tempFood,tempFood1,tempFood2,tempFood3,tempFood4; //initialized more than one food, and their position will later be replaced by random number generations.
    tempFood.setObjPos(3, 2, 'o');
    tempFood1.setObjPos(5, 2, 'o');
    tempFood2.setObjPos(6, 6, 'o');
    tempFood3.setObjPos(7, 7, 'o');
    tempFood4.setObjPos(8, 8, 'o');
    foodBucket=new objPosArrayList();        //Allocated on heap, thus destructor will be needed.
    foodBucket->insertHead(tempFood);
    foodBucket->insertHead(tempFood1);
    foodBucket->insertHead(tempFood2);
    foodBucket->insertHead(tempFood3);
    foodBucket->insertHead(tempFood4);
}

GameMechs::GameMechs(int boardX, int boardY)   //This is the constructor with board size setting available
{
    input=0; 
    exitFlag=false;
    loseFlag=false;
    score=0;
    boardSizeX=boardX;
    boardSizeY=boardY;

    
    objPos tempFood,tempFood1,tempFood2,tempFood3,tempFood4;    //initialized more than one food, and their position will later be replaced by random number generations.
    tempFood.setObjPos(3, 2, 'o');
    tempFood1.setObjPos(5, 2, 'o');
    tempFood2.setObjPos(6, 6, 'o');
    tempFood3.setObjPos(7, 7, 'o');
    tempFood4.setObjPos(8, 8, 'o');
    foodBucket=new objPosArrayList();        //Allocated on heap, thus destructor will be needed.
    foodBucket->insertHead(tempFood);
    foodBucket->insertHead(tempFood1);
    foodBucket->insertHead(tempFood2);
    foodBucket->insertHead(tempFood3);
    foodBucket->insertHead(tempFood4);
}


GameMechs::~GameMechs()  //This is the destructor
{
    delete foodBucket;  // deletion from heap
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

void GameMechs::generateFood(objPosArrayList* blockOff)
{       
        srand(time(NULL));
        int xRange = boardSizeX;
        int yRange = boardSizeY;
        bool flagy;
        bool flagy_special=true;
        int flag;
        int count=0;
        objPos tempBody;
        objPos tempFood;
        objPosArrayList* tempFoodlist;
        

        while (count<4)       
        {    
            flagy=false;
            int myRandomX = (rand() % (xRange-2)) + 1;
            int myRandomY = (rand() % (yRange-2)) + 1;
            for (int k = 0; k < blockOff->getSize(); k++)
            {
                blockOff->getElement(tempBody,k);
                if (tempBody.x==myRandomX&&tempBody.y==myRandomY)
                {
                    flagy=true;
                    break;
                }     
            }
           
            
            for ( int j = 0; j <count; j++)
            {
                foodBucket->getElement(tempFood,j);
                if(tempFood.x==myRandomX&&tempFood.y==myRandomY)
                {
                       
                    flagy=true;
                    break;   
                }
            }
            
            if (flagy==false)
            {
                tempFood.setObjPos(myRandomX, myRandomY, 'o');
                foodBucket->insertHead(tempFood);
                foodBucket->removeTail();
                count++;
            }
            
        }

        while (flagy_special)
        {   
            flagy_special=false;
            int myRandomX = (rand() % (xRange-2)) + 1;
            int myRandomY = (rand() % (yRange-2)) + 1;
            for (int k = 0; k < blockOff->getSize(); k++)
            {
                blockOff->getElement(tempBody,k);
                if (tempBody.x==myRandomX&&tempBody.y==myRandomY)
                {
                    flagy_special=true;
                    break;
                }     
            }

            for ( int j = 0; j <count; j++)
            {
                foodBucket->getElement(tempFood,j);
                if(tempFood.x==myRandomX&&tempFood.y==myRandomY)
                {
                       
                    flagy_special=true;
                    break;   
                }
            }

            if (flagy_special==false)
            {
                tempFood.setObjPos(myRandomX, myRandomY, '$');
                foodBucket->insertHead(tempFood);
                foodBucket->removeTail();
                count++;
            }
        }
     
}


objPosArrayList* GameMechs::getFoodlistPos()
{
    return foodBucket;
}
