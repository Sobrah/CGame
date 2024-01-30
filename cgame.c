#include "screen.c"


int main(void) { 

    // Initialize Window
    SetTargetFPS(FRAME_PER_SECOND);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mr. Clobber's Backyard");
    
    // Initialize Seed 
    srand(1); // time(NULL));
    
    // Initialize
    InitBoard("Images/Board/", BOARD_SIZE);
    
    
    DiceScreen();
    
    CloseWindow();  
}