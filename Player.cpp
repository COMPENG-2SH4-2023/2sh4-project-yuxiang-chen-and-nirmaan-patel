#include "Player.h"
#include "MacUILib.h" //Comment_for_test


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    //playerPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,mainGameMechsRef->getBoardSizeY()/2,'@');
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,
    mainGameMechsRef->getBoardSizeY()/2,'@');
    playerPosList=new objPosArrayList();
    playerPosList->insertHead(tempPos);

    //  //extra seg
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
}
// void Player::getPlayerPos(objPos &returnPos)
// {
//     returnPos.setObjPos(playerPos.x,playerPos.y,playerPos.symbol);
//     // return the reference to the playerPos arrray list
// }

void Player::updatePlayerDir()
{   
    // objPos dummy;
    // dummy=objPos(10,12,'&');
    // //====more sna
    // objPos tempPos;
    // tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,
    // mainGameMechsRef->getBoardSizeY()/2,'@');
    
    // PPA3 input processing logic
    switch(mainGameMechsRef->getInput())
        {                      
            case 27:  // exit
                mainGameMechsRef->setExitTrue();
                break;

            case 'w':
                if(myDir !=DOWN){
                    myDir=UP;
                    // MacUILib_printf("up");//Comment_for_test
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

            // case 'z':
            //     // mainGameMechsRef->generateFood(dummy);
            //     playerPosList->insertHead(tempPos);
            //     MacUILib_printf("ha");
                
            //     break;
            
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
    // objPos temp_Body;

    // for (int k = 1; k < playerPosList->getSize(); k++)
    // {   
    //     playerPosList->getElement(temp_Body,k);
    //     if (temp_Body.x==currentHead.x&&temp_Body.y==currentHead.y)
    // {   
    //     MacUILib_printf("1111111111111111111111111111111111");
    //     // mainGameMechsRef->setLoseFlag();
    //     // mainGameMechsRef->setExitFalse();
    // }
    // }
    
    

    switch (myDir)
        {
        case UP:
        currentHead.y--;
        // if (currentHead.y<=0)
        // {
        //     currentHead.y=mainGameMechsRef->getBoardSizeY()-2;
        // }
        
        break;

        case DOWN:
        currentHead.y++;
        // if (currentHead.y>=mainGameMechsRef->getBoardSizeY())
        // {
        //     currentHead.y=1;
        // }
        break;

        case LEFT:
        currentHead.x--;
        // if (currentHead.x<=0)
        // {
        //     currentHead.x=mainGameMechsRef->getBoardSizeX()-2;
        // }
        break;

        case RIGHT:
        currentHead.x++;
        // if (currentHead.x>=mainGameMechsRef->getBoardSizeX())
        // {
        //     currentHead.x=1;
        // }
        break;

        
        
        default:
            break;
        }
//wraparound here
    // playerPosList->insertHead(currentHead);
    
    // playerPosList->removeTail();

    int x_wrap, y_wrap;
    x_wrap=mainGameMechsRef->getBoardSizeX()-2;
    y_wrap=mainGameMechsRef->getBoardSizeY()-2;
    if (currentHead.x>x_wrap)//Sean: Can change later, depending on board size.--mainGameMechsRef->getBoardSizeY()-2
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

 //Player::

bool Player::checkFoodConsumption(){
    objPos temp_head;
    objPos temp_food;
    mainGameMechsRef->getFoodPos(temp_food);
    playerPosList->getHeadElement(temp_head);
    if (temp_head.x==temp_food.x&&temp_head.y==temp_food.y)
    {
        return true;
        //MacUILib_printf("=========================================");
    }
    else 
    {
        return false;
    }
    

}

void Player::increasePlayerLength(){
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);
    playerPosList->insertHead(currentHead);
}

bool Player::checkSelfCollision(){
    objPos temp_Body;
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);

    for (int k = 2; k < playerPosList->getSize(); k++)
    {   
        playerPosList->getElement(temp_Body,k);
        if (temp_Body.x==currentHead.x&&temp_Body.y==currentHead.y)
    {   
        //MacUILib_printf("1111111111111111111111111111111111");
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }
    }

}


// void GameMechs::generateFood(objPosArrayList* blockOff)
// {
//         int xRange = boardSizeX;
//         int yRange = boardSizeY;
//         int flag;
//         flag = 0;
//         int count = 0;
//         objPos tempBody;
//         while (count < 1)
//         {
//             srand(time(NULL));
//             int myRandomX = (rand() % (xRange-2)) + 1;
//             int myRandomY = (rand() % (yRange-2)) + 1;
//             for (int k = 0; k < blockOff->getSize(); k++)
//             {
//                 blockOff->getElement(tempBody,k);
//                 if (tempBody.x==myRandomX&&tempBody.y==myRandomY)
//                 {
//                     flag = 1;
//                     break;
//                 }   
//             }
//             if (flag != 1)
//             {
//                 foodPos.x = myRandomX;
//                 foodPos.y = myRandomY;
//                 count++;
//             }
//         }
        
// }