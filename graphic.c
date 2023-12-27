#include <raylib.h>

// Information Essentials
#include "info.c"


// Prototypes
void drawBoard(Color, Color);


int main(void) { 
    // Initialize Window
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Mr. Clobber's Backyard");
    SetTargetFPS(FRAME_PER_SECOND);

    // Drawing Board Background
    drawBoard(BROWN, DARKBROWN);
    
    // Load Item Images to the Memory
    Texture2D itemsTexture[ITEMS_NUMBER];
    for (int i = 0; i < ITEMS_NUMBER; i++) {
        Image itemImage = LoadImageSvg(Character[i].address, CELL_SIZE, CELL_SIZE);
        itemsTexture[i] = LoadTextureFromImage(itemImage);
        UnloadImage(itemImage);
    }

    
    // Rendering Frames Until When It Should Be Closed
    while (!WindowShouldClose()) {
        BeginDrawing();
            for (int i = 0; i < ITEMS_NUMBER; i++) {
                DrawTexture(itemsTexture[i], Character[i].x * CELL_SIZE, Character[i].y * CELL_SIZE, WHITE);
            }
        EndDrawing();
    }
    
   
    // Unload Texture From Memory
    for (int i = 0; i < ITEMS_NUMBER; i++) {
        UnloadTexture(itemsTexture[i]);
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