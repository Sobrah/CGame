#include "logic.c"


// Graphical Function Prototypes
void MenuScreen(void);
void DrawCharacters(void);
void DrawScoreBoard(int, Color);
void ScoreBoardIcons(void);
void DrawBoard(Color, int ,Color);
void DrawScoreBoardTable(int, Color);


// Logical Function Prototypes
void InitBoard(void);
void CheckMove(void);
Coordinate RandCell(Coordinate, int, char);
void ProcessMove(Coordinate, Coordinate);


// Menu Screen
void MenuScreen(void) {
    Color bgColor, borderColor;
    int thick = DIRECTION_COUNT;
    
    bgColor = BROWN;
    borderColor = DARKBROWN;
    char *btnlables[BUTTON_TYPE_MEMBER] ={
        "New Game" ,
        "Save Game",
        "Load Game"
    };

    Rectangle  buttons[BUTTON_TYPE_MEMBER];
    while (!WindowShouldClose()) {
        CheckMove();
        
        BeginDrawing();
            ClearBackground(bgColor);

            DrawBoard(borderColor, thick, ORANGE);
            DrawMenuScreen(borderColor , thick , btnlables,buttons);
            CheckCollisionMouse(buttons);
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
            const char *text = TextFormat("%i ", loopHelp[i][j]);
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
void DrawBoard(Color borderColor, int thick , Color wallColor) { 
    
     // Board Outline
    DrawRectangleLinesEx(
        (Rectangle){0, 0, WINDOW_HEIGHT, WINDOW_HEIGHT},
        thick, borderColor
    );

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < WINDOW_WIDTH / CELL_SIZE; j++) {
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

// Draw Menu Screen 
void DrawMenuScreen(Color borderColor , int thick ,
 char *btnlables[],
 Rectangle buttons[]
 )

 {

    // Board Outline
    
    int x = (WINDOW_WIDTH / 3);
    int y = (WINDOW_HEIGHT / 3) - (4 * CELL_SIZE);
    Color bgColor = DARKBROWN ;
    borderColor = BLACK;
    int fontSize = 1 * CELL_SIZE;
    int recwidth =  6* CELL_SIZE ;
    int recheight = 3* CELL_SIZE ;

    for(int i = 0 ; i < BUTTON_TYPE_MEMBER ; i++ , y+= 5*CELL_SIZE){

        DrawRectangleRec(
            (Rectangle){ 
            x, y, 
            recwidth, recheight } ,
            bgColor
        );

        DrawRectangleLines(
        x, y,
        recwidth, recheight,
        borderColor
        );

        // Draw Text

        const char *text = TextFormat("%s", btnlables[i]);
        int textWidth = MeasureText( text , fontSize);
        int textX = (WINDOW_WIDTH/3)+(6*CELL_SIZE-textWidth)/2;
        DrawText( text ,textX , y + CELL_SIZE ,fontSize , GOLD );

      
        //set rectangles info
    
        buttons[i].x = x;
        buttons[i].y = y;
        buttons[i].width = recwidth ;
        buttons[i].height = recheight;
     
        
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

// Check Buttons Clicks
void CheckCollisionMouse(Rectangle *buttons) {

        Vector2 mouse = GetMousePosition();

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            if(CheckCollisionPointRec(mouse, buttons[0]))exit(1);
            if(CheckCollisionPointRec(mouse, buttons[1]));
            if(CheckCollisionPointRec(mouse, buttons[2]));
        }

}

// New Game 
void NewGame(void) {


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
    User *user = &ScoreBoard.Users[ScoreBoard.turn];
    sCell = &Board[sPoint.y][sPoint.x];
    eCell = &Board[ePoint.y][ePoint.x];

    if (eCell -> primary) switch(eCell -> primary -> type) {
        case 'P':
            eCell -> secondary -> inactive = true;
            user -> strength ++;
            break;
        case 'F':
            eCell -> secondary -> inactive = true;
            int fishIndex = (eCell -> secondary) - (eCell -> primary -> Characters); 
            user -> energy += (fishIndex % 3) + 2; // 2 to 4 Inclusive

            int length, fishCount = 0;
            length = eCell -> primary -> n;
            for (int i = 0; i < length; i++) {
                if (!eCell -> primary -> Characters[i].inactive) fishCount ++;
            }

            if (fishCount < USER_NUMBER) for (int i = 0; i < length; i++) {
                eCell -> secondary -> inactive = false;
                Coordinate *point = &eCell -> primary -> Characters[i].point;
                *point = RandCell(*point, SCORE_TYPE_MEMBER, 'P');
            }

            break;
        case 'M':
            eCell -> secondary -> inactive = true;
            user -> score ++;
            break;
        default:
            return;
    }
    
    // Move on Character Set
    sCell -> secondary -> point = ePoint;

    // Move on Board
    eCell -> primary = sCell -> primary;
    eCell -> secondary = sCell -> secondary;

    // Remove from Last Cell
    sCell -> primary = NULL;
}