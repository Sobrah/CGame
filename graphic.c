#include <raylib.h>

// Logic Essentials
#include "logic.c"


// Prototypes
void drawBoard(Color, Color, Texture[]);


int main(void) { 
    // Initialize Window
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Mr. Clobber's Backyard");
    SetTargetFPS(TARGET_FPS);

    // Initialize Board
    initBoard();

    // Load Item Images to the Memory
    Texture itemsTexture[CHARACTER_SET_LENGTH];
    for (int i = 0; i < CHARACTER_SET_LENGTH; i++) {
        Image itemImage = LoadImageSvg(CharacterSet[i].address, CELL_SIZE, CELL_SIZE);
        itemsTexture[i] = LoadTextureFromImage(itemImage);
        UnloadImage(itemImage);
    }

    
    // Rendering Frames Until When It Should Be Closed
    while (!WindowShouldClose()) {
        BeginDrawing();
            drawBoard(BROWN, DARKBROWN, itemsTexture);
        EndDrawing();
    }
    
   
    // Unload Texture From Memory
    for (int i = 0; i < CHARACTER_SET_LENGTH; i++) {
        UnloadTexture(itemsTexture[i]);
    }

    CloseWindow();   
}


void drawBoard(Color backgroundColor, Color borderColor, Texture itemsTexture[]) {
    int sideSize = CELL_SIZE;
    
    ClearBackground(backgroundColor);
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            int x, y, location;
            x = sideSize * i;
            y = sideSize * j;
            
            DrawRectangleLines(x, y, sideSize, sideSize, borderColor);
            if (Board[i][j].kind) {
                for(location = 0; location < CHARACTER_SET_LENGTH; location++) {
                    if (CharacterSet[location].kind == Board[i][j].kind) break;
                }
                DrawTexture(itemsTexture[location], x, y, WHITE);
            }
        }
    }
}