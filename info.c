// Board Related Variables
#define SCREEN_SIZE 750
#define BOARD_SIZE 15
#define CELL_SIZE (SCREEN_SIZE / BOARD_SIZE)

// Other Variable
#define FRAME_PER_SECOND 30
#define ITEMS_NUMBER 37
#define STRING_MAX_LENGTH


// Store All Items' Properties In Item Structure
typedef struct Item {
    char name;
    int kind;
    int x, y;
    char *address;
} Item;


// Store Every Character Specifications In Character Array
Item Character[] = {
    {'H', 0, BOARD_SIZE / 2, BOARD_SIZE / 2, "Images/House.svg\0"},

    {'C', 1, 5, 7, "Images/Yellow Cat.svg\0"}, // 2 Cats
    {'C', 2, 9, 7, "Images/Black Cat.svg\0"},

    {'D', 1, 1, 2, "Images/Dog.svg\0"}, // Dogs
    {'D', 2, 1, 3, "Images/Poodle.svg\0"},

    {'P', 1, 14, 9, "Images/Chocolate.svg\0"}, // 8 Power Chocolates
    {'P', 2, 12, 14, "Images/Chocolate.svg\0"},
    {'P', 3, 7, 5, "Images/Chocolate.svg\0"},
    {'P', 4, 4, 10, "Images/Chocolate.svg\0"},
    {'P', 5, 1, 5, "Images/Chocolate.svg\0"},
    {'P', 6, 1, 12, "Images/Chocolate.svg\0"},
    {'P', 7, 0, 9, "Images/Chocolate.svg\0"},
    {'P', 8, 13, 0, "Images/Chocolate.svg\0"},

    {'F', 0, 13, 3, "Images/Fish.svg\0"}, // 10 Fish
    {'F', 0, 13, 8, "Images/Fish.svg\0"},
    {'F', 0, 9, 9, "Images/Fish.svg\0"},
    {'F', 0, 8, 3, "Images/Fish.svg\0"},
    {'F', 0, 12, 12, "Images/Fish.svg\0"},
    {'F', 0, 5, 14, "Images/Fish.svg\0"},
    {'F', 0, 4, 0, "Images/Fish.svg\0"},
    {'F', 0, 2, 13, "Images/Fish.svg\0"},
    {'F', 0, 1, 3, "Images/Fish.svg\0"},
    {'F', 0, 3, 5, "Images/Fish.svg\0"},

    {'B', 1, 1, 1, "Images/Bush.svg\0"}, // 8 Bushes
    {'B', 2, 2, 1, "Images/Bush.svg\0"},
    {'B', 3, 3, 1, "Images/Bush.svg\0"},
    {'B', 4, 3, 2, "Images/Bush.svg\0"},
    {'B', 5, 10, 10, "Images/Bush.svg\0"},
    {'B', 6, 9, 10, "Images/Bush.svg\0"},
    {'B', 7, 8, 10, "Images/Bush.svg\0"},
    {'B', 8, 8, 11, "Images/Bush.svg\0"},

    {'M', 0, 1, 7, "Images/Mouse.svg\0"}, // Mouse

    {'T', 1, 11, 4, "Images/Trap.svg\0"}, // 8 Traps
    {'T', 2, 11, 8, "Images/Trap.svg\0"},
    {'T', 3, 10, 13, "Images/Trap.svg\0"},
    {'T', 4, 8, 1, "Images/Trap.svg\0"},
    {'T', 5, 6, 3, "Images/Trap.svg\0"},
    {'T', 6, 6, 13, "Images/Trap.svg\0"},
    {'T', 7, 1, 1, "Images/Trap.svg\0"},
    {'T', 8, 0, 11, "Images/Trap.svg\0"}
};