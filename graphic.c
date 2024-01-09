#include "function.c"

int main(void) { 
    // Initialize Window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mr. Clobber's Backyard");
    SetTargetFPS(FRAME_PER_SECOND);
    
    // Load Category Images to the Memory
    for (int i = 0; i < SET_LENGTH; i++) {
        Image categoryImage = LoadImageSvg(
            CharacterSet[i].path,
            CELL_SIZE,
            CELL_SIZE
        );
        CharacterSet[i].texture = LoadTextureFromImage(categoryImage);
        UnloadImage(categoryImage);
    }

    // Initialize Board
    InitBoard();

    // Main Screen For Now
    PlayScreen();
    
    // Unload Textures From Memory
    for (int i = 0; i < SET_LENGTH; i++) {
        UnloadTexture(CharacterSet[i].texture);
    }

    CloseWindow();   
}