#include <raylib.h>

// For Random Functionality
#include <stdlib.h>
#include <time.h>

//  Global Const Variables
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 750
#define BOARD_SIZE 15
#define FRAME_PER_SECOND 30
#define USER_NUMBER 2

#define CELL_SIZE (SCREEN_HEIGHT / BOARD_SIZE)
#define SET_LENGTH (sizeof(CharacterSet) / sizeof(CharacterType))
#define MID_CELL (BOARD_SIZE / 2)
#define SCREEN_DELTA (SCREEN_WIDTH - SCREEN_HEIGHT)


Font font;


// Two Main Directions
typedef enum Direction {
    NORTH = -1,
    WEST = 1,
    DIRECTION_COUNT // For Flexibility Purposes
} Direction;

// Board Cell Struct
typedef struct Cell {
    bool fill;
    int primary;
    int secondary;
    Direction wall;
} Cell;

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

#define SCORE_TYPE_LENGTH 3
typedef struct ScoreType {
    int round;
    int turn;
    struct {
        int score;
        int strength;
        int energy;
    } Users[USER_NUMBER];
    char *paths[SCORE_TYPE_LENGTH];
    Texture textures[SCORE_TYPE_LENGTH];
} ScoreType;


// Game Board
Cell Board[BOARD_SIZE][BOARD_SIZE];

// Game Character Categories Storage
CharacterType CharacterSet[] = {
    {'C', "Images/Yellow Cat.svg", 1, 
        {MID_CELL + 1, MID_CELL}, true
    },
    {'C', "Images/Black Cat.svg", 1, 
        {MID_CELL - 1, MID_CELL},true
    },
    {'H', "Images/House.svg", 1, 
        {MID_CELL, MID_CELL}, true
    },
    {'D', "Images/Dog.svg", 2},
    {'D', "Images/Poodle.svg", 2},
    {'P', "Images/Chocolate.svg", 8},
    {'F', "Images/Fish.svg", 8},
    {'M', "Images/Mouse.svg", 8},
    {'T', "Images/Trap.svg", 8},
};

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