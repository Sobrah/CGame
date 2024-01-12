#include "logic.c"


// Graphical Function Prototypes
void PlayScreen(void);
void DrawCharacters(void);
void DrawScoreBoard(int, Color);
void ScoreBoardIcons(void);
void DrawBoard(Color, int, Color);
void DrawScoreBoardTable(int, Color);


// Logical Function Prototypes
void InitBoard(void);
void CheckMove(void);
Coordinate RandCell(int, int, char);
void ProcessMove(Coordinate, Coordinate);


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

    // Draw Round Text
    const char *text = TextFormat("Round\t%i", ScoreBoard.round);
    Vector2 position = {
        (WINDOW_WIDTH + WINDOW_HEIGHT - MeasureText(text, font.baseSize)) / 2,
        (CELL_SIZE - font.baseSize) / 2
    };
    DrawTextEx(font, text, position, font.baseSize, 0, BLACK); 
    
    int x = (WINDOW_HEIGHT + WINDOW_WIDTH) / 2;
    int y = 2 * CELL_SIZE;
    int loopHelp[2][SCORE_TYPE_MEMBER] = {
        {
            ScoreBoard.Users[0].score,
            ScoreBoard.Users[0].strength,
            ScoreBoard.Users[0].energy
        }, {
            ScoreBoard.Users[1].score,
            ScoreBoard.Users[1].strength,
            ScoreBoard.Users[1].energy
        }
    };
    for (int i = 0; i < USER_NUMBER; i++) {
        for (int j = 0; j < SCORE_TYPE_MEMBER; j++, y += 2 * CELL_SIZE) {
            const char *text = TextFormat("%i", loopHelp[i][j]);
            DrawText(text, x - MeasureText(text, font.baseSize), y, CELL_SIZE, WHITE);

            // Draw Score Board Icons
            DrawTexture(ScoreBoard.textures[j],
            x + 15,
            y ,
            WHITE
            );
        }
        y += CELL_SIZE;
    }
}




// Draw Score Board Table
void DrawScoreBoardTable(int thick, Color borderColor) {
    Vector2 position = {WINDOW_HEIGHT, 0};
    Vector2 size = {WINDOW_DELTA, CELL_SIZE};

    // White Area
    DrawRectangleV(position, size, WHITE);
    position.y += size.y;
    size.y = (BOARD_SIZE - 1) * CELL_SIZE / 2;
    
    // Red Area
    DrawRectangleV(position, size, MAROON);
    DrawLineEx(position, (Vector2){WINDOW_WIDTH, position.y}, thick, borderColor);
    position.y += size.y;

    // Blue Area
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
Coordinate RandCell(int start, int range, char factor) {
    int x, y;
    bool value;

    do {
        x = rand() % range + start;
        y = rand() % range + start;

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
                *point = RandCell(0, BOARD_SIZE, 'P');

            Board[point -> y][point -> x] = (Cell){
                &CharacterSet[i], &CharacterSet[i].Characters[j]
            };
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

// Check Board Movements
void CheckMove(void) {
    int key = GetKeyPressed();
    Coordinate ePoint, sPoint;

    ePoint = sPoint = CharacterSet[ScoreBoard.turn].Characters[0].point;

    switch (key) {
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
            ScoreBoard.turn = (ScoreBoard.turn + 1) % USER_NUMBER;
            return;
    }

    // Check Board Limit
    if (
        ePoint.x < 0 || ePoint.x >= BOARD_SIZE ||
        ePoint.y < 0 || ePoint.y >= BOARD_SIZE
    ) return;

    ProcessMove(sPoint, ePoint);
}

void ProcessMove(Coordinate sPoint, Coordinate ePoint) {
    Cell *sCell, *eCell;
    sCell = &Board[sPoint.y][sPoint.x];
    eCell = &Board[ePoint.y][ePoint.x];

    if (!eCell -> primary) {
        CharacterSet[ScoreBoard.turn].Characters[0].point = ePoint;

        eCell -> primary = sCell -> primary;
        eCell -> secondary = sCell -> secondary;

        Board[sPoint.y][sPoint.x].primary = NULL;
        return;
    }

    switch(eCell -> primary -> type) {
        case 'M':
            eCell -> secondary -> inactive = true;
            ScoreBoard.Users[ScoreBoard.turn].score += 1;

            CharacterSet[ScoreBoard.turn].Characters[0].point = ePoint;
            
            eCell -> primary = sCell -> primary;
            eCell -> secondary = sCell -> secondary;

            Board[sPoint.y][sPoint.x].primary = NULL;
            return;
    }
}