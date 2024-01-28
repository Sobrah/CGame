#include "screen.c"


int main(void) { 

    // Initialize Window
    SetTargetFPS(FRAME_PER_SECOND);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mr. Clobber's Backyard");
    
    // Initialize Seed 
    srand(1); // time(NULL));
    
    // Initialize
    InitBoard("Images/Board/", BOARD_SIZE);
    InitScoreBoard("Images/Score Board/");
    
    // Main Screen for Now
    // MenuScreen();
    PlayScreen();
    
    // Unload Textures from Memory
    for (int i = 0; i < SET_LENGTH; i++) {
        UnloadTexture(CharacterSet[i].pature.texture);
    }
    for (int i = 0; i < PROPERTY_LENGTH; i++) {
        UnloadTexture(ScoreBoard.Patures[i].texture);
    }

    CloseWindow();   
}