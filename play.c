#include "cgame.h"


// Play Screen
void PlayScreen(void) {
    
    while (!WindowShouldClose()) {
        CheckMove();
        
        if (IsKeyDown(KEY_SPACE)) {
            ScreenState = MENU;
            break;
        }

        BeginDrawing();
            ClearBackground(GROUND_COLOR);
            DrawScoreBoard();
            
            DrawCharacters();
            DrawBoard();
        EndDrawing();
    }
}