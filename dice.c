#include "screen.c"


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

int Dice[CAT_LENGTH] = {4, 4, 4, 4};

// Check Repetitive Dice
int CheckRepeat(void) {
    for (int i = 0; i < CAT_LENGTH; i++) {
        for (int j = i + 1; j < CAT_LENGTH; j++) {
            if (Dice[i] == Dice[j]) return i;
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
    int index = 4;

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

            for(int i = 0 ; i < CAT_LENGTH && Dice[i];x += xspace + TEXTURE_SIZE , i++) {
                DrawTexture(DICE_PATURES[Dice[i]].texture, x,y,WHITE);
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
            Dice[index] = rand() % (DICE_LENGTH - 1) + 1;
            index ++;
            continue;
        }

        int i = CheckRepeat();

        if(i == CAT_LENGTH) exit(1);
        while (CheckRepeat() <= i) {
            Dice[i] = rand() % (DICE_LENGTH - 1) + 1;
        }
    }
}


// Do Not Touch Here
int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mr. Clobber's Backyard");

    srand(time(NULL));
    
    DiceScreen();
}