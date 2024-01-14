#include "logic.c"


// Graphical Function Prototypes
void PlayScreen(void);
void DrawCharacters(void);
void DrawScoreBoard(int, Color);
void DrawBoard(Color, int, Color);
void DrawScoreBoardTable(int, Color);


// Logical Function Prototypes
void InitBoard(void);
void CheckMove(void);
void MoveCharacter(Coordinate, Coordinate);
void ProcessMove(Coordinate, Coordinate);
Coordinate RandCell(Coordinate, int, char);


// Play Screen
void PlayScreen(void) {
    Color bgColor, borderColor, wallColor;
    int thick = DIRECTION_COUNT;
    
    bgColor = BROWN;
    borderColor = DARKBROWN;
    wallColor = ORANGE;
    
    while (!WindowShouldClose()) {
        CheckMove();
        
        BeginDrawing();
            ClearBackground(bgColor);

            DrawCharacters();
            DrawBoard(borderColor, thick, wallColor);
            DrawScoreBoard(thick, borderColor);
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
        int *n = &ScoreBoard.Users[ScoreBoard.turn].score;
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




// Find Empty Cell Base On Wall Or Primary
Coordinate RandCell(Coordinate start, int range, char factor) {
    int x, y;
    bool value;

    do {
        x = rand() % range + start.x;
        y = rand() % range + start.y;

        switch (factor) {
            case 'P': value = Board[y][x].primary; break;
            case 'W': value = Board[y][x].wall; break;
        }
    } while(value);

    return (Coordinate){x, y};
}

// Initialize Board
void InitBoard(void) {
    for (int i = 0; i < SET_LENGTH; i++) {
        for (int j = 0; j < CharacterSet[i].n; j++) {            
            Coordinate *point = &CharacterSet[i].Characters[j].point;

            if (!CharacterSet[i].fix) 
                *point = RandCell((Coordinate){0, 0}, BOARD_SIZE, 'P');

            Board[point -> y][point -> x] = (Cell){
                &CharacterSet[i], &CharacterSet[i].Characters[j]
            };
        }
    }

    // Initialize Walls
    for (int i = 0; i < BOARD_SIZE; i++) {
        
        // Zero Is Not Valid
        Coordinate point = RandCell((Coordinate){1, 1}, BOARD_SIZE - 1, 'W');
        
        Board[point.y][point.x].wall = (
            rand() % DIRECTION_COUNT ? WEST : NORTH
        );
    }
}

// Check Board Movements
void CheckMove(void) {
    Coordinate ePoint, sPoint;
    ePoint = sPoint = (
        CharacterSet[ScoreBoard.turn].Characters[0].point
    );

    switch (GetKeyPressed()) {
        case KEY_NULL:
            return;
        case KEY_UP:
            if (Board[sPoint.y][sPoint.x].wall == NORTH) return;
            ePoint.y --;
            break;
        case KEY_LEFT:
            if (Board[sPoint.y][sPoint.x].wall == WEST) return;
            ePoint.x --;
            break;
        case KEY_DOWN:
            if (Board[sPoint.y + 1][sPoint.x].wall == NORTH) return;
            ePoint.y ++;
            break;
        case KEY_RIGHT:
            if (Board[sPoint.y][sPoint.x + 1].wall == WEST) return;
            ePoint.x ++;
            break;
        case KEY_ENTER:
            ScoreBoard.turn = (ScoreBoard.turn + 1) % USERS_NUMBER;
            return;
    }

    // Check Board Limit
    if (
        ePoint.x < 0 || ePoint.x >= BOARD_SIZE 
        ||
        ePoint.y < 0 || ePoint.y >= BOARD_SIZE
    ) return;

    ProcessMove(sPoint, ePoint);
}

void ProcessMove(Coordinate sPoint, Coordinate ePoint) {
    Cell *sCell, *eCell;
    User *user = &ScoreBoard.Users[ScoreBoard.turn];
    sCell = &Board[sPoint.y][sPoint.x];
    eCell = &Board[ePoint.y][ePoint.x];

    if (!eCell -> primary) {
        MoveCharacter(sPoint, ePoint);
        return;
    }
    
    switch(eCell -> primary -> type) {
        case 'P':
            eCell -> secondary -> inactive = true;
            user -> strength ++;

            MoveCharacter(sPoint, ePoint);
            return;
        case 'F':
            eCell -> secondary -> inactive = true;
            int fishIndex = (eCell -> secondary) - (eCell -> primary -> Characters); 
            user -> energy += (fishIndex % 3) + 2; // 2 to 4 Inclusive

            CharacterType *fishSet = eCell -> primary;
            MoveCharacter(sPoint, ePoint);

            int length, fishCount = 0;
            length = fishSet -> n;
            
            // Count Active Fishes
            for (int i = 0; i < length; i++) {
                if (!fishSet -> Characters[i].inactive) fishCount ++;
            }
            
            // Reset Fishes
            if (fishCount < USERS_NUMBER) 
                for (int i = 0; i < length; i++) {
                    Coordinate point = fishSet -> Characters[i].point;
                    if (Board[point.y][point.x].primary) point = RandCell(point, 3, 'P');

                    fishSet -> Characters[i] = (Character){point, false };
                    Board[point.y][point.x].primary = fishSet;
                    Board[point.y][point.x].secondary = &fishSet -> Characters[i];
                }

            break;
        case 'M':
            eCell -> secondary -> inactive = true;
            user -> score ++;
            MoveCharacter(sPoint, ePoint);
            break;
        default:
            return;
    }
}

void MoveCharacter(Coordinate sPoint, Coordinate ePoint) {
    Cell *sCell, *eCell;
    sCell = &Board[sPoint.y][sPoint.x];
    eCell = &Board[ePoint.y][ePoint.x];
            
    // Move on Character Set
    sCell -> secondary -> point = ePoint;

    // Move on Board
    eCell -> primary = sCell -> primary;
    eCell -> secondary = sCell -> secondary;

    // Remove from Last Cell
    sCell -> primary = NULL;
}