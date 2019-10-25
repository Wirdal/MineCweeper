// One large MEGAFILE
// Not messing around with headers and shit unless I need to.
#include <stdbool.h>
#include <time.h> // For counting the time it took. + Seeding
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
    printf("Mineloc %i \n", *mineLocs);
    free(mineLocs); // Get rid of dis
}
void Map_Draw(Map* this){ // TODO implement drawing
    int startingChar = 65; //ASCII A
    int startingNum  = 0;
    // Draw the Y axis legend first
    // Chess coords have it lettered from A to whatever
    // Although with large boards, we may have to do something else
    Tile ** startingPos = this->map;
    printf("    ");
    for(int y = 0; y != (this->width); y++){
        printf(" %c  ", startingChar + y);
    }
    printf("\n   "); // Newline, and indent for the tops
    // Start writing the row numbers along with tile boxes
    for(int width = 0; width != (this->width); width++){
        drawTop();
    }
    printf("-"); //Get that last lil bit
    // Draw the contents of the row
    for(int row = 0; row != (this->height); row ++){ // Looping through the rows
        printf("\n %i |", startingNum);
        for(int width = 0; width != (this->width); width++){ // Looping through tiles themselves
            drawBox((*this->map));
            this->map++;
        }
        startingNum++;
        printf("\n   "); // Indent, and draw the tops
        for(int width = 0; width != (this->width); width++){
            drawTop(); //( ͡° ͜ʖ ͡°)
        }
        printf("-"); // Once more
    }
    this->map = startingPos;
    printf("\n");
}
int Map_RowMJRfrom2D(Map* this, int x, int y){
    // matrix[ i ][ j ] = array[ y*w + x ].
    int rowMjr = y * (this->width) + x;
    return rowMjr;
}
int Map_findAdjMines(Map* this, int tilenum){
    // Needs to all be error checked
    int possible = 0;
    if((*this->map+1+tilenum)->mine){ //+1
        possible++;
    }
    if((*this->map-1+tilenum)->mine){ // -1
        possible++; 
    }
    if((*this->map-(this->width)+tilenum)->mine){ // -w
        possible++; 
    }
    if((*this->map+(this->width)+tilenum)->mine){ // +w
        possible++; 
    }
    if((*this->map+(this->width)+1+tilenum)->mine){ // +w + 1
        possible++; 
    }
    if((*this->map+(this->width)-1+tilenum)->mine){ // +w -1
        possible++; 
    }
    if((*this->map-(this->width)-1+tilenum)->mine){ // -w -1
        possible++; 
    }
    if((*this->map-(this->width)+1+tilenum)->mine){ // -w + 1
        possible++; 
    }
    return possible;
}
void Map_selectTile(Map* this, int tilenum){
    (*this->map+tilenum)->mineDistance=Map_findAdjMines(this, tilenum);
    (*this->map+tilenum)->state = clicked;
    printf("Adj mines %i\n", Map_findAdjMines(this, tilenum));
    return;
}
int main(int argc, char *argv[]){
    // 2 spaces; 1 action; 3 for height; 3 for width;
    char input[12];
    // 999 is our max
    char ** args; // Over sizing it jic
    if (argc != 4){
        printf("Please input the height, width, and amount of mines, in that order. \n ");
        return false;
    }
    // printf("Arg1 %i, arg2, %i, arg3 %i", atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    // Create map from passed dimensions and minecount
    // TODO: Take input from the command line. 
    // [1] is a space. Need to find the next space;
    printf("argc %i\n",argc);
    Map mymap;
    Map_CTOR(&mymap, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    Map_Draw(&mymap);
    while (1){
        fgets(input, 12, stdin);
        // Find the spots that are spaces and split up accordingly
        args = strSplit(input, ' ');
        // for(int i = 0; *(args +i); i++){
        // }
        int oneDPos = Map_RowMJRfrom2D(&mymap, ((**(args+1))-65), atoi(*(args+2)));
        // printf("Col: %i, Row: %i \n", ((**(args+1))-65), atoi(*(args+2))); //Test input reading
        // printf("oneDPos %i \n", oneDPos);
        Tile * tempTile = (*(mymap.map+oneDPos));
        switch (input[0]){
            case 'h':
                printf("Mines: %i\nFlags Left: %i", mymap.mineNum, mymap.minesLeft);
                printf("Valid command are: \n(h)elp\n(f)lag\n(r)eveal\nPlease give coordinates after flagging and revleaing, with colchar and rownum\n Seperate everything with a space. Cases matter");
                break;
            case 'f':
                // Tile * tempTile = (*mymap.map);
                if (tempTile->state == clicked){
                    printf("Tile already revealed\n");
                }
                else if (tempTile->state == flagged){
                    tempTile->state = hidden;
                }
                else{
                    tempTile->state = flagged;
                }
                break;
            case 'r':
                if (tempTile->mine){
                    GameOver();
                    return false;
                }
                else{
                    Map_selectTile(&mymap, oneDPos);
                }
                break;
            default:
                printf("Please give a valid command. Try inputing 'h' if you need help. Remember, that case matters!\n");
                break;
        }
        fflush(stdin);
        Map_Draw(&mymap);
        printf("Passing second draw\n");
    }
}
