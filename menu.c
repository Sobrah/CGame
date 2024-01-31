#include "cgame.h"

#define LABELS_LENGTH (sizeof(MENU_LABELS) / sizeof(char *))


// Screen Labels
const char *MENU_LABELS[] ={
    "Start", "New", "Save", "Load"
};

void (*Functions[])(void) = {
    DiceScreen, New, Save, Load
};


// Menu Screen
void MenuScreen(void) {
    
    // Screen Buttons 
    Rectangle Buttons[LABELS_LENGTH], rectangle = {
        WINDOW_DELTA + CELL_SIZE,
        CELL_SIZE,
        5 * CELL_SIZE,
        5 * CELL_SIZE
    };

    // Initialize Buttons
    for (int i = 0; i < LABELS_LENGTH / 2; i++) {
        for (int j = 0; j < LABELS_LENGTH / 2; j++) {
            Buttons[2 * i + j] = rectangle;
            Buttons[2 * i + j].x += j * (rectangle.width + 3 * CELL_SIZE);
        }
        rectangle.y += rectangle.height + 3 * CELL_SIZE;
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        
            // Draw Background
            ClearBackground(GROUND_COLOR);
            DrawScoreBoard();
            DrawCharacters();
            DrawBoard();

            // Draw Buttons
            for (int i = 0; i < LABELS_LENGTH; i++) {
                DrawRectangleRec(Buttons[i], BORDER_COLOR);
            
                // Draw Text
                int textWidth = MeasureText(MENU_LABELS[i], CELL_SIZE);
                DrawText(
                    MENU_LABELS[i], 
                    Buttons[i].x + (Buttons[i].width - textWidth) / 2,
                    Buttons[i].y + (Buttons[i].height - CELL_SIZE) / 2,
                    CELL_SIZE, WALL_COLOR 
                );  
            } 
        EndDrawing();

        // Check Click
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 point = GetMousePosition();

            // Check Collision
            for (int i = 0; i < LABELS_LENGTH; i++) {
                if (CheckCollisionPointRec(point, Buttons[i])) Functions[i]();
            }
        }
    }
}