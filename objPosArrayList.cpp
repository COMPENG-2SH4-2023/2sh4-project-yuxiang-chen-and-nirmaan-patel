#include "objPosArrayList.h"


objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; // new allocated space to store list
    sizeList = 0;                      // initializing sizeList to 0
    sizeArray = ARRAY_MAX_CAP;         // array size
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;                   // de-allocation
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(sizeList == sizeArray)
    {
        // cout << "array full.." << endl;
        return;
    }

    // pushing behind elements
    for (int i = sizeList; i > 0; i--)
    {
        aList[i] = aList[i-1];
    }

    aList[0] = thisPos; // inserting element to the head

    sizeList++;         // increment list size
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(sizeList == sizeArray)
    {
        // cout << "array full.." << endl;
        return;
    }
        
    aList[sizeList++] = thisPos;
}

void objPosArrayList::removeHead()
{
    if(sizeList <= 0)
    {
        // cout << "array full.." << endl;
        return;
    }

    for (int i = 0; i < sizeList - 1; i++)
    {
        aList[i] = aList[i+1];
    }

    sizeList--;          // decrement list size
    
}

void objPosArrayList::removeTail()
{
    if(sizeList <= 0)
    {
        // cout << "array full.." << endl;
        return;
    }

    sizeList--;         // decrement list size
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    if(sizeList == 0)
    {
        // cout << "[WARNING] List is Empty, Cannot Search for Elements." << endl;
        return;
    }
    
    returnPos = aList[0];
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    if(sizeList == 0)
    {
        // cout << "[WARNING] List is Empty, Cannot Search for Elements." << endl;
        return;
    }
    
    returnPos = aList[sizeList - 1];
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if(sizeList == 0 || index < 0 || index >= sizeList)
    {
        // cout << "[WARNING] Index Out of Bound, No Element Retrieval Allowed." << endl;
        return;
    }

    returnPos = aList[index];
}
