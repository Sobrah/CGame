#include "logic.c"


// Graphical Function Prototypes
void PlayScreen(void);
void CheckMove(void);
void DrawBoard(Color, Color);
void DrawCharacters(void);
void DrawWalls(int, Color);
void DrawScoreBoard(int, Color);

// Draw Score Board & Related Info
void DrawScoreBoard(int thick, Color color) {
    Font font = GetFontDefault();
    int x, y;
    
    // Draw Table
    y = CELL_SIZE;
    DrawLineEx(
        (Vector2){SCREEN_HEIGHT, y},
        (Vector2){SCREEN_WIDTH, y},
        thick, color
    );
    y = (BOARD_SIZE - 1) / 2 * CELL_SIZE;
    DrawLineEx(
        (Vector2){SCREEN_HEIGHT, y},
        (Vector2){SCREEN_WIDTH, y}  ,
        thick, color
    );

    // Draw Round
    x = SCREEN_HEIGHT + (SCREEN_WIDTH - SCREEN_HEIGHT - MeasureText("Round 1", 20)) / 2;
    y = (CELL_SIZE - font.baseSize) / 2;
    DrawText(
        TextFormat("ROUND %i", ScoreBoard.round),
        x, y, 20, WHITE
    );

    DrawText(
        TextFormat("%i\t%i\t%i", ScoreBoard.Users[0].score, ScoreBoard.Users[0].strength, ScoreBoard.Users[0].energy),
        SCREEN_HEIGHT + 10,
        2 * CELL_SIZE,
        CELL_SIZE,
        WHITE
    );
}

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

// Check Board Movements
void CheckMove(void) {
    Coordinate *point = &CharacterSet[1].Characters[0];

    switch (GetKeyPressed()) {
        case KEY_UP:
            if (Board[point -> y][point -> x].wall != NORTH)
                point -> y -= 1;
            break;
        case KEY_LEFT:
            if (Board[point -> y][point -> x].wall != WEST)
                point -> x -= 1;
            break;
        case KEY_DOWN:
            if (Board[point -> y + 1][point -> x].wall != NORTH)
                point -> y += 1;
            break;
        case KEY_RIGHT:
            if (Board[point -> y][point -> x + 1].wall != WEST)
                point -> x += 1;
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
void InitScoreBoard(void);


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

// Initialize Score Board
void InitScoreBoard(void) {
    ScoreBoard.round = 1;
    ScoreBoard.turn = 0;
    for (int i = 0; i < USER_NUMBER; i++) {
        ScoreBoard.Users[i] = (struct User){0, 2, 5};
    }
}