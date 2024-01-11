#include "logic.c"


// Graphical Function Prototypes
void PlayScreen(void);
void DrawBoard(Color, int, Color);
void DrawCharacters(void);
void DrawScoreBoard(int, Color);
void DrawScoreBoardTable(int, Color);


// Logical Function Prototypes
Coordinate RandCell(int, int, char);
void InitBoard(void);
void InitScoreBoard(void);
void CheckMove(void);
void ProcessMove(Coordinate, Coordinate);


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

    // Draw Round Text
    const char *text = TextFormat("Round\t%i", ScoreBoard.round);
    Vector2 position = {
        (SCREEN_WIDTH + SCREEN_HEIGHT - MeasureText(text, font.baseSize)) / 2,
        (CELL_SIZE - font.baseSize) / 2
    };
    DrawTextEx(font, text, position, font.baseSize, 0, BLACK); 
    
    int x = (SCREEN_HEIGHT + SCREEN_WIDTH) / 2;
    int y = 2 * CELL_SIZE;
    int loopHelp[SCORE_TYPE_LENGTH] = {
        ScoreBoard.Users[0].score,
        ScoreBoard.Users[0].strength,
        ScoreBoard.Users[0].energy
    };
    for (int i = 0; i < USER_NUMBER; i++) {
        for (int j = 0; j < SCORE_TYPE_LENGTH; j++, y += 2 * CELL_SIZE) {
            const char *text = TextFormat("%i", loopHelp[j]);
            DrawText(text, x - MeasureText(text, font.baseSize), y, CELL_SIZE, WHITE);
        }
        y += CELL_SIZE;
    }
}

void DrawScoreBoardTable(int thick, Color borderColor) {
    Vector2 position = {SCREEN_HEIGHT, 0};
    Vector2 size = {SCREEN_DELTA, CELL_SIZE};

    DrawRectangleV(position, size, WHITE);
    position.y += size.y;
    size.y = (BOARD_SIZE - 1) * CELL_SIZE / 2;
    
    DrawRectangleV(position, size, MAROON);
    DrawLineEx(position, (Vector2){SCREEN_WIDTH, position.y}, thick, borderColor);
    position.y += size.y;

    DrawRectangleV(position, size, DARKBLUE);
    DrawLineEx(position, (Vector2){SCREEN_WIDTH, position.y}, thick, borderColor);

    // Score Board Outline
    DrawRectangleLinesEx(
        (Rectangle){
            SCREEN_HEIGHT - thick, 0,
            SCREEN_DELTA + thick, SCREEN_HEIGHT
        }, thick, borderColor
    );
}

// Draw Board
void DrawBoard(Color borderColor, int thick, Color wallColor) { 
    // Board Outline
    DrawRectangleLinesEx(
        (Rectangle){0, 0, SCREEN_HEIGHT, SCREEN_HEIGHT},
        thick, borderColor
    );

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
        

            if (CharacterSet[i].Characters[j].isDead) continue;

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
                point = CharacterSet[i].Characters[j].point;
            } else {
                point = RandCell(0, BOARD_SIZE, 'F');
                CharacterSet[i].Characters[j].point = point;
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

// Check Board Movements
void CheckMove(void) {
    int key = GetKeyPressed();
    Coordinate ePoint, sPoint;

    ePoint = sPoint = CharacterSet[ScoreBoard.turn].Characters[0].point;

    switch (key) {
        case KEY_NULL:
            break;
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

    ProcessMove(sPoint,ePoint);
}

void ProcessMove(Coordinate sPoint, Coordinate ePoint) {
    Cell *sCell, *eCell;
    sCell = &Board[sPoint.y][sPoint.x];
    eCell = &Board[ePoint.y][ePoint.x];

    if (!eCell -> fill) {
        CharacterSet[ScoreBoard.turn].Characters[0].point = ePoint;

        eCell -> fill = true;
        eCell -> primary = sCell -> primary;
        eCell -> secondary = sCell -> secondary;

        Board[sPoint.y][sPoint.x].fill = false;
        return;
    }

    switch(CharacterSet[eCell -> primary].type) {
        case 'H':
            break;
        case 'M':
            CharacterSet[eCell -> primary].Characters[eCell ->secondary].isDead = true;
            ScoreBoard.Users[ScoreBoard.turn].score += 1;

            CharacterSet[ScoreBoard.turn].Characters[0].point = ePoint;
            

            eCell -> fill = true;
            eCell -> primary = sCell -> primary;
            eCell -> secondary = sCell -> secondary;

            Board[sPoint.y][sPoint.x].fill = false;
            return;
    }
}