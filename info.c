#include <raylib.h>


//  Global Const Variables
#define WINDOW_WIDTH 950
#define WINDOW_HEIGHT 750
#define FRAME_PER_SECOND 30
#define BOARD_SIZE 15
#define USERS_NUMBER 4
#define SCORE_TYPE_COUNT 3


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
    const bool fix; // Fix Position at Start
    Texture texture;
    int identity;
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
    Cell cat;
    int counter;
    Cell mice[BOARD_SIZE];
} User;

// Score Board Struct
typedef struct ScoreType {
    int round;
    int turn;
    User Users[USERS_NUMBER];
    char *paths[SCORE_TYPE_COUNT];
    Texture textures[SCORE_TYPE_COUNT];
} ScoreType;

// Temporary
typedef struct Dog {
    int strength, energy, speed;
} Dog; 
Dog Dogs[] = {
    {5, 30, 5},
    {2, 15, 2},
    {2, 20, 3},
    {1, 5, 1}
};

// Character Categories Storage
CharacterType CharacterSet[] = {
    {'C', "Images/Purple Cat.svg", 1, 
        {MID_CELL, MID_CELL, true}, true,
    },
    {'C', "Images/Blue Cat.svg", 1, 
        {MID_CELL, MID_CELL, true}, true,
    },
    {'C', "Images/Yellow Cat.svg", 1, 
        {MID_CELL, MID_CELL, true}, true,
    },
    {'C', "Images/Green Cat.svg", 1, 
        {MID_CELL, MID_CELL, true}, true,
    },

    {'H', "Images/House.svg", 1, 
        {MID_CELL, MID_CELL}, true
    },
    
    {'D', "Images/Poodle.svg", 1, .identity = 0},
    {'D', "Images/Dog.svg", 1, .identity = 1},
    {'D', "Images/Fox.svg", 1, .identity = 2},
    {'D', "Images/Wolf.svg", 1, .identity = 3},
    
    {'M', "Images/White Mouse.svg", 8},
    {'M', "Images/Blue Mouse.svg", 6},
    {'M', "Images/Purple Mouse.svg", 4},

    {'T', "Images/Trap.svg", 8},
    {'P', "Images/Chocolate.svg", 8},
    {'F', "Images/Fish.svg", 10}
};

// Game Board
Cell Board[BOARD_SIZE][BOARD_SIZE];

User DEFAULT_USER = {0, 2, 5};
ScoreType ScoreBoard = {
    1, 0, 
    .paths = {
        "Images/Score.svg",
        "Images/Strength.svg",
        "Images/Energy.svg"
    }
};