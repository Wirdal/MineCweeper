// One large MEGAFILE
// Not messing around with headers and shit unless I need to.
#include <stdbool.h>
#include <time.h> // For counting the time it took
#include <stdlib.h>

// Might put this in a header tho

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
// Map
typedef struct
{
    // Location within the map
    int xPos, yPos;
    // true if there is a mine
    bool mine;
} Tile;

// Map
typedef struct
{
    // 2D Array of tiles. Stored in row-major order
    Tile* map;
    // Dimensions
    int height;
    int width;
    int mineNum;
    // Methods
} Map;

// Tile Methods
// Map Methods

void Map_CTOR(Map* this, int height, int width, int mineNum){
    srand(time(NULL));

    this->height = height;
    this->width = width;
    this->mineNum = mineNum;

    int tileamt = width * height;

    // Holds location of mines
    int* mineLocs = malloc(mineNum * sizeof(int));
    
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
    this->map = malloc(tileamt *sizeof(Tile));
    final:
    tempmap = malloc(tileamt * sizeof(Tile));
    for (int i = 1; i < tileamt+1; i++){ //TODO Assign the tiles their positions
        // Translate from the 1D to 2D in row major order
        this->map->xPos =
        this->map->yPos = 
        this->map++;
    }

    for (mineLocs; mineLocs != 0; mineLocs++){ //TODO assign tiles their mines, if they have them

        // From I, get the til
        // tempmap->xPos
        // tempmap->xpos
        // if (i == mineLocs)
    }
    free(mineLocs);
}

void Map_Draw(Map* this){ // TODO implement drawing

}

void selectTile(int x, int y){
    // Check if our selection was a mine
    // TODO implement failure/winning
}


int main(int argc, char *argv[]){
    // Create map from passed dimensions and minecount
    // Take input from the command line.
    Map mymap;
    Map_CTOR(&mymap, 5, 5, 3);

    while (1){
        /* gameloop */
    }
    
}