#include "logic.c"

// Graphical Function Prototypes
void PlayScreen(void);
void DrawCharacters(void);
void DrawScoreBoard(int, Color);
void DrawBoard(Color, int, Color);
void DrawScoreBoardTable(int, Color);


// Play Screen
void PlayScreen(void) {
    while (!WindowShouldClose()) {
        CheckMove();
        
        BeginDrawing();
            ClearBackground(BROWN);

            DrawCharacters();
            DrawBoard(DARKBROWN, DIRECTION_COUNT, ORANGE);
            DrawScoreBoard(DIRECTION_COUNT, DARKBROWN);
        EndDrawing();
    }
}

// Draw Score Board & Related Info
void DrawScoreBoard(int thick, Color borderColor) {

    DrawScoreBoardTable(thick, borderColor);

    // Draw Round
    int fontSize = 0.6 * CELL_SIZE;
    const char *text = TextFormat("Round %02i", ScoreBoard.round);
    DrawText(
        text,
        (WINDOW_WIDTH + WINDOW_HEIGHT - MeasureText(text, fontSize)) / 2,
        (CELL_SIZE - fontSize) / 2,
        fontSize, BLACK
    );
    
    fontSize = 1.2 * CELL_SIZE;
    int y = 2 * CELL_SIZE;
    for (int i = 0; i < 2; i++) {
        int *n = &ScoreBoard.Users[i].score;
        for (int j = 0; j < SCORE_TYPE_COUNT; j++, y += 2 * CELL_SIZE, n++) {
            const char *text = TextFormat("%i ", *n);
            int textWidth = MeasureText(text, fontSize);
            int width = textWidth + CELL_SIZE;
            int textX = (WINDOW_WIDTH + WINDOW_HEIGHT - width) / 2;
            DrawText(text, textX, y, fontSize, WHITE);

            // Draw Score Board Icons
            DrawTexture(
                ScoreBoard.textures[j], textX + textWidth, y, WHITE
            );
        }
        y += CELL_SIZE;
    }
}

// Draw Score Board Table
void DrawScoreBoardTable(int thick, Color borderColor) {
    
    // White Area
    Vector2 position = {WINDOW_HEIGHT, 0};
    Vector2 size = {WINDOW_DELTA, CELL_SIZE};
    DrawRectangleV(position, size, WHITE);
    
    // Red Area
    position.y += size.y;
    size.y = (BOARD_SIZE - 1) * CELL_SIZE / 2;
    DrawRectangleV(position, size, MAROON);
    DrawLineEx(position, (Vector2){WINDOW_WIDTH, position.y}, thick, borderColor);
    
    // Blue Area
    position.y += size.y;
    DrawRectangleV(position, size, DARKBLUE);
    DrawLineEx(position, (Vector2){WINDOW_WIDTH, position.y}, thick, borderColor);

    // Score Board Outline
    DrawRectangleLinesEx(
        (Rectangle){
            WINDOW_HEIGHT - thick, 0,
            WINDOW_DELTA + thick, WINDOW_HEIGHT
        }, thick, borderColor
    );
}

// Draw Board
void DrawBoard(Color borderColor, int thick, Color wallColor) { 
    
    // Board Outline
    DrawRectangleLinesEx(
        (Rectangle){0, 0, WINDOW_HEIGHT, WINDOW_HEIGHT},
        thick, borderColor
    );

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            int x = CELL_SIZE * j;
            int y = CELL_SIZE * i;

            // Draw Cell
            DrawRectangleLines(
                x, y, CELL_SIZE, CELL_SIZE, borderColor
            );

            if (!Board[i][j].wall) continue;

            // Draw Wall
            Vector2 endPoint, startPoint = {x, y};
            endPoint = startPoint;

            switch (Board[i][j].wall) {
                case NORTH: endPoint.x += CELL_SIZE; break;
                case WEST: endPoint.y += CELL_SIZE; break;
            }

            DrawLineEx(startPoint, endPoint, thick, wallColor);
        }
    }
}

// Draw Characters
void DrawCharacters(void) {
    for (int i = 0; i < SET_LENGTH; i++) {
        for (int j = 0; j < CharacterSet[i].n; j++) {

            if (CharacterSet[i].Characters[j].inactive) continue;

            DrawTexture(
                CharacterSet[i].texture,
                CharacterSet[i].Characters[j].point.x * CELL_SIZE,
                CharacterSet[i].Characters[j].point.y * CELL_SIZE,
                WHITE
            );
        }
    }
}