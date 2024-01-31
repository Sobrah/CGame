#include "cgame.h"


int main(void) { 
    
    // Initialize Window
    SetTargetFPS(FRAME_PER_SECOND);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mr. Clobber's Backyard");
    
    // Window Icon
    Image ICON = LoadImageSvg(
        "Images/Board/Yellow Cat.svg", CELL_SIZE, CELL_SIZE
    ); 
    SetWindowIcon(ICON);

    // Initialize Seed 
    srand(1); // time(NULL));
    
    // Initialize
    InitBoard();
    
    
    DiceScreen();
    
    CloseWindow(); 

    UnloadImage(ICON); 
}