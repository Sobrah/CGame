#include "cgame.h"


// Play Screen
void PlayScreen(void) {
    int order[] = {1, 2, 3, 4};
    InitScoreBoard(order);
    
    while (!WindowShouldClose()) {
        CheckMove();
        
        BeginDrawing();
            ClearBackground(GROUND_COLOR);
            DrawScoreBoard();
            
            DrawCharacters();
            DrawBoard();
        EndDrawing();
    }

        // Unload Textures from Memory
    for (int i = 0; i < SET_LENGTH; i++) {
        UnloadTexture(CharacterSet[i].pature.texture);
    }
    for (int i = 0; i < PROPERTY_LENGTH; i++) {
        UnloadTexture(ScoreBoard.Patures[i].texture);
    }
}