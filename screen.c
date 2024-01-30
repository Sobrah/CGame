#include "graphic.c"


void MenuScreen(void);
void PlayScreen(void);
void DiceScreen(void);


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


// Menu Screen
void MenuScreen(void) {
    
    // Screen Labels
    const char *Labels[] ={
        "Start",
        "New",
        "Save",
        "Load"
    }; 
    const int LABELS_LENGTH = sizeof(Labels) / sizeof(char *);

    // Screen Buttons 
    Rectangle Buttons[LABELS_LENGTH], rectangle = {
        WINDOW_DELTA + CELL_SIZE,
        CELL_SIZE,
        5 * CELL_SIZE,
        5 * CELL_SIZE
    };

    // Initialize Buttons
    for (int i = 0; i < LABELS_LENGTH / 2; i++) {
        for (int j = 0; j < LABELS_LENGTH / 2; j++) {
            Buttons[2 * i + j] = rectangle;
            Buttons[2 * i + j].x += j * (rectangle.width + 3 * CELL_SIZE);
        }
        rectangle.y += rectangle.height + 3 * CELL_SIZE;
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        
            // Draw Background
            ClearBackground(GROUND_COLOR);
            DrawScoreBoard();
            DrawCharacters();
            DrawBoard();

            // Draw Buttons
            for(int i = 0; i < LABELS_LENGTH; i++){
                DrawRectangleRec(Buttons[i], BORDER_COLOR);
            
                // Draw Text
                int textWidth = MeasureText(Labels[i], CELL_SIZE);
                DrawText(
                    Labels[i], 
                    Buttons[i].x + (Buttons[i].width - textWidth) / 2,
                    Buttons[i].y + (Buttons[i].height - CELL_SIZE) / 2,
                    CELL_SIZE, WALL_COLOR 
                );  
            } 
        EndDrawing();

        // Check Click
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 point = GetMousePosition();

            if(CheckCollisionPointRec(point, Buttons[0])) 
                break;
            if(CheckCollisionPointRec(point, Buttons[1]))
                exit(1);
            if(CheckCollisionPointRec(point, Buttons[2]))
                exit(2);
            if(CheckCollisionPointRec(point, Buttons[3]))
                exit(2);
        }
    }
    DiceScreen();
}


void DiceScreen(void) {

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
    
    // Initialize
    InitBoard("Images/Board/", BOARD_SIZE);
    
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