#include "cgame.h"

#define MEDAL_LENGTH (sizeof(StandNumber) / sizeof(char))

Pature MEDAL_PATURES[] = {
    {"Silver Medal.svg"},
    {"Gold Medal.svg"},
    {"Bronze Medal.svg"}
};

// Win Screen
void WinScreen() {
    char *StandNumber[] ={
        "2th",
        "1th",
        "3th"
    };

    // Stand Rectangle
    Rectangle Stands[MEDAL_LENGTH], rectangle={
        3 * CELL_SIZE + WINDOW_DELTA,
        8 * CELL_SIZE,
        3 * CELL_SIZE,
        3 * CELL_SIZE
    };

    // Initialize Stands
    for (int i = 0 ; i < MEDAL_LENGTH; i++) {
        Stands[i] = rectangle;
        Stands[i].x += i * (3 * CELL_SIZE); 
    }

    // Initialize Buttons
    Rectangle Button = { 
        WINDOW_DELTA + 5 * CELL_SIZE ,
        WINDOW_HEIGHT - (7 / 2) * CELL_SIZE ,
        5 * CELL_SIZE,
        3 * CELL_SIZE
    };

    // Initialize Line
    int startX = WINDOW_DELTA + 3*CELL_SIZE;
    int endX = startX + 9 * CELL_SIZE;
    int y = 11 * CELL_SIZE;

    // Load Medal Texture
    for (int i = 0; i < MEDAL_LENGTH; i++) {
        LoadPature("Images/Medal", MEDAL_PATURES + i, 3 * CELL_SIZE);
    }

    // Check Winners
    // TO DO
    
    while(!WindowShouldClose()){
        BeginDrawing();

            // Draw Background
            ClearBackground(GROUND_COLOR);

            //Draw Strands
            for (int i = 0 ; i < MEDAL_LENGTH ; i++) {
                DrawRectangleRec(Stands[i], BORDER_COLOR);

                // Draw Stands Number
                int textWidth = MeasureText(StandNumber[i], 2 * CELL_SIZE);
                DrawText(
                    StandNumber[i],
                    Stands[i].x + (Stands[i].width - textWidth) / 2,
                    Stands[i].y + (Stands[i].height - CELL_SIZE) / 2,
                    2 * CELL_SIZE , WALL_COLOR
                );
            }
                
            DrawLine(startX, y, endX, y, GROUND_COLOR);

            // Draw Medal Texture
            int x = WINDOW_DELTA + CELL_SIZE; int y = CELL_SIZE;
            for (int i = 0  ; i < MEDAL_LENGTH ; i++)
                DrawTexture(MEDAL_PATURES[i].texture, x += i * (3 * CELL_SIZE), y, WHITE);
            
            // Draw Back To Menu Button And Info
            DrawRectangleRec(Button, BORDER_COLOR);

            int fontSize = 2 * CELL_SIZE;
                
            Vector2 point = GetMousePosition();
            if (CheckCollisionPointRec(point , Button)) 
                fontSize = 2.1 * CELL_SIZE;

            //Draw Text 
            /*
            int textWidth = MeasureText(StandNumber, fontSize);
                DrawText(
                    StandNumber[MEDAL_LENGTH],
                    Button.x + (Button.width - textWidth) * 0.5,
                    Button.y + (Button.height - textWidth) * 0.5,
                    2 * CELL_SIZE,
                    GOLD
            */

                // Draw Win Cats
                //TO DO
                
        EndDrawing();

        //Check Click
        if(CheckCollisionPointRec(point , Button))
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                MenuScreen();
            }
    };

    // Unload Textures
    for (int i = 0 ; i < MEDAL_LENGTH ; i++) {
        UnloadTexture(MEDAL_PATURES[i].texture);
    }
}
