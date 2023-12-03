#ifndef PLAYER_H
#define PLAYER_H
#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  
        Player(GameMechs* thisGMRef);
        ~Player();
        objPosArrayList* getPlayerPos(); 
        void updatePlayerDir();
        void movePlayer();
        int checkFoodConsumption();
        void increasePlayerLength();
        bool checkSelfCollision();

    private:       
        objPosArrayList *playerPosList;
        enum Dir myDir;
        GameMechs* mainGameMechsRef;
};

#endif