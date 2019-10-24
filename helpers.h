#ifndef HELPERS_H
#define HELPERS_H
#include "main.h"
#include <stdio.h>




bool mineExists(int* mineArray, int newMine, int mapSize){
    int* startingLoc = mineArray;
    for(mineArray; *mineArray != 0; mineArray++){
        if(newMine == *(mineArray)){
            mineArray = startingLoc;
            return false;
        }
    }
    *mineArray = newMine;
    // Go back to the begining
    mineArray = startingLoc;
    return true;
}
void drawBox(Tile* tile){
    // Each of these are drawing 4 characters
    if (tile->state == hidden){
        printf("   |");
    }
    else if (tile->state == clicked){
        printf(" %i |", tile->mineDistance);
    }
    else{ //Flagged
        printf(" ! |");
    }
    
}
void drawTop(){
    printf("----");
}

#endif