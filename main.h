#ifndef MAIN_H
#define MAIN_H
#include "helpers.h"


typedef enum TileState{
    hidden = 0,
    clicked = 1,
    flagged = 2,
}TileState;

typedef struct
{
    // Location within the map
    int xPos; 
	int yPos;
	// RowMjr position
	int rowMjrPos;
    // true if there is a mine
    bool mine;
    int adjMines;
    TileState state;

}Tile;

// Map
typedef struct
{
    // Array of tiles. Stored in row-major order
    Tile **map;
    // Dimensions
    int height;
    int width;
    // Mines
    int mineNum;
    int minesLeft;
    int corners[4];
} Map;


#endif