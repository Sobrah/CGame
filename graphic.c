#include "logic.c"


// Prototypes
void drawBoard(Color, Color);


int main(void) { 
    // Initialize Window
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Mr. Clobber's Backyard");
    SetTargetFPS(TARGET_FPS);
    
    // Load Category Images to the Memory
    for (int i = 0; i < CATEG_LENGTH; i++) {
        Image categoryImage = LoadImageSvg(Categories[i].path, CELL_SIZE, CELL_SIZE);
        Categories[i].texture = LoadTextureFromImage(categoryImage);
        UnloadImage(categoryImage);
    }

    // Initialize Board
    initBoard();

    
    // Rendering Frames Until When It Should Be Closed
    while (!WindowShouldClose()) {
        BeginDrawing();
            drawBoard(BROWN, DARKBROWN);
            drawCharacters();
        EndDrawing();
    }
    
   
    // Unload Texture From Memory
    for (int i = 0; i < CATEG_LENGTH; i++) {
        UnloadTexture(Categories[i].texture);
    }

    CloseWindow();   
}


void drawBoard(Color backgroundColor, Color borderColor) {
    int sideSize = CELL_SIZE;
    
    ClearBackground(backgroundColor);
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            DrawRectangleLines(sideSize * i, sideSize * j, sideSize, sideSize, borderColor);
        }
    }
}


void drawCharacters(void) {
    for (int i = 0; i < 39; i++) {
        DrawTexture(
            *Characters[i].texture,
            Characters[i].x * CELL_SIZE,
            Characters[i].y * CELL_SIZE,
            WHITE
        );
    }
}
