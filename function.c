#include "logic.c"


// Graphical Function Prototypes
void PlayScreen(void);
void CheckMove(void);
void DrawBoard(Color, int, Color);
void DrawCharacters(void);
void DrawScoreBoard(int, Color);
void DrawUserInfo(void);

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
    y = (MID_CELL + 1) * CELL_SIZE;
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

    DrawUserInfo();
}

void DrawUserInfo(void) {
    // TODO: Add Textures
    int x = SCREEN_HEIGHT + (SCREEN_WIDTH - SCREEN_HEIGHT) / 2;

    DrawText(TextFormat("%i", ScoreBoard.Users[0].score), x, 2 * CELL_SIZE, CELL_SIZE, WHITE);
    DrawText(TextFormat("%i", ScoreBoard.Users[0].strength), x, 4 * CELL_SIZE, CELL_SIZE, WHITE);
    DrawText(TextFormat("%i", ScoreBoard.Users[0].energy), x, 6 * CELL_SIZE, CELL_SIZE, WHITE);
    
    DrawText(TextFormat("%i", ScoreBoard.Users[1].score), x, 9 * CELL_SIZE, CELL_SIZE, WHITE);
    DrawText(TextFormat("%i", ScoreBoard.Users[1].strength), x, 11 * CELL_SIZE, CELL_SIZE, WHITE);
    DrawText(TextFormat("%i", ScoreBoard.Users[1].energy), x, 13 * CELL_SIZE, CELL_SIZE, WHITE);
}

// Check Board Movements
int walkCount = 0;
void CheckMove(void) {
    if (walkCount >= 3) {
        ScoreBoard.turn = (ScoreBoard.turn + 1) % USER_NUMBER;
        walkCount = 0;
    }
    
    Coordinate *point = &CharacterSet[ScoreBoard.turn].Characters[0];

    switch (GetKeyPressed()) {
        case KEY_UP:
            if (Board[point -> y][point -> x].wall != NORTH) {
                point -> y -= 1;
                walkCount ++;
            }
            break;
        case KEY_LEFT:
            if (Board[point -> y][point -> x].wall != WEST) {
                point -> x -= 1;
                walkCount ++;
            }
            break;
        case KEY_DOWN:
            if (Board[point -> y + 1][point -> x].wall != NORTH) {
                point -> y += 1;
                walkCount ++;
            }
            break;
        case KEY_RIGHT:
            if (Board[point -> y][point -> x + 1].wall != WEST) {
                point -> x += 1;
                walkCount ++;
            }
            break;
    }
}

// Draw Board
void DrawBoard(Color borderColor, int thick, Color wallColor) { 
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            // Draw Cell
            DrawRectangleLines(
                CELL_SIZE * j,
                CELL_SIZE * i, 
                CELL_SIZE, CELL_SIZE,
                borderColor
            );

            // Draw Wall
            if (!Board[i][j].wall) continue;

            Vector2 endPoint, startPoint = {
            CELL_SIZE * j,
            CELL_SIZE * i
            };
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
            DrawTexture(
                CharacterSet[i].texture,
                CharacterSet[i].Characters[j].x * CELL_SIZE,
                CharacterSet[i].Characters[j].y * CELL_SIZE,
                WHITE
            );
        }
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
        
        Board[point.y][point.x].wall = (
            rand() % DIRECTION_COUNT ? WEST : NORTH
        );
    }
}