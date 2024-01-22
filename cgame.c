#include "graphic.c"


int main(void) { 
    SetTargetFPS(FRAME_PER_SECOND);

    // Initialize Window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mr. Clobber's Backyard");
    
    // Initialize Seed 
    // srand(time(NULL));
    
    // Initialization
    InitBoard(BOARD_SIZE);
    InitScoreBoard();

    // Main Screen For Now
    PlayScreen();
    
    // Unload Textures From Memory
    for (int i = 0; i < SET_LENGTH; i++) {
        UnloadTexture(CharacterSet[i].pathTexture.texture);
    }
    for (int i = 0; i < PROPERTY_LENGTH; i++) {
        UnloadTexture(ScoreBoard.PathTextures[i].texture);
    }

    CloseWindow();   
}