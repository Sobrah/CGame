#include "move.c"

const Color LIGHTS[USERS_NUMBER] = {
    {190, 149, 196, 255},
    {85, 166, 48, 255},
    {255, 186, 8, 255},
    {0, 180, 216, 255}
};
const Color DARKS[USERS_NUMBER] = {
    {94, 84, 142, 255},
    {0, 127, 95, 255},
    {244, 140, 6, 255},
    {0, 119, 182, 255}
};

#define THICK 1
#define WALL_THICK (PROPERTY_LENGTH * THICK)
#define GROUND_COLOR (BROWN)
#define BORDER_COLOR (DARKBROWN)
#define WALL_COLOR (ORANGE)


// Graphical Function Prototypes
void DrawCharacters(void);
void DrawBoard(void);
void DrawScoreBoard(void);
void DrawUserProperty(Coordinate, int);


// Draw Characters
void DrawCharacters(void) {
    for (int i = 0; i < SET_LENGTH; i++) {
        Coordinate point;

        for (int j = 0; j < CharacterSet[i].n; j++) {
            if (CharacterSet[i].Characters[j].inactive) continue;

            point = CharacterSet[i].Characters[j].point; 
            DrawTexture(
                CharacterSet[i].pature.texture,
                point.x * CELL_SIZE + WINDOW_DELTA,
                point.y * CELL_SIZE, WHITE
            );
        }
    }
}

// Draw Board
void DrawBoard(void) { 
    for (int i = 0; i < BOARD_SIZE; i++) {        
        for (int j = 0; j < BOARD_SIZE; j++) {
            Vector2 ePoint, sPoint = {
                CELL_SIZE * j + WINDOW_DELTA,
                CELL_SIZE * i
            };

            // Draw Cell
            DrawRectangleLinesEx(
                (Rectangle){
                    sPoint.x, sPoint.y, CELL_SIZE, CELL_SIZE
                }, THICK, BORDER_COLOR
            );

            // Draw Wall
            if (!Board[i][j].wall) continue;

            ePoint = sPoint;
            switch (Board[i][j].wall) {
                case NORTH: ePoint.x += CELL_SIZE; break;
                case WEST: ePoint.y += CELL_SIZE; break;
            }
            DrawLineEx(sPoint, ePoint, WALL_THICK, WALL_COLOR);
        }
    }

    // Board Outline
    DrawRectangleLinesEx(
        (Rectangle){
            0, 0, WINDOW_WIDTH, WINDOW_HEIGHT
        }, THICK, BORDER_COLOR
    );
}

// Draw Score Board & Related Info
void DrawScoreBoard(void) {
    Coordinate point = {0, 0};

    for (int i = 0; i < USERS_NUMBER / 2; i++) {        

        // Draw Round BackGround
        Rectangle rectangle = {
            point.x, point.y, WINDOW_DELTA, CELL_SIZE
        };
        DrawRectangleRec(rectangle, WHITE);
        DrawRectangleLinesEx(rectangle, THICK, DARKBROWN);

        // Draw Round Text
        int posX, posY, fontSize = 0.8 * CELL_SIZE;
        const char *text = TextFormat("Round %2i", ScoreBoard.round);

        posX = point.x + (WINDOW_DELTA - MeasureText(text, fontSize)) / 2;
        posY = point.y + (CELL_SIZE - fontSize) / 2;
        DrawText(text, posX, posY, fontSize, BLACK);

        // Draw User Property
        posY = CELL_SIZE;
        for (int j = 0; j < USERS_NUMBER / 2; j++) {
            DrawUserProperty(
                (Coordinate){point.x, posY}, 2 * i + j
            );
            posY += MID_CELL * CELL_SIZE;
        }

        point.x = WINDOW_DELTA + WINDOW_HEIGHT;
    }
}

// Draw User Property
void DrawUserProperty(Coordinate start, int index) {
    Rectangle rectangle = {
        start.x, start.y, WINDOW_DELTA, MID_CELL * CELL_SIZE
    };
    
    DrawRectangleRec(rectangle, DARKS[index]);
    if (ScoreBoard.turn == index)
        DrawRectangleLinesEx(rectangle, MID_CELL, LIGHTS[index]);
    DrawRectangleLinesEx(rectangle, THICK, BORDER_COLOR);

    int *property = &ScoreBoard.Users[index].feature.score;

    int fontSize = 1.2 * CELL_SIZE;
    int posY = start.y + CELL_SIZE;

    for (int i = 0; i < PROPERTY_LENGTH; i++) {
        const char *text = TextFormat("%-3i", *(property + i));

        int textureWidth = ScoreBoard.Patures[i].texture.width;  
        int textWidth = MeasureText(text, fontSize);

        int posX = start.x + (WINDOW_DELTA - textureWidth - textWidth) / 2;
        
        DrawText(text, posX, posY, fontSize, WHITE);
        DrawTexture(
            ScoreBoard.Patures[i].texture,
            posX + textWidth, posY, WHITE
        );

        posY += 2 * CELL_SIZE;
    }
}
