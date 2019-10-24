# MineCweeper
Minesweeper clone written in C.

## Compilation
Run `make` in the directory and it will spit out an executable

## How to play
Paramaters are passed via command line. After the program constructs the map, it will draw it an await input. The input comand is as follows.

`[h | f | r]<colchar +rownum>`

- (h)elp displays these options, as well as map dimensions, and mines count, and flags remaining. colchar and rownum not required
- (f)lag a tile. colchar and rownum required
- (r)eveal a tile. Revealing a mine will result in game over. colchar and rownum required

The objective of the game is to flag all mines, using the tiles revealed to gauge how many mines are adjacent. Orthoganals and diagonals are both counted.

### Author
Chase Maguire