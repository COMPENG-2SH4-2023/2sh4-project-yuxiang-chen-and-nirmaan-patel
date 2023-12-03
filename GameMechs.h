#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
 
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;
        int boardSizeX;
        int boardSizeY;
        objPosArrayList* foodBucket;

    public:
        GameMechs();
        ~GameMechs();
        GameMechs(int boardX, int boardY);
        
        bool getExitFlagStatus();
        bool getLoseFlagStatus();

        void setExitTrue();
        void setExitFalse();
        void setInput(char this_input);
        void setLoseFlag();

        char getInput();
        int getScore();

        void clearInput();

        int getBoardSizeX();
        int getBoardSizeY();

        void incrementScore();
        
        // Additional Functions for Food Generation
        void generateFood(objPosArrayList* blockOff);
        
        objPosArrayList* getFoodlistPos();
      
};

#endif
