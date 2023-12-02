#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"
#include <time.h>

using namespace std;

#define DELAY_CONST 100000

//bool exitFlag;
GameMechs* myGM;       // global pointer for setting up the game
Player* myPlayer;      // global pointer for setting up the player

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus()==false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM=new GameMechs(30,15);  // initialization and allocation
    myPlayer=new Player(myGM);
    
    objPosArrayList* playerBody=myPlayer->getPlayerPos();    // obtaining player position
    myGM->generateFood(playerBody);       // food generation according to player position
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();       // updating directionn of player
    myPlayer->movePlayer();            // player movement
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    objPos tempfood;
    
    myGM->getFoodPos(tempfood);      // obtaining position of food

    objPosArrayList* playerBody=myPlayer->getPlayerPos();    // obtaining position of player

    objPos tempBody;

    bool drawn;
    
    MacUILib_printf("Your Score: %d\n",myGM->getScore());
    
    int x_wrap, y_wrap;
    x_wrap=myGM->getBoardSizeX();
    y_wrap=myGM->getBoardSizeY();

    
    
    for (int i=0; i < y_wrap; i++)
    {
        for (int j=0; j < x_wrap; j++)
        {   
            drawn=false;

            for (int k = 0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(tempBody,k);

                if (tempBody.x==j&&tempBody.y==i)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn=true;
                    break;
                }
                
            }

            if(drawn) continue;

            // printing the boundary
            if(j == 0 || j == x_wrap-1 || i == 0 || i == y_wrap-1)
            {
                MacUILib_printf("#");
            }

            // printing the food
            else if ((j == tempfood.x) && (i == tempfood.y))
            {
                MacUILib_printf("%c", tempfood.symbol);
            }

            else
            {
                MacUILib_printf(" ");
            }

        
        }

        MacUILib_printf("\n");
    }
    

    if (myPlayer->checkFoodConsumption())    // checking for food consumption and implementing certain steps
    {   
        myPlayer->increasePlayerLength();
        myGM->incrementScore();
        myGM->generateFood(playerBody);
    }

    myPlayer->checkSelfCollision();
    

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST);
}


void CleanUp(void)
{
    MacUILib_clearScreen();

    if (myGM->getLoseFlagStatus())
    {

        // printing final messages to user

        MacUILib_printf("==================\n"); 
        MacUILib_printf("You Lose :(\n"); 
        MacUILib_printf("Your Score was %d\n",myGM->getScore());
        MacUILib_printf("==================\n"); 
    }
      
  
    MacUILib_uninit();
    delete myGM;         // de-allocating memory to prevent memory leakage
    delete myPlayer;
}
