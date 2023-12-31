#include "Player.h"
#include "MacUILib.h" 


Player::Player(GameMechs* thisGMRef)    //This is the constructor
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;   //The snake will not move at the start of game.
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,
    mainGameMechsRef->getBoardSizeY()/2,'@');               //This will initialize the player's starting position and symbol.
    playerPosList=new objPosArrayList();            //Allocated on heap, thus destructor will be needed.
    playerPosList->insertHead(tempPos);         //The initial snake is only one symbol long.

}


Player::~Player()   //This is the destructor
{
    
    delete playerPosList;   // deletion from heap
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
}

void Player::updatePlayerDir()
{   
    
    switch(mainGameMechsRef->getInput())       //The input logic transplanted from PPA, but now in OOD manner.
        {                      
            case 27:         //ESC key for easy exit
                mainGameMechsRef->setExitTrue();
                break;

            case 'w':
                if(myDir !=DOWN){
                    myDir=UP;
                    
                }
                
                break;
            
            case 's':
                 if(myDir !=UP){
                    myDir=DOWN;
                }
                
                break;
            
            case 'a':
                if(myDir !=RIGHT){
                    myDir=LEFT;
                }
                
                break;
            
            case 'd':
                if(myDir !=LEFT){
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
    
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);
    
    // applying movement of player according to input, just like in PPA
    switch (myDir)
        {
        case UP:
        currentHead.y--;
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
    if (currentHead.x>x_wrap)                       //wraparound logic transplanted from PPA
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

    playerPosList->insertHead(currentHead);          //This is the way how snake moves, insert head and remove tail.
    playerPosList->removeTail();
}

 

int Player::checkFoodConsumption(){   //This is the upgraded version of checkFoodConsumption, it is able to distinguish special food eaten from normal food eaten, and award different score&body length.
    objPos temp_head;
    objPos temp_food;
    objPosArrayList* temp_foodlist;
    temp_foodlist=mainGameMechsRef->getFoodlistPos();
    playerPosList->getHeadElement(temp_head);
    for (int i = 0; i < 1; i++)    //This checks if the special food was eaten, if yes, return 1.
    {   
        temp_foodlist->getElement(temp_food,i);
        if (temp_head.x==temp_food.x&&temp_head.y==temp_food.y)
        {
        return 1;
        }
    }

    for (int i = 1; i < 5; i++)   //This checks if the normal food was eaten, if yes, return 2.
    {   
        temp_foodlist->getElement(temp_food,i);
        if (temp_head.x==temp_food.x&&temp_head.y==temp_food.y)
        {
        return 2;
        }
    }
    return 0;

}

void Player::increasePlayerLength(){
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);
    playerPosList->insertHead(currentHead);
}

bool Player::checkSelfCollision(){  // checking for collision with snake's own body
    objPos temp_Body;
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);

    for (int k = 3; k < playerPosList->getSize(); k++)
    {   
        playerPosList->getElement(temp_Body,k);
        if (temp_Body.x==currentHead.x&&temp_Body.y==currentHead.y)//in this for loop, it will detect whether snake head touches any part of snake body.
    {   
        mainGameMechsRef->setLoseFlag();  //"You lost" signal, differentiated from game exit by ESC.
        mainGameMechsRef->setExitTrue();  //Game over signal
    }
    }

}































        
