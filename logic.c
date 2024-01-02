#include <raylib.h>

// For Random Functionality
#include <stdlib.h>
#include <time.h>


//  Global Const Variables
#define SCREEN_SIZE 750
#define FRAME_PER_SECOND 60
#define BOARD_SIZE 15

#define CELL_SIZE (SCREEN_SIZE / BOARD_SIZE)
#define SET_LENGTH (sizeof(CharacterSet) / sizeof(CharacterType))


// Board Cell Struct
typedef struct Cell {
    int primary;
    int secondary;
    char wall;
} Cell;

// Character Category Struct
typedef struct Point {
    int x, y;
} Point;

typedef struct CharacterType {
    char type;
    char *path;
    int n;
    Point Characters[BOARD_SIZE];
    Texture texture;
} CharacterType;


// Game Board
Cell Board[BOARD_SIZE][BOARD_SIZE];

// Game Character Categories Storage
CharacterType CharacterSet[] = {
    {'H', "Images/House.svg\0", 1},

    {'C', "Images/Yellow Cat.svg\0", 1},
    {'C', "Images/Black Cat.svg\0", 1},

    {'D', "Images/Dog.svg\0", 2},
    {'D', "Images/Poodle.svg\0", 2},

    {'P', "Images/Chocolate.svg\0", 8},

    {'F', "Images/Fish.svg\0", 8},

    {'M', "Images/Mouse.svg\0", 8},

    {'T', "Images/Trap.svg\0", 8},
};


void InitBoard(void) {
    
    // Initialize Seed
    srand(time(NULL));

    for (int i = 0; i < SET_LENGTH; i++) {
        int length = CharacterSet[i].n;

        for (int j = 0; j < length; j++) {

            // Finding Empty Random Cell
            int x, y;
            do {
                x = rand() % BOARD_SIZE;
                y = rand() % BOARD_SIZE;
            } while(Board[y][x].primary);

            CharacterSet[i].Characters[j].x = x;
            CharacterSet[i].Characters[j].y = y;

            // Primary & Secondary Starts From One
            Board[y][x].primary = i + 1;
            Board[y][x].secondary = j + 1;
        }
    }
}