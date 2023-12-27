#include <stdlib.h>
#include <time.h>

// Board Related Variables
#define SCREEN_SIZE 750
#define BOARD_SIZE 15
#define CELL_SIZE (SCREEN_SIZE / BOARD_SIZE)

// Other Variable
#define FRAME_PER_SECOND 30
#define CHARACTER_GROUP_LENGTH 10
#define MAX_CHARACTER 10


char Board[BOARD_SIZE][BOARD_SIZE][2] = {0};


// Store Each Character Properties
typedef struct Character {
    const int kind;
    int x, y;
} Character;

// Set of Distinct Characters
typedef struct CharacterSet {
    const char identifier;
    const char *address;
    int charactersNumber;
    Character Characters[MAX_CHARACTER];
} CharacterSet;


// Store Every Character Specifications In Character Array
CharacterSet CharactersGroup[] = {
    {'H', "Images/House.svg\0", 1, {0, BOARD_SIZE / 2, BOARD_SIZE / 2}},

    {'C', "Images/Yellow Cat.svg\0", 1, {1, BOARD_SIZE / 2 + 1, BOARD_SIZE / 2}},
    {'C', "Images/Black Cat.svg\0", 1, {2, BOARD_SIZE / 2 - 1, BOARD_SIZE / 2}},

    {'D', "Images/Dog.svg\0", 2},
    {'D', "Images/Poodle.svg\0", 2},

    {'B', "Images/Bush.svg\0", 8},

    {'P', "Images/Chocolate.svg\0", 8},

    {'F', "Images/Fish.svg\0", 8},

    {'M', "Images/Mouse.svg\0", 8},

    {'T', "Images/Trap.svg\0", 8}
};

void randomizeBoard(void) {
    Board[BOARD_SIZE / 2][BOARD_SIZE / 2][0] = 'H';
    Board[BOARD_SIZE / 2 + 1][BOARD_SIZE / 2][0] = 'C';
    Board[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2][0] = 'C';

    srand(time(NULL));

    // House, Cat1, Cat2 Coordination Should Not Be Changed
    for (int i = 3; i < CHARACTER_GROUP_LENGTH; i++) {
        int length = CharactersGroup[i].charactersNumber;

        for (int j = 0; j < length; j++) {
            int x, y;
            do {
                x = rand() % BOARD_SIZE;
                y = rand() % BOARD_SIZE;
            } while(Board[x][y][0]);

            CharactersGroup[i].Characters[j].x = x;
            CharactersGroup[i].Characters[j].y = y;
            Board[x][y][0] = CharactersGroup[i].identifier;
            Board[x][y][1] = j;
        }
    }
}