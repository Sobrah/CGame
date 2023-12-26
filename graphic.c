#include <raylib.h>


// Board Related Variables
#define SCREEN_SIZE 750
#define BOARD_SIZE 15
#define CELL_SIZE (SCREEN_SIZE / BOARD_SIZE)

#define FRAME_PER_SECOND 30
#define ITEMS 10


char Names[][50] = {
    "Images/Black Cat.svg\0",
    "Images/Bush.svg\0",
    "Images/Chocolate.svg\0",
    "Images/Dog.svg\0",
    "Images/Fish.svg\0",
    "Images/House.svg\0",
    "Images/Mouse.svg\0",
    "Images/Poodle.svg\0",
    "Images/Trap.svg\0",
    "Images/Yellow Cat.svg\0"
};


// Prototypes
void drawBoard(Color, Color);


int main(void) {
    // Initialize Window
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Mr. Clobber's Backyard");
    SetTargetFPS(FRAME_PER_SECOND);

    // Drawing Board Background
    drawBoard(BROWN, DARKBROWN);
    
    // Load Item Images to the Memory
    Texture2D Items[ITEMS];
    for (int i = 0; i < ITEMS; i++) {
        Image itemImage = LoadImageSvg(Names[i], CELL_SIZE, CELL_SIZE);
        Items[i] = LoadTextureFromImage(itemImage);
        UnloadImage(itemImage);
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
            for (int i = 0; i < ITEMS; i++) {
                DrawTexture(Items[i], CELL_SIZE * i, CELL_SIZE * i, WHITE);
            }
        EndDrawing();
    }
    
    // Unload Texture From Memory
    for (int i = 0; i < ITEMS; i++) {
        UnloadTexture(Items[i]);
    }
    
    CloseWindow();   
}


void drawBoard(Color backgroundColor, Color lineColor) {
    int sideSize = CELL_SIZE;
    
    BeginDrawing();
    ClearBackground(backgroundColor);
    
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            DrawRectangleLines(sideSize * i, sideSize * j, sideSize, sideSize, lineColor);
        }
    }
    EndDrawing();
}
