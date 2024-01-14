#include "graphic.c"


int main(void) { 
    
    // Initialize Window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mr. Clobber's Backyard");
    SetTargetFPS(FRAME_PER_SECOND);
    
    // Load Textures to the Memory
    for (int i = 0; i < SET_LENGTH; i++) {
        Image itemImage = LoadImageSvg(
            CharacterSet[i].path,
            CELL_SIZE,
            CELL_SIZE
        );
        CharacterSet[i].texture = LoadTextureFromImage(itemImage);
        UnloadImage(itemImage);
    }
    for (int i = 0; i < SCORE_TYPE_COUNT; i++) {
        Image itemImage = LoadImageSvg(
            ScoreBoard.paths[i],
            CELL_SIZE,
            CELL_SIZE
        );
        ScoreBoard.textures[i] = LoadTextureFromImage(itemImage);
        UnloadImage(itemImage);
    }

    // Initialize Seed // srand(time(NULL));
    
    // Initialization
    InitBoard();

    // Main Screen For Now
    PlayScreen();
    
    // Unload Textures From Memory
    for (int i = 0; i < SET_LENGTH; i++) {
        UnloadTexture(CharacterSet[i].texture);
    }
    for (int i = 0; i < SCORE_TYPE_COUNT; i++) {
        UnloadTexture(ScoreBoard.textures[i]);
    }

    CloseWindow();   
}