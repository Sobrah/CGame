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


// Two Main Directions
typedef enum Direction {
    NORTH,
    WEST,
    DIRECTION_COUNT // For Flexibility Purposes
} Direction;

// Board Cell Struct
typedef struct Cell {
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
    Texture texture;
} CharacterType;


// Game Board
Cell Board[BOARD_SIZE][BOARD_SIZE];

// Board Walls
Coordinate Walls[BOARD_SIZE];

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


// Find Empty Cell Base On Wall Or Primary
Coordinate RandCell(int start, char factor) {
    int x, y, value;

    do {
        x = rand() % BOARD_SIZE + start;
        y = rand() % BOARD_SIZE + start;

        switch (factor) {
            case 'P': value = Board[y][x].primary; break;
            case 'W': value = Board[y][x].wall; break;
        }
    } while(value);

    return (Coordinate){x, y};
}


void InitBoard(void) {
    
    // Initialize Seed
    srand(time(NULL));

    // Initialize Characters And Board
    for (int i = 0; i < SET_LENGTH; i++) {
        int length = CharacterSet[i].n;

        for (int j = 0; j < length; j++) {
            
            // Finding Empty Random Cell
            Coordinate point = RandCell(0, 'P');
            CharacterSet[i].Characters[j] = point;

            // Primary & Secondary Starts From One
            Board[point.y][point.x].primary = i + 1;
            Board[point.y][point.x].secondary = j + 1;
        }
    }

    // Initialize Walls
    for (int i = 0; i < BOARD_SIZE; i++) {
        
        // Zero Is Not Valid
        Coordinate point = RandCell(1, 'W');
        
        Walls[i] = point;
        Board[point.y][point.x].wall = rand() % DIRECTION_COUNT;
    }
}