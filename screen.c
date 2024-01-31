#include "cgame.h"



// Check Repetitive Dice
int CheckRepeat(int *Dice) {
    for (int i = 0; i < USERS_NUMBER; i++) {
        for (int j = i + 1; j < USERS_NUMBER; j++) {
            if (Dice[i] == Dice[j]) return i;
        }
    }
    return USERS_NUMBER;
}



void DiceScreen(void) {
    
Pature DICE_PATURES[] = {
    {"Craps.svg"},
    {"One.svg"},
    {"Two.svg"},
    {"Three.svg"},
    {"Four.svg"},
    {"Five.svg"},
   { "Six.svg"}
};

Pature CAT_PATURES[] = {
    {"Purple Cat.svg"},
    {"Green Cat.svg"},
    {"Yellow Cat.svg"},
    {"Blue Cat.svg"}
};



    // Load Textures
    LoadPatures(
        "Images/Dice/",
        DICE_PATURES,
        MID_CELL,
        2 * CELL_SIZE
    );
    LoadPatures(
        "Images/Board/", 
        CAT_PATURES,
        USERS_NUMBER,
        3 * CELL_SIZE
    );

    // Current User Index
    int Dice[USERS_NUMBER] = {0}, index = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(GROUND_COLOR);
            DrawScoreBoard();
            DrawBoard();

            // Draw Cat Textures
            int x = WINDOW_DELTA + CELL_SIZE, y = CELL_SIZE;
            for (int i = 0 ; i < USERS_NUMBER / 2; i++) {
                for (int j = 0; j < USERS_NUMBER / 2; j++) {
                    DrawTexture(
                        CAT_PATURES[2 * i + j].texture,
                        x,
                        y + j * (7 * CELL_SIZE),
                        WHITE
                    );
                    DrawTexture(
                        DICE_PATURES[Dice[2 * i + j]].texture,
                        x + 0.5 * CELL_SIZE,
                        5 * CELL_SIZE + j * (7 * CELL_SIZE),
                        WHITE
                    );
                }
                x += 10 * CELL_SIZE;
            }
            Rectangle button = {
                WINDOW_DELTA + MID_CELL * CELL_SIZE - 0.5 * CELL_SIZE,
                MID_CELL * CELL_SIZE - 0.5 * CELL_SIZE,
                2 * CELL_SIZE,
                2 * CELL_SIZE
            };
            DrawTexture(
                DICE_PATURES[0].texture,
                button.x, button.y,
                WHITE
            );
        EndDrawing();

        // Click Button 
        if(
            !CheckCollisionPointRec(GetMousePosition(), button)
            ||
            !IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
        ) continue;

        if (index < USERS_NUMBER) {
            Dice[index] = rand() % 6 + 1;
            index ++;
            continue;
        }

        int i = CheckRepeat(Dice);
        if(i == USERS_NUMBER) {
            InitScoreBoard("Images/Score/", Dice);
        }

        while (CheckRepeat(Dice) <= i) {
            Dice[i] = rand() % 6 + 1;
        }
    }
}

// Play Screen
void PlayScreen(void) {
        
    // Initialize Texture
    for (int i = 0; i < SET_LENGTH; i++) {
        const char *path[] = {"Images/Board/", CharacterSet[i].pature.path};
        Image picture = LoadImageSvg(
            TextJoin(path, sizeof(path) / sizeof(char *), ""),
            CELL_SIZE, CELL_SIZE
        );
        CharacterSet[i].pature.texture = LoadTextureFromImage(picture);
        UnloadImage(picture);
    }
    // Load Textures
    for (int i = 0; i < PROPERTY_LENGTH; i++) {
        const char *path[] = {"Images/Score/", ScoreBoard.Patures[i].path};
        
        Image itemImage = LoadImageSvg(
            TextJoin(path, sizeof(path) / sizeof(char *), ""),
            CELL_SIZE, CELL_SIZE
        );
        ScoreBoard.Patures[i].texture = LoadTextureFromImage(itemImage);
        UnloadImage(itemImage);
    }
        
    // Initialize
    InitBoard(BOARD_SIZE);
    
    while (!WindowShouldClose()) {
        CheckMove();
        
        BeginDrawing();
            ClearBackground(GROUND_COLOR);
            DrawScoreBoard();
            
            DrawCharacters();
            DrawBoard();
        EndDrawing();
    }

        // Unload Textures from Memory
    for (int i = 0; i < SET_LENGTH; i++) {
        UnloadTexture(CharacterSet[i].pature.texture);
    }
    for (int i = 0; i < PROPERTY_LENGTH; i++) {
        UnloadTexture(ScoreBoard.Patures[i].texture);
    }
}