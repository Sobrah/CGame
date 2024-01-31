#include "cgame.h"


// Default Screen State
State ScreenState = MENU;


int main(void) { 
    
    // Initialize Window
    SetTargetFPS(FRAME_PER_SECOND);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mr. Clobber's Backyard");
    
    // Window Icon
    const Image ICON = LoadImageSvg(
        "Images/Board/Yellow Cat.svg", CELL_SIZE, CELL_SIZE
    ); 
    SetWindowIcon(ICON);

    // Initialize Seed 
    srand(1); // time(NULL));
    
    // Load Character Set Textures
    for (int i = 0; i < SET_LENGTH; i++) {
        LoadPature("Images/Board", &CharacterSet[i].pature, CELL_SIZE);
    }
    
    // Load Score Board Textures
    for (int i = 0; i < PROPERTY_LENGTH; i++) {
        LoadPature("Images/Score", ScoreBoard.Patures + i, CELL_SIZE);
    }

    // Start Game
    New();
    while (!WindowShouldClose()) {
        switch (ScreenState) {
            case MENU: MenuScreen(); break;
            case DICE: DiceScreen(); break;
            case PLAY: PlayScreen(); break;
            case WIN: break;
        }
    }
    
    // Unload Textures
    for (int i = 0; i < SET_LENGTH; i++) {
        UnloadTexture(CharacterSet[i].pature.texture);
    }
    for (int i = 0; i < PROPERTY_LENGTH; i++) {
        UnloadTexture(ScoreBoard.Patures[i].texture);
    }
    UnloadImage(ICON); 

    CloseWindow();
}