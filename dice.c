#include "graphic.c"

#define diceLength (sizeof(DICE_PATHS) / sizeof(char *))
#define catlength (sizeof(CAT_PATHS) / sizeof(char *))

char *DICE_PATHS[] = {
    "Images/Dice/Craps.svg",
    "Images/Dice/Dice One.svg",
    "Images/Dice/Dice Two.svg",
    "Images/Dice/Dice Three.svg",
    "Images/Dice/Dice Four.svg",
    "Images/Dice/Dice Five.svg",
    "Images/Dice/Dice Six.svg"
};

char *CAT_PATHS[] = {
    "Images/Blue Cat.svg",
    "Images/Green Cat.svg",
    "Images/Purple Cat.svg",
    "Images/Yellow Cat.svg"
};

Texture DICE_TEXTURES[diceLength];
Texture CAT_TEXTURES[catlength];

void DiceScreen(void) {
    
    // Load Textures
    for (int i = 0; i < diceLength; i++) {
        Image itemImage = LoadImageSvg(
            DICE_PATHS[i],
            2 * CELL_SIZE,
            2 * CELL_SIZE
        );
        DICE_TEXTURES[i] = LoadTextureFromImage(itemImage);
        UnloadImage(itemImage);
    }
    for(int i = 0; i < catlength ; i++){
        Image itemImage = LoadImageSvg(
            CAT_PATHS[i],
            2 * CELL_SIZE,
            2 * CELL_SIZE
        );
        CAT_TEXTURES[i] = LoadTextureFromImage(itemImage);
        UnloadImage(itemImage);
    }

    // Set Textures Cordination
    int x = 60;
    int y = 2 *CELL_SIZE;

    int dicenumbers[catlength];

    


    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BROWN);

        
        // Draw Cat Textures
        for (int i = 0 ; i < catlength ; x += 60 + 2* CELL_SIZE, i++)
        {
            DrawTexture(CAT_TEXTURES[i], x ,y , WHITE);
        }
        
            DrawTexture(DICE_TEXTURES[0], 362 , 550, WHITE);

        EndDrawing();
    }
}


// Do Not Touch Here
int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mr. Clobber's Backyard");

    DiceScreen();
}