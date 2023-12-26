// Board Related Variables
#define SCREEN_SIZE 750
#define BOARD_SIZE 15
#define CELL_SIZE (SCREEN_SIZE / BOARD_SIZE)

// Other Variable
#define FRAME_PER_SECOND 30
#define ITEMS_NUMBER 10
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
    {'C', 1, 1, 0, "Images/Yellow Cat.svg\0"},
    {'C', 2, 1, 1, "Images/Black Cat.svg\0"},
    {'D', 1, 1, 2, "Images/Dog.svg\0"},
    {'D', 2, 1, 3, "Images/Poodle.svg\0"},
    {'P', 0, 1, 4, "Images/Chocolate.svg\0"},
    {'F', 0, 1, 5, "Images/Fish.svg\0"},
    {'B', 0, 1, 6, "Images/Bush.svg\0"},
    {'M', 0, 1, 7, "Images/Mouse.svg\0"},
    {'T', 0, 1, 8, "Images/Trap.svg\0"},
};