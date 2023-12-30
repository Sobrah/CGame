#include "logic.c"


// Prototypes
void drawBoard(Color, Color);


int main(void) { 
    // Initialize Window
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Mr. Clobber's Backyard");
    SetTargetFPS(TARGET_FPS);
    
    // Load Item Images to the Memory
    for (int i = 0; i < CHARACTER_SET_LENGTH; i++) {
        Image itemImage = LoadImageSvg(CharacterSet[i].address, CELL_SIZE, CELL_SIZE);
        CharacterSet[i].image = LoadTextureFromImage(itemImage);
        UnloadImage(itemImage);
    }

    // Initialize Board
    initBoard();

    
    // Rendering Frames Until When It Should Be Closed
    while (!WindowShouldClose()) {
        BeginDrawing();
            drawBoard(BROWN, DARKBROWN);
        EndDrawing();
    }
    
   
    // Unload Texture From Memory
    for (int i = 0; i < CHARACTER_SET_LENGTH; i++) {
        UnloadTexture(CharacterSet[i].image);
    }

    CloseWindow();   
}


void drawBoard(Color backgroundColor, Color borderColor) {
    int sideSize = CELL_SIZE;
    
    ClearBackground(backgroundColor);
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            int x, y;
            x = sideSize * i;
            y = sideSize * j;
            
            DrawRectangleLines(x, y, sideSize, sideSize, borderColor);
            if (Board[i][j].kind) {
                    DrawTexture(*Board[x][y].image, x, y, WHITE);
            }
        }
    }
}