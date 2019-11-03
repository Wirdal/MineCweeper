#ifndef HELPERS_H
#define HELPERS_H
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


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
    if (tile->state == clicked){
        printf(" %i |", tile->adjMines);
    }
    if (tile->state == flagged){ 
        printf(" ! |");
    }
    
}
void drawTop(){
    printf("----");
}

char** strSplit(char* a_str, const char a_delim){
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}
void GameOver(){
    printf("GAMEOVER\n"); // Place holder, for now.
}
bool victoryCheck(const Map* map){
    // Check if there is ANY flagged tiles that don't have mines
    int totalTiles = map->height * map->width;
    Tile ** tiles = map->map;
    for(int i = 0; i != totalTiles-1; i++){
        if((*(tiles+i))->mine && ((*(tiles+i))->state != flagged)){
            return false;
        }
    }
    // Check if all tiles with mines are flagged
    for(int i = 0; i != totalTiles-1; i++){
        if(!((*(tiles+i))->mine) && ((*(tiles+i))->state == flagged)){
            return false;
        }
    }
    return true;
}
#endif