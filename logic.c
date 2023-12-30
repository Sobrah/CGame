#include <raylib.h>

// For Random Functionality
#include <stdlib.h>
#include <time.h>


// Board Related Variables
#define SCREEN_SIZE 750
#define BOARD_SIZE 15
#define TARGET_FPS 60

// Other Variables
#define CELL_SIZE (SCREEN_SIZE / BOARD_SIZE)
#define CHARACTER_SET_LENGTH (sizeof(CharacterSet) / sizeof(Character))


// Board Cell Struct
typedef struct Cell {
    char kind;
    int identifier;
    char wall;
    Texture *image;
} Cell;

// Character Category Struct
typedef struct Character {
    char kind;
    char *address;
    int number;
    Texture image;
} Character;


// Cell NULL_CELL;
Cell Board[BOARD_SIZE][BOARD_SIZE];

Character CharacterSet[] = {
    {'H', "Images/House.svg\0", 1},

    {'B', "Images/Yellow Cat.svg\0", 1},
    {'C', "Images/Black Cat.svg\0", 1},

    {'D', "Images/Dog.svg\0", 2},
    {'E', "Images/Poodle.svg\0", 2},

    {'P', "Images/Chocolate.svg\0", 8},

    {'F', "Images/Fish.svg\0", 8},

    {'M', "Images/Mouse.svg\0", 8},

    {'T', "Images/Trap.svg\0", 8}
};


void initBoard(void) {
    int middleCell = BOARD_SIZE / 2;
    
    // Fixed Position Characters
    Board[middleCell][middleCell].kind = 'H';
    Board[middleCell][middleCell].identifier = 1;
    Board[middleCell][middleCell].image = &CharacterSet[0].image;


    Board[middleCell + 1][middleCell].kind = 'B';
    Board[middleCell + 1][middleCell].identifier = 1;
    Board[middleCell + 1][middleCell].image = &CharacterSet[1].image;

    Board[middleCell - 1][middleCell].kind = 'C';
    Board[middleCell - 1][middleCell].identifier = 1;
    Board[middleCell - 1][middleCell].image = &CharacterSet[2].image;

    // Initialize Seed
    srand(time(NULL));

    // House, Cat1, Cat2 Coordination Should Not Be Changed
    for (int i = 3; i < CHARACTER_SET_LENGTH; i++) {
        int length = CharacterSet[i].number;

        for (int j = 1; j <= length; j++) {
            // Finding Empty Random Cell
            int x, y;
            do {
                x = rand() % BOARD_SIZE;
                y = rand() % BOARD_SIZE;
            } while(Board[x][y].kind);

            Board[x][y].kind = CharacterSet[i].kind;
            Board[x][y].identifier = j;
            Board[x][y].image = &CharacterSet[i].image;
        }
    }
}