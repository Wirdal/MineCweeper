// One large MEGAFILE
// Not messing around with headers and shit unless I need to.
#include <stdbool.h>
#include <time.h> // For counting the time it took
#include <stdlib.h>
#include <stdio.h>

#include "helpers.h"
#include "main.h"


void Map_CTOR(Map* this, int height, int width, int mineNum){
    srand(time(NULL));

    int tileamt = width * height;
    this->height = height;
    this->width = width;
    this->mineNum = mineNum;
    this->corners[0]=0;
    this->corners[1]=width-1;
    this->corners[2]= tileamt - width ;
    this->corners[3]= tileamt - 1;

    // Holds location of mines
    int* mineLocs = calloc(mineNum, sizeof(int));
    
    int tempMineLoc;

    Tile* tempmap;
    // Generate our mines
    int goodMines = 0;
    while (1){
        // Generate number
        tempMineLoc = rand() % tileamt + 1; 
        // Check if that number is in the array
        // The helper function also adds the number for us
        if (mineExists(mineLocs, tempMineLoc, tileamt)){
            goodMines++;
            // Add mine to our locations
        }
        // Can be break?
        if (goodMines == mineNum){
            goto final;
        }
    }
    // Allocate memory
    final:
    this->map = (Tile **) calloc(tileamt, sizeof(Tile*));
	Tile ** startingTile = this->map;
	int tempYPos = 0;
    for (int tempXPos = 0; tempYPos!=height ; tempXPos++){
        // Indexing the map at 0
        // Create a new tile
        Tile* newTile = calloc(1, sizeof(Tile)); // We dont free this.
        newTile->mine = false;
        newTile->xPos = tempXPos;
        newTile->yPos = tempYPos;
        newTile->state = hidden;

        *this->map = newTile;
		// this->map
        this->map++;
		if (tempXPos == width){
			tempYPos++;
			tempXPos = 0;
		}
    }
	// Go back to the starting point
	this->map = startingTile;

    for (int j = 0; j != mineNum; j++){ //TODO assign tiles their mines, if they have them
		
        int i = *mineLocs;
        this->map += i - 1;
        (*this->map)->mine = true; //What is this notation
        // Go back
        this->map -= i - 1;
        mineLocs++;
    }
    mineLocs -= mineNum;
    free(mineLocs); // Get rid of dis
}

void Map_Draw(Map* this){ // TODO implement drawing
    int startingChar = 65; //ASCII A
    int startingNum  = 0;
    // Draw the Y axis legend first
    // Chess coords have it lettered from A to whatever
    // Although with large boards, we may have to do something else
    Tile ** startingPos = this->map;
    for(int y = 0; y != (this->width); y++){
        printf(" %c ", startingChar + y);
    }
    printf("\n");
    // Start writing the row numbers along with tile boxes
    for(int row = 0; row != (this->height); row ++){ // Looping through the rows
        for(int width = 0; width != (this->width); width++){
            drawTop();
        }

        printf("\n %i ", startingNum);
        for(int width = 0; width != (this->width); width++){ // Looping through tiles themselves
            drawBox((*this->map));
            this->map++;
        }
        printf("\n");
        startingNum++;
    }
}
// void Map_selectTile(int x, int y){
//     // Check if our selection was a mine
//     // TODO implement failure/winning
//     ;
// }


int main(int argc, char *argv[]){
    // Create map from passed dimensions and minecount
    // TODO: Take input from the command line. 
    Map mymap;
    Map_CTOR(&mymap, 5, 5, 3);
    Map_Draw(&mymap);
    // while (1){
    //     /* gameloop */
    //     ;
    // }
}
