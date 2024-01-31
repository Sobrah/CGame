#include "cgame.h"

#define DICE_LENGTH (sizeof(DICE_PATURES) / sizeof(Pature))


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
    {"Blue Cat.svg"},
    {"Yellow Cat.svg"}
};


// Check Repetitive Dice
int CheckRepeat(int *Dice) {
    for (int i = 0; i < USERS_NUMBER; i++) {
        for (int j = i + 1; j < USERS_NUMBER; j++) {
            if (Dice[i] == Dice[j]) return j;
        }
    }
    return USERS_NUMBER;
}

void DiceScreen(void) {

    // Load Dice Textures
    LoadPature("Images/Dice", DICE_PATURES , 3 * CELL_SIZE);
    for (int i = 1; i < DICE_LENGTH; i ++) {
        LoadPature("Images/Dice", DICE_PATURES + i, 2 * CELL_SIZE);
    }

    // Load Cat Textures
    for (int i = 0; i < USERS_NUMBER; i++) {
        LoadPature("Images/Board", CAT_PATURES + i, 4* CELL_SIZE);
    }

    // Current User Index
    int Dice[USERS_NUMBER] = {0}, index = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(GROUND_COLOR);
            DrawScoreBoard();
            DrawBoard();

            // Draw Cat Textures
            int x = WINDOW_DELTA + CELL_SIZE, y = CELL_SIZE * 0.5;
            for (int i = 0 ; i < USERS_NUMBER / 2; i++) {
                for (int j = 0; j < USERS_NUMBER / 2; j++) {
                    DrawTexture(
                        CAT_PATURES[2 * i + j].texture,
                        x,
                        y + j * (7 * CELL_SIZE),
                        WHITE
                    );
                    if (Dice[2 * i + j]) {
                        DrawTexture(
                            DICE_PATURES[Dice[2 * i + j]].texture,
                            x + CELL_SIZE,
                            5 * CELL_SIZE + j * (7 * CELL_SIZE),
                            WHITE
                        );
                    }
                }
                x += 9 * CELL_SIZE;
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

        if (GetKeyPressed() == KEY_SPACE) {
            ScreenState = MENU;
            break;
        }

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
        if (i == USERS_NUMBER) {
            InitScoreBoard(Dice);
            ScreenState = PLAY;
            break;
        }

        bool check = false;
        do {
            Dice[i] = rand() % 6 + 1;

            check = true;
            for (int j = 0; j < USERS_NUMBER; j++) {
                if (i == j) continue;
                
                if (Dice[i] == Dice[j]) {
                    check = false;
                    break;
                }
            }
        } while (!check);
    }

    // Unload Textures
    for (int i = 0; i < DICE_LENGTH; i++) {
        UnloadTexture(DICE_PATURES[i].texture);
    }
    for (int i = 0; i < USERS_NUMBER; i++) {
        UnloadTexture(CAT_PATURES[i].texture);
    }
}