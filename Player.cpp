#include "Player.h"
#include "MacUILib.h" //Comment_for_test


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,
    mainGameMechsRef->getBoardSizeY()/2,'@');
    playerPosList=new objPosArrayList();
    playerPosList->insertHead(tempPos);
    
}


Player::~Player()
{
    delete playerPosList;  // deletion of heap members
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
}


void Player::updatePlayerDir()
{   
    
    // PPA3 input processing logic
    switch(mainGameMechsRef->getInput())
    {
        case 27:  // exit
            mainGameMechsRef->setExitTrue();
            break;

        case 'w':
        if(myDir !=DOWN)
        {
            myDir=UP;
        }
            
        break;
        
        case 's':
        if(myDir !=UP)
        {
            myDir=DOWN;
        }
        
        break;
        
        case 'a':
        if(myDir !=RIGHT)
        {
            myDir=LEFT;
        }
        
        break;
        
        case 'd':
        if(myDir !=LEFT)
        {
            myDir=RIGHT;
        }
        
        break;
        
        default:
        break;

    }
        
    mainGameMechsRef->clearInput();
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);
    
    // applying movement of player according to input
    switch (myDir)
    {
        case UP:
        currentHead.y--;   // movement of head element to move snake
        break;

        case DOWN:
        currentHead.y++;
        break;

        case LEFT:
        currentHead.x--;
        break;

        case RIGHT:
        currentHead.x++;
        break;
        
        default:
            break;
    }


    int x_wrap, y_wrap;
    x_wrap=mainGameMechsRef->getBoardSizeX()-2;
    y_wrap=mainGameMechsRef->getBoardSizeY()-2;
    
    if (currentHead.x>x_wrap)
    {
        currentHead.x=currentHead.x%x_wrap;
    }

    if (currentHead.x<1)
    {
        currentHead.x=currentHead.x+x_wrap;
    }

    if (currentHead.y>y_wrap)
    {
        currentHead.y=currentHead.y%y_wrap;
    }

    if (currentHead.y<1)
    {
        currentHead.y=currentHead.y+y_wrap;
    }

    playerPosList->insertHead(currentHead);
    
    playerPosList->removeTail();
}


bool Player::checkFoodConsumption()  // checking when snake touches food
{
    objPos temp_head;
    objPos temp_food;
    mainGameMechsRef->getFoodPos(temp_food);    // obtaining food position
    playerPosList->getHeadElement(temp_head);   // obtaining player position

    // comparing positions to check if they intercepted and assigning boolean value
    if (temp_head.x==temp_food.x&&temp_head.y==temp_food.y)
    {
        return true;
    }

    else 
    {
        return false;
    }
    

}

void Player::increasePlayerLength()     // increasing length of snake when food is eaten
{
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);
    playerPosList->insertHead(currentHead);
}


bool Player::checkSelfCollision()   // checking for collision with snake's own body
{
    objPos temp_Body;

    objPos currentHead;
    playerPosList->getHeadElement(currentHead);

    for (int k = 2; k < playerPosList->getSize(); k++)
    {

        playerPosList->getElement(temp_Body,k);

        if (temp_Body.x==currentHead.x&&temp_Body.y==currentHead.y)
        {   
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
        }
    }

}
