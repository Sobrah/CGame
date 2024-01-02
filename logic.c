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
#define CATEG_LENGTH (sizeof(Categories) / sizeof(CharacterType))


// Board Cell Struct
typedef struct Cell {
    int identity;
    char wall;
} Cell;

// Character Category Struct
typedef struct Character {
    int identity;
    char type;
    int x, y;
    Texture *texture;
} Character;

typedef struct CharacterType {
    char type;
    char *path;
    int n;
    Texture texture;
} CharacterType;


// Game Board
Cell Board[BOARD_SIZE][BOARD_SIZE];

// Game Character Categories
CharacterType Categories[] = {
    {'H', "Images/House.svg\0", 1},

    {'C', "Images/Yellow Cat.svg\0", 1},
    {'C', "Images/Black Cat.svg\0", 1},

    {'D', "Images/Dog.svg\0", 2},
    {'D', "Images/Poodle.svg\0", 2},

    {'P', "Images/Chocolate.svg\0", 8},

    {'F', "Images/Fish.svg\0", 8},

    {'M', "Images/Mouse.svg\0", 8},

    {'T', "Images/Trap.svg\0", 8}
};

// Game Characters
Character Characters[39];


void initBoard(void) {

    int middleCell = BOARD_SIZE / 2;


    // Initialize Seed
    srand(time(NULL));


    int id = 0;


    // House, Cat1, Cat2 Coordination Should Not Be Changed
    for (int i = 0; i < CATEG_LENGTH; i++) {
        int length = Categories[i].n;

        for (int j = 0; j < length; j++) {

            // Finding Empty Random Cell
            int x, y;
            do {
                x = rand() % BOARD_SIZE;
                y = rand() % BOARD_SIZE;
            } while(Board[x][y].identity);

            Characters[id].identity = id + 1;
            Characters[id].type = Categories[i].type;
            Characters[id].x = x;
            Characters[id].y = y;
            Characters[id].texture = &Categories[i].texture;

            Board[x][y].identity = Characters[id].identity;
            id++;
        }
    }
}