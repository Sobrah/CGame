#include "graphic.c"


void MenuScreen(void);
void PlayScreen(void);
void DiceScreen(void);


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
    
    // Initialize
    InitBoard("Images/Board/", BOARD_SIZE);
    InitScoreBoard("Images/Score/");

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
                exit(0);
            if(CheckCollisionPointRec(point, Buttons[1]))
                exit(1);
            if(CheckCollisionPointRec(point, Buttons[2]))
                exit(2);
            if(CheckCollisionPointRec(point, Buttons[3]))
                exit(2);
        }
    }
}


#define TEXTURE_SIZE (PROPERTY_LENGTH * CELL_SIZE)
#define CAT_LENGTH (sizeof(CAT_PATURES) / sizeof(Pature))
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
    {"Yellow Cat.svg"},
    {"Blue Cat.svg"}
};

Coordinate Dice[CAT_LENGTH];

// Check Repetitive Dice
int CheckRepeat(void) {
    for (int i = 0; i < CAT_LENGTH; i++) {
        for (int j = i + 1; j < CAT_LENGTH; j++) {
            if (Dice[i].y == Dice[j].y) return i;
        }
    }
    return CAT_LENGTH;
}

void LoadPatures(char *basePath, Pature *Patures, int n) {
    for (int i = 0; i < n; i++) {
        const char *path[] = {basePath, Patures[i].path};
        
        Image picture = LoadImageSvg(
            TextJoin(path, sizeof(path) / sizeof(char *), ""),
            TEXTURE_SIZE,
            TEXTURE_SIZE
        );

        Patures[i].texture = LoadTextureFromImage(picture);

        UnloadImage(picture);
    }
}

void DiceScreen(void) {

    // Load Dice Textures
    LoadPatures("Images/Dice/", DICE_PATURES, DICE_LENGTH);
    
    // Load Cat Textures
    LoadPatures("Images/Board/", CAT_PATURES, CAT_LENGTH);

    // Current User Index
    int index = 0;

    while (!WindowShouldClose()) {
        
        // Set Textures Coordination
        int xspace = (WINDOW_WIDTH - CAT_LENGTH * TEXTURE_SIZE) / (CAT_LENGTH + 1);
        int x = xspace;
        int y = TEXTURE_SIZE / 2;

        BeginDrawing();
            ClearBackground(GROUND_COLOR);
            
            // Draw Cat Textures
            for (int i = 0 ; i < CAT_LENGTH; i++) {
                DrawTexture(CAT_PATURES[i].texture, x, y, WHITE);
                x += xspace + TEXTURE_SIZE;
            }

            // Draw Dice Texture
            x = xspace;
            y =  2 * TEXTURE_SIZE;

            for(int i = 0 ; i < CAT_LENGTH && Dice[i].y;x += xspace + TEXTURE_SIZE , i++) {
                DrawTexture(DICE_PATURES[Dice[i].y].texture, x,y,WHITE);
            }
            
            // Draw Dice Button
            int xbtn = (WINDOW_WIDTH - TEXTURE_SIZE) / 2;
            int ybtn = (4 * TEXTURE_SIZE) - CELL_SIZE;

            DrawTexture(
                DICE_PATURES[0].texture,
                xbtn, ybtn, WHITE
            );
        EndDrawing();

        
        bool checkCollision = CheckCollisionPointRec(
            GetMousePosition(), 
            (Rectangle){
                xbtn, ybtn,
                TEXTURE_SIZE, TEXTURE_SIZE
            }
        );
        
        // Click Button 
        if(!checkCollision || !IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            continue;

        if (index < CAT_LENGTH) {
            Dice[index].y = rand() % (DICE_LENGTH - 1) + 1;
                index ++;
            continue;
        }

        int i = CheckRepeat();

        if(i == CAT_LENGTH) {
            break;
        }
        while (CheckRepeat() <= i) {
            Dice[i].y = rand() % (DICE_LENGTH - 1) + 1;
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