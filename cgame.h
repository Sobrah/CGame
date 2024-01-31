#include <raylib.h>

// for Random Purposes
#include <stdlib.h>
#include <time.h>


// Global Variables
#define WINDOW_WIDTH 1150
#define WINDOW_HEIGHT 750
#define FRAME_PER_SECOND 30
#define BOARD_SIZE 15
#define USERS_NUMBER 4

// Graphic Constants
#define THICK 1
#define WALL_THICK (PROPERTY_LENGTH * THICK)
#define GROUND_COLOR (BROWN)
#define BORDER_COLOR (DARKBROWN)
#define WALL_COLOR (ORANGE)

// for Ease of Access
#define MID_CELL (BOARD_SIZE / 2)
#define CELL_SIZE (WINDOW_HEIGHT / BOARD_SIZE)
#define WINDOW_DELTA ((WINDOW_WIDTH - WINDOW_HEIGHT) / 2)
#define PROPERTY_LENGTH (sizeof(UserProperty) / sizeof(int))
#define SET_LENGTH (sizeof(CharacterSet) / sizeof(CharacterType))
#define DOGS_NUMBER (sizeof(Dogs) / sizeof(UserProperty))


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
    const bool fix;
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

typedef struct Wall {
    Coordinate point;
    Direction wall;
} Wall;

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
typedef struct ScoreType {
    int round, turn, walk;
    Pature Patures[PROPERTY_LENGTH];
    User Users[USERS_NUMBER];
} ScoreType;


// Game Board
extern Cell Board[BOARD_SIZE][BOARD_SIZE];
extern Wall Walls[BOARD_SIZE];

// Character Categories Storage
extern CharacterType CharacterSet[BOARD_SIZE];
extern const Character DEFAULT_CAT;

// Score Board Information
extern ScoreType ScoreBoard;
extern const UserProperty DEFAULT_PROPERTY;

// Dogs Information
extern const UserProperty DEFAULT_DOGS[USERS_NUMBER];
extern UserProperty Dogs[USERS_NUMBER];


// Function Prototypes
void PlayScreen(void);
void DiceScreen(void);
void MenuScreen(void);

void New(void);
void Save(void);
void Load(void);

void InitBoard();
void InitScoreBoard(char *basePath, int *Order);
Coordinate RadiusRandCell(Coordinate);
Coordinate RandCell(Coordinate, Coordinate, char);
void LoadPature(char *, Pature *, int);

void CheckMove(void);
void DrawCharacters(void);
void DrawBoard(void);
void DrawScoreBoard(void);