#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

//bool exitFlag;
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

    myGM=new GameMechs(26,13);
    myPlayer=new Player(myGM);
    //exitFlag = false;
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
    objPos tempPos;
    myPlayer->getPlayerPos(tempPos);
    MacUILib_printf("Board Size: %d-%d\nPlayer Position <%d-%d>\nSymbol-%c\n", myGM->getBoardSizeX(),myGM->getBoardSizeY(),tempPos.x,tempPos.y,tempPos.symbol);
    MacUILib_printf("Test key pressed: %c\n",myGM->getInput());
    //MacUILib_printf("%c\n",myPlayer->getInput());
    //MacUILib_printf("x:%d-y:%d\n",tempPos.x,tempPos.y);
    //MacUILib_printf("Board Size: %d-%d\nPlayer Position <%d-%d>\nSymbol-%c\n", myGM->getBoardSizeX(),myGM->getBoardSizeY(),tempPos.x,tempPos.y,tempPos.symbol);
    int x_wrap, y_wrap;
    x_wrap=myGM->getBoardSizeX();
    y_wrap=myGM->getBoardSizeY();
    
    for (int i=0; i < y_wrap; i++)
    {
        for (int j=0; j < x_wrap; j++)
        {
            if(j == 0 || j == x_wrap-1 || i == 0 || i == y_wrap-1)
            {
                MacUILib_printf("#");
            }

            else if ((j == tempPos.x) && (i == tempPos.y))
            {
                MacUILib_printf("%c", tempPos.symbol);
            }

            else
            {
                MacUILib_printf(" ");
            }

        }
        MacUILib_printf("\n");
    }

    //     for (int i=0; i < 15; i++)
    // {
    //     for (int j=0; j < 30; j++)
    //     {
    //         if(j == 0 || j == 29 || i == 0 || i == 14)
    //         {
    //             MacUILib_printf("#");
    //         }

    //         else if ((j == tempPos.x) && (i == tempPos.y))
    //         {
    //             MacUILib_printf("%c", tempPos.symbol);
    //         }

    //         else
    //         {
    //             MacUILib_printf(" ");
    //         }

    //     }
    //     MacUILib_printf("\n");
    // }

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
}
