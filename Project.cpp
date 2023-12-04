#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"
#include <time.h>
using namespace std;
#define DELAY_CONST 100000

//============================================================================================================================================================================
//Welcome to Chen and Patel's Snake game! 
//This game is an upgraded version from the basic Snake game, with 5 foods randomly generated on game board, and one of them is special food.
//Special food symbol:$    
//By consuming special food, snake will increase its score by 5 and length by 2.
//Hope you enjoy our effort, for any question/feedback/advice feel free to contact us: cheny19@mcmaster.ca and paten90@mcmaster.ca
//Thank you for reviewing our codes.
//============================================================================================================================================================================

GameMechs* myGM;                //global pointers
Player* myPlayer;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


int main(void)               //Main Finite State Machine
{

    Initialize();

    while(myGM->getExitFlagStatus()==false)                 //replaced the exitflag variable from PPAs
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

    myGM=new GameMechs(44,20);               //initialization of pointers on heap, will be deallocated at the end of program.
    myPlayer=new Player(myGM);               //myPlayer gets the reference from GameMechs, ie, myGM.
    
    objPosArrayList* playerBody=myPlayer->getPlayerPos(); 
    myGM->generateFood(playerBody);               //First random number generation at the start of game, so everytime someone opens the game, the food locations are different.
}

void GetInput(void)               //this part is integrated into myPlayer's functions
{
  
}

void RunLogic(void)               //controls player's moving by inputs from keyboard, and the moving logic transplanted from PPA2/PPA3.
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
    MacUILib_printf("Your Score: %d\n",myGM->getScore());               //displays current score

    int x_wrap, y_wrap;
    x_wrap=myGM->getBoardSizeX();
    y_wrap=myGM->getBoardSizeY();

    
    
    for (int i=0; i < y_wrap; i++)               //draws the screen with nested for loops
    {
        for (int j=0; j < x_wrap; j++)
        {   
            drawn=false;
            for (int k = 0; k < playerBody->getSize(); k++)                   //draws snake body from its arraylist
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
             for (int z = 0; z < 5; z++)                        //draws multiple foods from its arraylist
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
            if(j == 0 || j == x_wrap-1 || i == 0 || i == y_wrap-1)                //draws gameboard's frame and space
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
    

    switch (myPlayer->checkFoodConsumption())               //when snake eats a food, it will determine if it ate a special food or normal food
    {

    case 1:               //special food eaten, increase score by 5 and length by 2.
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

    case 2:                     //normal food eaten, increase score by 1 and length by 1.
        myPlayer->increasePlayerLength();
        myGM->incrementScore();
        myGM->generateFood(playerBody);
        break;
    
    default:
        break;
    }

    myPlayer->checkSelfCollision();                   //check if snake eats itself

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); 
}


void CleanUp(void)
{
    MacUILib_clearScreen();  
    if (myGM->getLoseFlagStatus())                   //If game ends by snake eating itself, "you lose" interface will be displayed, differed from game ending by pressing ESC.
    {
        MacUILib_printf("==================\n"); 
        MacUILib_printf("You Lose :(\n"); 
        MacUILib_printf("Your Score was %d\n",myGM->getScore());
        MacUILib_printf("==================\n"); 
    }
      
  
    MacUILib_uninit();
    delete myGM;                           //deallocation at the end to prevent memory leakage
    delete myPlayer;
}
