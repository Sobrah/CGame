#include "graphic.c"

#define diceLength (sizeof(DICE_PATHS) / sizeof(char *))

char *DICE_PATHS[] = {
    "Images/Dice/Craps.svg",
    "Images/Dice/Dice One.svg",
    "Images/Dice/Dice Two.svg",
    "Images/Dice/Dice Three.svg",
    "Images/Dice/Dice Four.svg",
    "Images/Dice/Dice Five.svg",
    "Images/Dice/Dice Six.svg"
};

Texture DICE_TEXTURES[diceLength];

void DiceScreen(void) {
    
    // Load Textures
    for (int i = 0; i < diceLength; i++) {
        Image itemImage = LoadImageSvg(
            DICE_PATHS[i],
            3 * CELL_SIZE,
            3 * CELL_SIZE
        );
        DICE_TEXTURES[i] = LoadTextureFromImage(itemImage);
        UnloadImage(itemImage);
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BROWN);

            DrawTexture(DICE_TEXTURES[0], 500, 500, WHITE);
        EndDrawing();
    }
}


// Do Not Touch Here
int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mr. Clobber's Backyard");

    DiceScreen();
}