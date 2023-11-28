#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"


using namespace std;

#define DELAY_CONST 100000

// bool exitFlag;
 GameMechs zGM;
 objPos myPos;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(zGM.getExitFlagStatus()==false)  
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
    zGM=GameMechs();
    myPos.setObjPos(4,4,'@');
    // MacUILib_getChar();
   
    
    //exitFlag = false;
    zGM.setExitFalse();
}

void GetInput(void)
{
   if (MacUILib_hasChar()){
        
        zGM.setInput(MacUILib_getChar());
        // zGM.input=MacUILib_getChar(); 

    }
}

void RunLogic(void)
{
    if(zGM.getInput() != 0)  // if not null character
    {
        switch(zGM.getInput())
        {                      
            case 27:  // exit
                setExitTrue();
                break;

            case 'w':
                if(mode !=down){
                    mode=up;
                }
                
                break;
            
            case 's':
                 if(mode !=up){
                    mode=down;
                }
                
                break;
            
            case 'a':
                if(mode !=right){
                    mode=left;
                }
                
                break;
            
            case 'd':
                if(mode !=left){
                    mode=right;
                }
                
                break;
            


            default:
                break;
        }

        input = 0;
    }
        switch (mode)
        {
        case up:
        obj.y--;
        break;

        case down:
        obj.y++;
        break;

        case left:
        obj.x--;
        break;

        case right:
        obj.x++;
        break;

        
        
        default:
            break;
        }

    if (obj.x>18)
    {
        obj.x=obj.x%18;
    }

    if (obj.x<1)
    {
        obj.x=obj.x+18;
    }

    if (obj.y>8)
    {
        obj.y=obj.y%8;
    }

    if (obj.y<1)
    {
        obj.y=obj.y+8;
    }
}

// void RunLogic(void)
// {
//     // [COPY AND PASTE FROM PPA2] Copy your main logic routine from PPA2 and paste them below
//      if(input != 0)  // if not null character
//     {
//         switch(input)
//         {                      
//             case 27:  // exit
//                 exitFlag = 1;
//                 break;

//             case 'w':
//                 moveFlag=1;
//                 if(mode !=down){
//                     mode=up;
//                 }
                
//                 break;
            
//             case 's':
//                 moveFlag=1;
//                  if(mode !=up){
//                     mode=down;
//                 }
                
//                 break;
            
//             case 'a':
//                 moveFlag=1;
//                 if(mode !=right){
//                     mode=left;
//                 }
                
//                 break;
            
//             case 'd':
//                 moveFlag=1;
//                 if(mode !=left){
//                     mode=right;
//                 }
                
//                 break;
//             // case 'z':
//             //     GenerateItems(Item_Bin, 5, playerobj, 20, 10, Goal_String);
                
//             //     break;
            
            
//             // Add more key processing here
//             // Add more key processing here    


//             default:
//                 break;
//         }

//         input = 0;
//     }
//         switch (mode)
//         {
//         case up:
//         playerobj->y--;
//         break;

//         case down:
//         playerobj->y++;
//         break;

//         case left:
//         playerobj->x--;
//         break;

//         case right:
//         playerobj->x++;
//         break;

        
        
//         default:
//             break;
//         }

//     if (playerobj->x>18)
//     {
//         playerobj->x=playerobj->x%18;
//     }

//     if (playerobj->x<1)
//     {
//         playerobj->x=playerobj->x+18;
//     }

//     if (playerobj->y>8)
//     {
//         playerobj->y=playerobj->y%8;
//     }

//     if (playerobj->y<1)
//     {
//         playerobj->y=playerobj->y+8;
//     }

//     if (moveFlag==1)
//     {
//         step_count++;
//     }
    
//     // [TODO]   Implement the Object Collision logic here
//     //
//     //      Simple Collision Algorithm
//     //      1. Go through all items on board and check their (x,y) against the player object x and y.
//     //      2. If a match is found, use the ASCII symbol of the collided character, and 
//     //         find all the occurrences of this ASCII symbol in the Goal String
//     //      3. For every occurrence, reveal its ASCII character at the corresponding location in the
//     //         Collected String
//     //      4. Then, determine whether the game winning condition is met.
//     int i,j;
//     for ( i = 0; i < 5; i++)
//     {
//         if (Item_Bin[i].x==playerobj->x&&Item_Bin[i].y==playerobj->y)
//         {
//             //printf("BOOOOOOOOOP");
//             for ( j = 0; j < 12; j++)
//             {
//                 if (Item_Bin[i].shape==Goal_String[j])
//                 {
//                     Mystery_String[j]=Item_Bin[i].shape;/* code */
//                 }
                
//             }
            
//             GenerateItems(Item_Bin, 5, playerobj, 20, 10, Goal_String);
//         }
        
//     }
    
//     // [TODO]   Implement Game Winning Check logic here
//     //
//     //      Game Winning Check Algorithm
//     //      1. Check if the contents of the Collected String exactly matches that of the Goal String.
//     //         YOU MUST USE YOUR OWN my_strcmp() function from Lab 3.
//     //      2. If matched, end the game.
//     //      3. Otherwise, discard the current items on the game board, and 
//     //         generate a new set of random items on the board.  Game continues.
//     if (my_strcmp(Mystery_String,Goal_String))
//     {
//         exitFlag = 1;
//         winFlag=1;
//         //printf("BOOOOOOOOOP");
//     }
    
    
    
// }
// void RunLogic(void)
// {
    
// }

void DrawScreen(void)
{

    MacUILib_clearScreen();

    for (int i=0; i < 10; i++)
    {
        for (int j=0; j < 20; j++)
        {
            if(j == 0 || j == 19 || i == 0 || i == 9)
            {
                MacUILib_printf("#");
            }

            else if ((j == myPos.x) && (i == myPos.y))
            {
                MacUILib_printf("%c", myPos.symbol);
            }

            else
            {
                MacUILib_printf(" ");
            }

        }
        MacUILib_printf("\n");
    }

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
