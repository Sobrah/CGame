#include "logic.c"

void PlayScreen(void);
void CheckMove(void);
void DrawBoard(Color, Color);
void DrawCharacters(void);
void DrawWalls(int, Color);

// Play Screen Function
void PlayScreen(void) {
    while (!WindowShouldClose()) {
        CheckMove();
        
        BeginDrawing();
            DrawBoard(BROWN, DARKBROWN);
            DrawCharacters();
            DrawWalls(DIRECTION_COUNT, ORANGE);
            DrawText("Turn: ", SCREEN_HEIGHT, SCREEN_HEIGHT / 2, 20, WHITE);
        EndDrawing();
    }
}


void CheckMove(void) {
    switch (GetKeyPressed()) {
        case KEY_UP:
            CharacterSet[8].Characters[0].y -= 1;
            break;
        case KEY_LEFT:
            CharacterSet[8].Characters[0].x -= 1;
            break;
        case KEY_DOWN:
            CharacterSet[8].Characters[0].y += 1;
            break;
        case KEY_RIGHT:
            CharacterSet[8].Characters[0].x += 1;
            break;
    }
}


void DrawBoard(Color bgColor, Color borderColor) {
    ClearBackground(bgColor);
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            DrawRectangleLines(
                CELL_SIZE * i,
                CELL_SIZE * j,
                CELL_SIZE, CELL_SIZE, 
                borderColor
            );
        }
    }
}


void DrawCharacters(void) {
    for (int i = 0; i < SET_LENGTH; i++) {
        for (int j = 0; j < CharacterSet[i].n; j++) {
            DrawTexture(
                CharacterSet[i].texture,
                CharacterSet[i].Characters[j].x * CELL_SIZE,
                CharacterSet[i].Characters[j].y * CELL_SIZE,
                WHITE
            );
        }
    }
}


void DrawWalls(int thick, Color bgColor) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        Vector2 endPoint, startPoint = {
            CELL_SIZE * Walls[i].x,
            CELL_SIZE * Walls[i].y
        };
        endPoint = startPoint;

        switch (Board[Walls[i].y][Walls[i].x].wall) {
            case NORTH: endPoint.x += CELL_SIZE; break;
            case WEST: endPoint.y += CELL_SIZE; break;
        }

        DrawLineEx(startPoint, endPoint, thick, bgColor);
    }
} 