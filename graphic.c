#include <raylib.h>


// Board Related Variables
#define SCREEN_SIZE 750
#define BOARD_SIZE 15
#define CELL_SIZE (SCREEN_SIZE / BOARD_SIZE)

#define FRAME_PER_SECOND 30


// Prototypes
void drawBoard(Color, Color);


int main(void) {
    // Initialize Window
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Mr. Clobber's Backyard");
    SetTargetFPS(FRAME_PER_SECOND);

    // Drawing Board Background
    drawBoard(BROWN, DARKBROWN);
    
    // Add Cat Image to the Board
    Image houseImage = LoadImageSvg("Images/House.svg", CELL_SIZE, CELL_SIZE);
    Image catImage = LoadImageSvg("Images/Yellow Cat.svg", CELL_SIZE, CELL_SIZE);
    
    Texture2D HouseTexture = LoadTextureFromImage(houseImage);
    Texture2D catTexture = LoadTextureFromImage(catImage);

    UnloadImage(houseImage);
    UnloadImage(catImage);

    while (!WindowShouldClose()) {
        BeginDrawing();
            DrawTexture(HouseTexture, CELL_SIZE * (BOARD_SIZE / 2), CELL_SIZE * (BOARD_SIZE / 2), WHITE);
            DrawTexture(catTexture, SCREEN_SIZE / BOARD_SIZE, SCREEN_SIZE / BOARD_SIZE, WHITE);
        EndDrawing();
    }
    
    // Unload Texture From Memory
    UnloadTexture(catTexture);
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
