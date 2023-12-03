#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"
#include <time.h>
using namespace std;
#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;

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

    myGM=new GameMechs(56,26);
    myPlayer=new Player(myGM);
    
    objPosArrayList* playerBody=myPlayer->getPlayerPos(); 
    myGM->generateFood(playerBody);
}

void GetInput(void)
{
  
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    objPosArrayList* tempFoodlist=myGM->getFoodlistPos();
    objPos temp_food;

    objPosArrayList* playerBody=myPlayer->getPlayerPos(); 
    objPos tempBody;
    bool drawn;
    bool drawn_food;
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
             for (int z = 0; z < 5; z++)
            {
                tempFoodlist->getElement(temp_food,z);
                drawn_food=false;
                if ((j == temp_food.x) && (i == temp_food.y))
            {   
                drawn_food=true;
                MacUILib_printf("%c", temp_food.symbol);
                break;
            }
                

            }
            if(drawn_food) continue;
            if(j == 0 || j == x_wrap-1 || i == 0 || i == y_wrap-1)
            {
                MacUILib_printf("#");
            }

            else
            {
                MacUILib_printf(" ");
            }

        }
        MacUILib_printf("\n");
    }
    

    switch (myPlayer->checkFoodConsumption())
    {

    case 1:
        for (int t = 0; t < 5; t++)
        {
            myGM->incrementScore();
        }
        for (int y = 0; y < 2; y++)
        {
            myPlayer->increasePlayerLength();
        }
        
        myGM->generateFood(playerBody);
        break;

    case 2:
        myPlayer->increasePlayerLength();
        myGM->incrementScore();
        myGM->generateFood(playerBody);
        break;
    
    default:
        break;
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
        MacUILib_printf("==================\n"); 
        MacUILib_printf("You Lose :(\n"); 
        MacUILib_printf("Your Score was %d\n",myGM->getScore());
        MacUILib_printf("==================\n"); 
    }
      
  
    MacUILib_uninit();
    delete myGM;
    delete myPlayer;
}
