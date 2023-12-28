// For Random Functionality
#include <stdlib.h>
#include <time.h>

// Board Related Variables
#define SCREEN_SIZE 750
#define BOARD_SIZE 15
#define CELL_SIZE (SCREEN_SIZE / BOARD_SIZE)

// Other Variable
#define FRAME_PER_SECOND 60
#define CHARACTER_SET_LENGTH (sizeof(CharacterSet) / sizeof(Character))


typedef struct Cell {
    char kind;
    int identifier;
    char wall;
} Cell;

typedef struct Character {
    char kind;
    char *address;
    int number;
} Character;

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

Cell NULL_CELL;
Cell Board[BOARD_SIZE][BOARD_SIZE];



void initBoard(void) {
    int middleCell = BOARD_SIZE / 2;
    
    // Fixed Position Characters
    Board[middleCell][middleCell].kind = 'H';
    Board[middleCell][middleCell].identifier = 1;

    Board[middleCell + 1][middleCell].kind = 'B';
    Board[middleCell + 1][middleCell].identifier = 1;

    Board[middleCell - 1][middleCell].kind = 'C';
    Board[middleCell - 1][middleCell].identifier = 2;

    srand(time(NULL));

    // House, Cat1, Cat2 Coordination Should Not Be Changed
    for (int i = 3; i < CHARACTER_SET_LENGTH; i++) {
        int length = CharacterSet[i].number;

        for (int j = 0; j < length; j++) {
            int x, y;
            do {
                x = rand() % BOARD_SIZE;
                y = rand() % BOARD_SIZE;
            } while(Board[x][y].kind);

            Board[x][y].kind = CharacterSet[i].kind;
            Board[x][y].identifier = j;
        }
    }
}