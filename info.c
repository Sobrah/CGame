#include <raylib.h>


//  Global Const Variables
#define WINDOW_WIDTH 1150
#define WINDOW_HEIGHT 750
#define FRAME_PER_SECOND 30
#define BOARD_SIZE 15
#define USERS_NUMBER 4


// For Ease of Access
#define MID_CELL (BOARD_SIZE / 2)
#define CELL_SIZE (WINDOW_HEIGHT / BOARD_SIZE)
#define WINDOW_DELTA ((WINDOW_WIDTH - WINDOW_HEIGHT) / 2)
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

// Conduct to a Character Struct
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
    UserProperty property;
    Conduct userCat;
    int n;
    Conduct Mice[BOARD_SIZE];
} User;

// Score Board Struct
typedef struct ScoreBoardType {
    int round, turn, walk;
    PathTexture PathTextures[PROPERTY_LENGTH];
    User Users[USERS_NUMBER];
} ScoreBoardType;


// Character Categories Storage
CharacterType CharacterSet[] = {
    
    // Cats
    {'C', {"Images/Board/Purple Cat.svg"}, 1, 
        {MID_CELL, MID_CELL, true}, true,
    },
    {'C', {"Images/Board/Blue Cat.svg"}, 1, 
        {MID_CELL, MID_CELL, true}, true,
    },
    {'C', {"Images/Board/Yellow Cat.svg"}, 1, 
        {MID_CELL, MID_CELL, true}, true,
    },
    {'C', {"Images/Board/Green Cat.svg"}, 1, 
        {MID_CELL, MID_CELL, true}, true,
    },
    
    // Dogs
    {'D', {"Images/Board/Poodle.svg"}, 1},
    {'D', {"Images/Board/Dog.svg"}, 1},
    {'D', {"Images/Board/Fox.svg"}, 1},
    {'D', {"Images/Board/Wolf.svg"}, 1},
    
    // Mice
    {'M', {"Images/Board/White Mouse.svg"}, 8},
    {'M', {"Images/Board/Blue Mouse.svg"}, 6},
    {'M', {"Images/Board/Purple Mouse.svg"}, 4},

    // House
    {'H', {"Images/Board/House.svg"}, 1, 
        {MID_CELL, MID_CELL}, true
    },

    // Traps, Fish & Chocolates
    {'T', {"Images/Board/Trap.svg"}, 8},
    {'F', {"Images/Board/Fish.svg"}, 10},
    {'P', {"Images/Board/Chocolate.svg"}, 8}
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
        {"Images/Score Board/Score.svg"},
        {"Images/Score Board/Strength.svg"},
        {"Images/Score Board/Energy.svg"}
    }
};
const UserProperty DEFAULT_USER_PROPERTY = {0, 2, 5};