#include <raylib.h>

// For Random Functionality
#include <stdlib.h>
#include <time.h>

//  Global Const Variables
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 750
#define BOARD_SIZE 15
#define FRAME_PER_SECOND 30
#define USER_NUMBER 2
#define SCORE_TYPE_MEMBER 3

// For Ease of Access
#define MID_CELL (BOARD_SIZE / 2)
#define CELL_SIZE (WINDOW_HEIGHT / BOARD_SIZE)
#define WINDOW_DELTA (WINDOW_WIDTH - WINDOW_HEIGHT)
#define SET_LENGTH (sizeof(CharacterSet) / sizeof(CharacterType))


// Two Main Directions
typedef enum Direction {
    NORTH = -1,
    WEST = 1,
    DIRECTION_COUNT // For Flexibility Purposes
} Direction;

// Coordinate Struct
typedef struct Coordinate {
    int x, y;
} Coordinate;

// Character Struct
typedef struct Character {
    Coordinate point;
    bool inactive;
} Character;

// Character Type Struct
typedef struct CharacterType {
    char type;
    char *path; // Local Address
    int n;
    Character Characters[BOARD_SIZE];
    const bool fix; // Fix Positions
    Texture texture;
} CharacterType;

// Board Cell Struct
typedef struct Cell {
    CharacterType *primary; // Point Character Type
    Character *secondary; // Point Character 
    Direction wall;
} Cell;

typedef struct User {
    int score;
    int strength;
    int energy;
    Character *mouse;
} User;

// Score Board Struct
typedef struct ScoreType {
    int round;
    int turn;
    User Users[USER_NUMBER];
    char *paths[SCORE_TYPE_MEMBER];
    Texture textures[SCORE_TYPE_MEMBER];
} ScoreType;


// Character Categories Storage
CharacterType CharacterSet[] = {
    {'C', "Images/Yellow Cat.svg", 1, 
        {MID_CELL + 1, MID_CELL}, true
    },
    {'C', "Images/Black Cat.svg", 1, 
        {MID_CELL - 1, MID_CELL}, true
    },
    {'H', "Images/House.svg", 1, 
        {MID_CELL, MID_CELL}, true
    },
    {'D', "Images/Dog.svg", 2},
    {'D', "Images/Poodle.svg", 2},
    {'P', "Images/Chocolate.svg", 8},
    {'F', "Images/Fish.svg", 3},
    {'M', "Images/Mouse.svg", 8},
    {'T', "Images/Trap.svg", 8},
};

// Game Board
Cell Board[BOARD_SIZE][BOARD_SIZE];

ScoreType ScoreBoard = {
    1, 0, {
        {0, 2, 5},
        {0, 2, 5}
    }, {
        "Images/Score.svg",
        "Images/Strength.svg",
        "Images/Energy.svg"
    }
};