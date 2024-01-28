#include "graphic.c"


void MenuScreen(void);
void PlayScreen(void);


// Menu Screen
void MenuScreen(void) {
    int LABELS_LENGTH, FONT_SIZE = CELL_SIZE;
    
    // Screen Labels
    const char *Labels[] ={
        "New Game",
        "Save Game",
        "Load Game"
    }; LABELS_LENGTH = sizeof(Labels) / sizeof(char *);

    // Screen Buttons 
    Rectangle Buttons[LABELS_LENGTH], rectangle = {
        (WINDOW_WIDTH - MID_CELL * CELL_SIZE) / 2,
        2 * CELL_SIZE,
        MID_CELL * CELL_SIZE,
        MID_CELL / 2 * CELL_SIZE
    };

    // Initialize Buttons
    for (int i = 0; i < LABELS_LENGTH; i++) {
        Buttons[i] = rectangle;

        rectangle.y += Buttons[i].height + CELL_SIZE;
    }

    while (!WindowShouldClose()) {

        // Check Click
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 point = GetMousePosition();

            if(CheckCollisionPointRec(point, Buttons[0])) 
                PlayScreen();
            if(CheckCollisionPointRec(point, Buttons[1]))
                SaveBoard();
            if(CheckCollisionPointRec(point, Buttons[2]))
                LoadBoard();
        }
        
        BeginDrawing();
        
            // Draw Background
            ClearBackground(GROUND_COLOR);
            DrawScoreBoard();
            
            DrawCharacters();
            DrawBoard();

            // Draw Buttons
            for(int i = 0 ; i < LABELS_LENGTH ; i++){
                DrawRectangleRec(Buttons[i], BORDER_COLOR);
            
                // Draw Text
                int textWidth = MeasureText(Labels[i], FONT_SIZE);
                DrawText(
                    Labels[i], 
                    Buttons[i].x + (Buttons[i].width - textWidth) / 2,
                    Buttons[i].y + (Buttons[i].height - FONT_SIZE) / 2,
                    FONT_SIZE, WALL_COLOR 
                );  
            } 
        EndDrawing();
    }
}

// Play Screen
void PlayScreen(void) {
    while (!WindowShouldClose()) {
        CheckMove();
        
        BeginDrawing();
            ClearBackground(GROUND_COLOR);
            DrawScoreBoard();
            
            DrawCharacters();
            DrawBoard();
        EndDrawing();
    }
}