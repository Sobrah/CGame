#include <raylib.h>


// Constant Global Variables
#define SCREEN_SIZE 650
#define FRAME_PER_SECOND 30
#define TABLE_SIZE 15


// Prototypes
void drawBoard(Color, Color);


int main(void) {
    // Initialize Window
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Mr. Clobber's Backyard");
    SetTargetFPS(FRAME_PER_SECOND);

    // Drawing Board Background
    drawBoard(BROWN, DARKBROWN);
    
    // Add Cat Image to the Board
    Image catImage = LoadImage("Images/Yellow Cat.png");
    ImageResize(&catImage, SCREEN_SIZE / TABLE_SIZE, SCREEN_SIZE / TABLE_SIZE);  
    Texture2D catTexture = LoadTextureFromImage(catImage);
    UnloadImage(catImage);

    while (!WindowShouldClose()) {
        BeginDrawing();
            DrawTexture(catTexture, SCREEN_SIZE / TABLE_SIZE, SCREEN_SIZE / TABLE_SIZE, WHITE);
        EndDrawing();
    }
    
    // Unload Texture From Memory
    UnloadTexture(catTexture);
    CloseWindow();   
}


void drawBoard(Color backgroundColor, Color lineColor) {
    int sideSize = SCREEN_SIZE / TABLE_SIZE;
    
    BeginDrawing();
    ClearBackground(backgroundColor);
    
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            DrawRectangleLines(sideSize * i, sideSize * j, sideSize, sideSize, lineColor);
        }
    }
    EndDrawing();
}
