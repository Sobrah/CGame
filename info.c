#include <raylib.h>


// Global Variables
#define WINDOW_WIDTH 1150
#define WINDOW_HEIGHT 750
#define FRAME_PER_SECOND 30
#define BOARD_SIZE 15
#define USERS_NUMBER 4


// for Ease of Access
#define MID_CELL (BOARD_SIZE / 2)
#define CELL_SIZE (WINDOW_HEIGHT / BOARD_SIZE)
#define WINDOW_DELTA ((WINDOW_WIDTH - WINDOW_HEIGHT) / 2)
#define PROPERTY_LENGTH (sizeof(UserProperty) / sizeof(int))
#define SET_LENGTH (sizeof(CharacterSet) / sizeof(CharacterType))


// Main Directions
typedef enum Direction {
    NORTH = -1,
    WEST = 1,
    DIRECTION_COUNT // for Flexibility Purposes
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

// Path & Texture struct
typedef struct Pature {
    const char *path; // Local Address
    Texture texture;
} Pature;

// Character Type Struct
typedef struct CharacterType {
    const char type;
    Pature pature;
    const int n;
    Character Characters[BOARD_SIZE];
} CharacterType;

// Conduct to Specific Character Struct
typedef struct Conduct {
    CharacterType *primary;
    Character *secondary; 
} Conduct;

// Board Cell Struct
typedef struct Cell {
    Conduct route;
    Direction wall;
} Cell;

// User Properties Struct
typedef struct UserProperty {
    int score, strength, energy;
} UserProperty;

// User Struct
typedef struct User {
    UserProperty feature;
    Conduct cat;
    int n;
    Conduct Mice[BOARD_SIZE];
} User;

// Score Board Struct
typedef struct ScoreBoardType {
    int round, turn, walk;
    Pature Patures[PROPERTY_LENGTH];
    User Users[USERS_NUMBER];
} ScoreBoardType;


// Character Categories Storage
CharacterType CharacterSet[] = {
    
    // Cats
    {'C', {"Purple Cat.svg"}, 1, 
        {MID_CELL, MID_CELL, true}
    },
    {'C', {"Green Cat.svg"}, 1, 
        {MID_CELL, MID_CELL, true}
    },
    {'C', {"Yellow Cat.svg"}, 1, 
        {MID_CELL, MID_CELL, true}
    },
    {'C', {"Blue Cat.svg"}, 1, 
        {MID_CELL, MID_CELL, true}
    },
    
    // Dogs
    {'D', {"Poodle.svg"}, 1},
    {'D', {"Dog.svg"}, 1},
    {'D', {"Fox.svg"}, 1},
    {'D', {"Wolf.svg"}, 1},
    
    // Mice
    {'M', {"White Mouse.svg"}, 8},
    {'M', {"Blue Mouse.svg"}, 6},
    {'M', {"Purple Mouse.svg"}, 4},

    // House
    {'H', {"House.svg"}, 1, 
        {MID_CELL, MID_CELL}
    },

    // Traps, Fish & Chocolates
    {'T', {"Trap.svg"}, 8},
    {'F', {"Fish.svg"}, 10},
    {'P', {"Chocolate.svg"}, 8}
};

// Game Board
Cell Board[BOARD_SIZE][BOARD_SIZE];

// Dogs Information
UserProperty Dogs[] = {
    {5, 5, 30},
    {2, 2, 15},
    {3, 2, 20},
    {1, 1, 5}
};

// Score Board Information
ScoreBoardType ScoreBoard = {
    1, 0, 0, {
        {"Score.svg"},
        {"Strength.svg"},
        {"Energy.svg"}
    }
};
const UserProperty DEFAULT_USER_PROPERTY = {0, 2, 5};