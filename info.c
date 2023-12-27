// Board Related Variables
#define SCREEN_SIZE 750
#define BOARD_SIZE 15
#define CELL_SIZE (SCREEN_SIZE / BOARD_SIZE)

// Other Variable
#define FRAME_PER_SECOND 30
#define CHARACTER_GROUP_LENGTH 10
#define STRING_MAX_LENGTH
#define MAX_CHARACTER 10


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
    
    {'C', "Images/Yellow Cat.svg\0", 1, {1, 5, 7}},
    {'C', "Images/Black Cat.svg\0", 1, {2, 9, 7}},

    {'D', "Images/Dog.svg\0", 1, {1, 1, 2}},
    {'D', "Images/Poodle.svg\0", 1, {2, 1 , 3}},

    {'P', "Images/Chocolate.svg\0", 8, {
        {1, 14, 9},
        {2, 12, 14},
        {3, 7, 5},
        {4, 4, 10},
        {5, 1, 5},
        {6, 1, 12},
        {7, 0, 9},
        {8, 13, 0}
    }},

    {'F', "Images/Fish.svg\0", 10, {
        {1, 13, 3},
        {2, 13, 8},
        {3, 9, 9},
        {4, 8, 3},
        {5, 12, 12},
        {6, 5, 14},
        {7, 4, 0},
        {8, 2, 13},
        {9, 1, 3},
        {10, 3, 5},
    }},

    {'B', "Images/Bush.svg\0", 8, {
        {1, 1, 1},
        {2, 2, 1},
        {3, 3, 1},
        {4, 3, 2},
        {5, 10, 10},
        {6, 9, 10},
        {7, 8, 10},
        {8, 8, 11}
    }},

    {'M', "Images/Mouse.svg\0", 1, {0, 1, 7}},

    {'T', "Images/Trap.svg\0", 8, {
        {1, 11, 4},
        {2, 11, 8},
        {3, 10, 13},
        {4, 8, 1},
        {5, 6, 3},
        {6, 6, 13},
        {7, 1, 1},
        {8, 0, 11},
    }}
};