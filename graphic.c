#include "logic.c"


// Prototypes
void DrawBoard(Color, Color);
void DrawCharacters(void);
void DrawWalls(int, Color);


int main(void) { 
    // Initialize Window
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Mr. Clobber's Backyard");
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

    
    // Rendering Frames Until When It Should Be Closed
    while (!WindowShouldClose()) {
        BeginDrawing();
            DrawBoard(BROWN, DARKBROWN);
            DrawCharacters();
            DrawWalls(DIRECTION_COUNT, ORANGE);
        EndDrawing();
    }
    

    // Unload Textures From Memory
    for (int i = 0; i < SET_LENGTH; i++) {
        UnloadTexture(CharacterSet[i].texture);
    }

    CloseWindow();   
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