#ifndef OBJPOS_H
#define OBJPOS_H

class objPos
{
    public:
        int x;
        int y;
        char symbol;

        objPos();  // default
        objPos(objPos &o); // copy constructor
        objPos(int xPos, int yPos, char sym); // additional

        void setObjPos(objPos o);        
        void setObjPos(int xPos, int yPos, char sym);

        void getObjPos(objPos &returnPos);
        char getSymbol();

        bool isPosEqual(const objPos* refPos);  // condition checker
        
        char getSymbolIfPosEqual(const objPos* refPos);
};

#endif
