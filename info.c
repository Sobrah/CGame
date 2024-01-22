#include <raylib.h>


//  Global Const Variables
#define WINDOW_WIDTH 950
#define WINDOW_HEIGHT 750
#define FRAME_PER_SECOND 30
#define BOARD_SIZE 15
#define USERS_NUMBER 4


// For Ease of Access
#define MID_CELL (BOARD_SIZE / 2)
#define CELL_SIZE (WINDOW_HEIGHT / BOARD_SIZE)
#define WINDOW_DELTA (WINDOW_WIDTH - WINDOW_HEIGHT)
#define PROPERTY_LENGTH (sizeof(UserProperty) / sizeof(int))
#define SET_LENGTH (sizeof(CharacterSet) / sizeof(CharacterType))


// Main Directions
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

// Path & Texture struct
typedef struct PathTexture {
    const char *path; // Local Address
    Texture texture;
} PathTexture;

// Character Type Struct
typedef struct CharacterType {
    const char type;
    PathTexture pathTexture;
    const int n;
    Character Characters[BOARD_SIZE];
    const bool fix; // Stable Position
} CharacterType;

// Board Cell Struct
typedef struct Cell {
    CharacterType *primary;
    Character *secondary; 
    Direction wall;
} Cell;

// User Properties Struct
typedef struct UserProperty {
    int score, strength, energy;
} UserProperty;

// User Struct
typedef struct User {
    UserProperty property;
    Cell userCat;
    int n;
    Cell rats[BOARD_SIZE];
} User;

// Score Board Struct
typedef struct ScoreType {
    int round, turn;
    PathTexture PathTextures[PROPERTY_LENGTH];
    User Users[USERS_NUMBER];
} ScoreType;


// Character Categories Storage
CharacterType CharacterSet[] = {
    
    // Cats
    {'C', {"Images/Purple Cat.svg"}, 1, 
        {MID_CELL, MID_CELL, true}, true,
    },
    {'C', {"Images/Blue Cat.svg"}, 1, 
        {MID_CELL, MID_CELL, true}, true,
    },
    {'C', {"Images/Yellow Cat.svg"}, 1, 
        {MID_CELL, MID_CELL, true}, true,
    },
    {'C', {"Images/Green Cat.svg"}, 1, 
        {MID_CELL, MID_CELL, true}, true,
    },
    
    // Dogs
    {'D', {"Images/Poodle.svg"}, 1},
    {'D', {"Images/Dog.svg"}, 1},
    {'D', {"Images/Fox.svg"}, 1},
    {'D', {"Images/Wolf.svg"}, 1},

    // House
    {'H', {"Images/House.svg"}, 1, 
        {MID_CELL, MID_CELL}, true
    },
    
    // Mice
    {'M', {"Images/White Mouse.svg"}, 8},
    {'M', {"Images/Blue Mouse.svg"}, 6},
    {'M', {"Images/Purple Mouse.svg"}, 4},

    // Traps, Fish & Chocolates
    {'T', {"Images/Trap.svg"}, 8},
    {'F', {"Images/Fish.svg"}, 10},
    {'P', {"Images/Chocolate.svg"}, 8}
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
ScoreType ScoreBoard = {
    1, 0, {
        {"Images/Score.svg"},
        {"Images/Strength.svg"},
        {"Images/Energy.svg"}
    }
};
const UserProperty DEFAULT_USER_PROPERTY = {0, 2, 5};