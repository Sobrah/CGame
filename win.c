#include "cgame.h"
#include <stdio.h>

#define MEDAL_LENGTH (sizeof(MEDAL_PATURES) / sizeof(Pature))

Pature MEDAL_PATURES[] = {
    {"Silver Medal.svg"},
    {"Gold Medal.svg"},
    {"Bronze Medal.svg"}
};

char *StandNumber[] ={
    "2",
    "1",
    "3"
};

char *CATS[] = {
    "Purple Cat.svg",
    "Green Cat.svg",
    "Blue Cat.svg",
    "Yellow Cat.svg"
};

int CompareProperty(const void *p1, const void *p2) {
    const User *u1 = p1; 
    const User *u2 = p2;
    if (u1 -> feature.score > u2 -> feature.score) return -1;
    if (u2 -> feature.score > u1 -> feature.score) return 1;
    
    if (u1 -> feature.strength > u2 -> feature.strength) return -1;
    if (u2 -> feature.strength > u1 -> feature.strength) return 1;

    if (u1 -> feature.energy > u2 -> feature.energy) return -1;
    if (u2 -> feature.energy > u1 -> feature.energy) return 1;

    return 0;
}


// Win Screen
void WinScreen() {
    // Load Medal Texture
    for (int i = 0; i < MEDAL_LENGTH; i++) {
        LoadPature("Images/Medal", MEDAL_PATURES + i, 3 * CELL_SIZE);
    }

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

    // Check Winners
    Pature WINNER_PATURES[3];
    User Users[USERS_NUMBER];

    // Copy Info
    for (int i = 0; i < USERS_NUMBER; i++) {
        Users[i] = ScoreBoard.Users[i];
    }

    // Sort
    qsort(Users, USERS_NUMBER, sizeof(User), CompareProperty);
    
    for (int i = 0; i < 3; i++) {
        int catIndex = Users[i].cat.primary - CharacterSet;
        WINNER_PATURES[i].path = CATS[catIndex];
        LoadPature(
            "Images/Board",
            WINNER_PATURES + i,
            3 * CELL_SIZE
        );
    }
    
    char *CAT_NAMES = {
        "Purple Cat",
        "Green Cat",
        "Blue Cat",
        "Yellow Cat"
    };
    
    // Save Winners
    FILE *file = fopen("Data/winners.txt","wt");

    // File Error
    if(!file) return;
    
    for(int i = 0 ; i < MEDAL_LENGTH ; i++) {
        fprintf(file ,"%d\. %s\n", i, CATS[i]);
    }
    
    fclose(file);
    
    while(!WindowShouldClose()){
        if (IsKeyDown(KEY_SPACE)) {
            ScreenState = MENU;
            New();
            break;
        }

        BeginDrawing();

            // Draw Background
            ClearBackground(GROUND_COLOR);
            DrawScoreBoard();
            DrawBoard();

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

            // Draw  Win Cats
            // Cat 2
            DrawTexture(WINNER_PATURES[0].texture,
            3 * CELL_SIZE + WINDOW_DELTA,
            5 * CELL_SIZE,
            WHITE
            );
            // Cat 1 
            DrawTexture(WINNER_PATURES[1].texture,
            6 * CELL_SIZE + WINDOW_DELTA,
            4 * CELL_SIZE,
            WHITE
            );
            // Cat 3
            DrawTexture(WINNER_PATURES[2].texture,
            9 * CELL_SIZE + WINDOW_DELTA,
            5 * CELL_SIZE,
            WHITE
            );
                
            DrawLine(startX, y, endX, y, GROUND_COLOR);

            // Draw Medal Texture
            int x = WINDOW_DELTA + CELL_SIZE; int y = CELL_SIZE;
            for (int i = 0  ; i < MEDAL_LENGTH ; i++)
                DrawTexture(MEDAL_PATURES[i].texture, x + i * (5 * CELL_SIZE), y, WHITE);

        EndDrawing();            
    };
    
    // Unload Textures
    for (int i = 0 ; i < MEDAL_LENGTH ; i++) {
        UnloadTexture(MEDAL_PATURES[i].texture);
    }
    for (int i = 0; i < 3; i++) {
        UnloadTexture(WINNER_PATURES[i].texture);
    }
}
