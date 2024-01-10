#include <raylib.h>

// For Random Functionality
#include <stdlib.h>
#include <time.h>

//  Global Const Variables
#define SCREEN_WIDTH 1050
#define SCREEN_HEIGHT 750
#define BOARD_SIZE 15
#define FRAME_PER_SECOND 60
#define USER_NUMBER 2

#define CELL_SIZE (SCREEN_HEIGHT / BOARD_SIZE)
#define SET_LENGTH (sizeof(CharacterSet) / sizeof(CharacterType))
#define MID_CELL (BOARD_SIZE / 2) 

// Two Main Directions
typedef enum Direction {
    NORTH = -1,
    WEST = +1,
    DIRECTION_COUNT // For Flexibility Purposes
} Direction;

// Board Cell Struct
typedef struct Cell {
    bool fill;
    int primary;
    int secondary;
    Direction wall;
} Cell;

// Character Category Struct
typedef struct Coordinate {
    int x, y;
} Coordinate;

typedef struct CharacterType {
    char type;
    char *path;
    int n;
    Coordinate Characters[BOARD_SIZE];
    const bool fix;
    Texture texture;
} CharacterType;

struct {
    int round;
    int turn;
    struct User {
        int score;
        int strength;
        int energy;
    } Users[USER_NUMBER];
} ScoreBoard;


// Game Board
Cell Board[BOARD_SIZE][BOARD_SIZE] = {-1};

// Board Walls
Coordinate Walls[BOARD_SIZE];

// Game Character Categories Storage
CharacterType CharacterSet[] = {
    {'H', "Images/House.svg\0", 1, 
        {MID_CELL, MID_CELL}, true
    },

    {'C', "Images/Yellow Cat.svg\0", 1, 
        {MID_CELL + 1, MID_CELL}, true
    },

    {'C', "Images/Black Cat.svg\0", 1, 
        {MID_CELL - 1, MID_CELL},true
    },
    
    {'D', "Images/Dog.svg\0", 2},
    {'D', "Images/Poodle.svg\0", 2},

    {'P', "Images/Chocolate.svg\0", 8},

    {'F', "Images/Fish.svg\0", 8},

    {'M', "Images/Mouse.svg\0", 8},

    {'T', "Images/Trap.svg\0", 8},
};