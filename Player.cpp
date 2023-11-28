#include "Player.h"
#include "MacUILib.h" //Comment_for_test


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,mainGameMechsRef->getBoardSizeY()/2,'*');
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos.setObjPos(playerPos.x,playerPos.y,playerPos.symbol);
    // return the reference to the playerPos arrray list
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
                if(myDir !=DOWN){
                    myDir=UP;
                    MacUILib_printf("up");//Comment_for_test
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
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    switch (myDir)
        {
        case UP:
        playerPos.y--;
        break;

        case DOWN:
        playerPos.y++;
        break;

        case LEFT:
        playerPos.x--;
        break;

        case RIGHT:
        playerPos.x++;
        break;

        
        
        default:
            break;
        }

    if (playerPos.x>18)//Sean: Can change later, depending on board size.
    {
        playerPos.x=playerPos.x%18;
    }

    if (playerPos.x<1)
    {
        playerPos.x=playerPos.x+18;
    }

    if (playerPos.y>8)
    {
        playerPos.y=playerPos.y%8;
    }

    if (playerPos.y<1)
    {
        playerPos.y=playerPos.y+8;
    }
}

