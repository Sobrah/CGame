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
    randomizeBoard();
    drawBoard(BROWN, DARKBROWN);
    
    // Load Item Images to the Memory
    Texture2D itemsTexture[CHARACTER_GROUP_LENGTH];
    for (int i = 0; i < CHARACTER_GROUP_LENGTH; i++) {
        Image itemImage = LoadImageSvg(CharactersGroup[i].address, CELL_SIZE, CELL_SIZE);
        itemsTexture[i] = LoadTextureFromImage(itemImage);
        UnloadImage(itemImage);
    }

    
    // Rendering Frames Until When It Should Be Closed
    while (!WindowShouldClose()) {
        BeginDrawing();
        for (int i = 0; i < CHARACTER_GROUP_LENGTH; i++) {
            for (int j = 0; j < CharactersGroup[i].charactersNumber;  j++) {
                DrawTexture(itemsTexture[i], CharactersGroup[i].Characters[j].x * CELL_SIZE, CharactersGroup[i].Characters[j].y * CELL_SIZE, WHITE);
            }
        }
        Rectangle rec1 = {150, 150 - 5, 100, 10};
        Rectangle rec2 = {250 - 5, 150, 10, 50};
        DrawRectangleRounded(rec1, 10, 10, DARKGRAY);
        DrawRectangleRounded(rec2, 10, 10, DARKGRAY);
        EndDrawing();
    }
    
   
    // Unload Texture From Memory
    for (int i = 0; i < CHARACTER_GROUP_LENGTH; i++) {
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