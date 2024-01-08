#include <raylib.h>

// For Random Functionality
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//  Global Const Variables
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 750
#define BOARD_SIZE 15
#define FRAME_PER_SECOND 60
#define USERS 2

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


// Game Board
Cell Board[BOARD_SIZE][BOARD_SIZE] = {-1};

// Board Walls
Coordinate Walls[BOARD_SIZE];

// Game Character Categories Storage
CharacterType CharacterSet[] = {
    {'D', "Images/Dog.svg\0", 2},
    {'D', "Images/Poodle.svg\0", 2},

    {'P', "Images/Chocolate.svg\0", 8},

    {'F', "Images/Fish.svg\0", 8},

    {'M', "Images/Mouse.svg\0", 8},

    {'T', "Images/Trap.svg\0", 8},

    {'H', "Images/House.svg\0", 1, 
        {MID_CELL, MID_CELL}, true
    },

    {'C', "Images/Black Cat.svg\0", 1, 
        {MID_CELL - 1, MID_CELL},true
    },

    {'C', "Images/Yellow Cat.svg\0", 1, 
        {MID_CELL + 1, MID_CELL}, true
    }
};


// Find Empty Cell Base On Wall Or Primary
Coordinate RandCell(int start, char factor) {
    int x, y, value;

    do {
        x = rand() % BOARD_SIZE + start;
        y = rand() % BOARD_SIZE + start;

        switch (factor) {
            case 'F': value = Board[y][x].fill; break;
            case 'W': value = Board[y][x].wall; break;
        }
    } while(value);

    return (Coordinate){x, y};
}


void InitBoard(void) {
    
    // Initialize Seed
    // srand(time(NULL));

    // House, Yellow Cat And Black Cat Should Not Be Changed
    for (int i = 0; i < SET_LENGTH; i++) {
        int length = CharacterSet[i].n;

        for (int j = 0; j < length; j++) {
            Coordinate point;
            
            if (CharacterSet[i].fix) {
                point = CharacterSet[i].Characters[j];
            } else {
                point = RandCell(0, 'F');
                CharacterSet[i].Characters[j] = point;
            } 

            Board[point.y][point.x] = (Cell){true, i, j};
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