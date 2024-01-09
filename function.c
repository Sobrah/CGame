#include "logic.c"


// Graphical Function Prototypes
void PlayScreen(void);
void CheckMove(void);
void DrawBoard(Color, Color);
void DrawCharacters(void);
void DrawWalls(int, Color);
void DrawScoreBoard(int, Color);


// Play Screen
void PlayScreen(void) {
    while (!WindowShouldClose()) {
        CheckMove();
        
        BeginDrawing();
            DrawBoard(BROWN, DARKBROWN);
            DrawCharacters();
            DrawWalls(DIRECTION_COUNT, ORANGE);
            DrawScoreBoard(DIRECTION_COUNT, DARKBROWN);
        EndDrawing();
    }
}

// Draw Score Board & Related Info
void DrawScoreBoard(int thick, Color color) {
    DrawLineEx(
        (Vector2){SCREEN_HEIGHT, 0},
        (Vector2){SCREEN_HEIGHT, SCREEN_HEIGHT},
        thick, color
    );
    DrawLineEx(
        (Vector2){SCREEN_HEIGHT, SCREEN_HEIGHT / 2},
        (Vector2){SCREEN_WIDTH, SCREEN_HEIGHT / 2},
        thick, color
    );
}

// Check Board Movements
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

// Draw Board
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

// Draw Characters
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

// Draw Walls
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


// Logical Function Prototypes
Coordinate RandCell(int, int, char);
void InitBoard(void);


// Find Empty Cell Base On Wall Or Primary
Coordinate RandCell(int start, int range, char factor) {
    int x, y, value;

    do {
        x = rand() % range + start;
        y = rand() % range + start;

        switch (factor) {
            case 'F': value = Board[y][x].fill; break;
            case 'W': value = Board[y][x].wall; break;
        }
    } while(value);

    return (Coordinate){x, y};
}

// Initialize Board
void InitBoard(void) {
    
    // Initialize Seed
    // srand(time(NULL));

    for (int i = 0; i < SET_LENGTH; i++) {
        int length = CharacterSet[i].n;

        for (int j = 0; j < length; j++) {
            Coordinate point;
            
            if (CharacterSet[i].fix) {
                point = CharacterSet[i].Characters[j];
            } else {
                point = RandCell(0, BOARD_SIZE, 'F');
                CharacterSet[i].Characters[j] = point;
            } 

            Board[point.y][point.x] = (Cell){true, i, j};
        }
    }

    // Initialize Walls
    for (int i = 0; i < BOARD_SIZE; i++) {
        
        // Zero Is Not Valid
        Coordinate point = RandCell(1, BOARD_SIZE - 1, 'W');
        
        Walls[i] = point;
        Board[point.y][point.x].wall = (
            rand() % DIRECTION_COUNT ? WEST : NORTH
        );
    }
}