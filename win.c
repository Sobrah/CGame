#include "graphic.c"

Pature MEDALL_NAME[] = {
        {"silver medall.svg"},
        {"gold medall.svg"},
        {"bronze medall.svg"}
};

// Win Screen
void WinScreen() {

   
    const int MEDALL_LENGTH = sizeof(MEDALL_NAME) / sizeof(char *);

    // Platform Rectangle
    Rectangle Standrec[MEDALL_LENGTH] , rectangle={
        WINDOW_DELTA + 3*CELL_SIZE,
        8 * CELL_SIZE,
        3 * CELL_SIZE,
        3 * CELL_SIZE
    };

    //Intialize Standrec
    for(int i = 0 ; i < MEDALL_LENGTH ; i++){
        Standrec[i] = rectangle;
        Standrec[i].x += i * ( 3 *CELL_SIZE); 
    }

    char *StandNumber[MEDALL_LENGTH] ={
        "2",
        "1",
        "3"
    };

    //Intialize Line
    int startx = WINDOW_DELTA + 3*CELL_SIZE;
    int endx = startx + 9 * CELL_SIZE;
    int y = 11 * CELL_SIZE;

    //Load Medall Texture
            LoadPatures(
                "Images/Win Board/",
                MEDALL_NAME,
                MEDALL_LENGTH,
                3 * CELL_SIZE
            );

    while(!WindowShouldClose()){
        BeginDrawing();

            // Draw Background
            ClearBackground(GROUND_COLOR);

            //Draw Standrec
            for(int i = 0 ; i < MEDALL_LENGTH ; i++){
                DrawRectangleRec(Standrec[i],BORDER_COLOR);

                //Draw Standrec Number
                int textwidth = MeasureText(StandNumber[i], 2 *CELL_SIZE);
                DrawText(
                        StandNumber[i],
                        Standrec[i].x + (Standrec[i].width - textwidth) / 2,
                        Standrec[i].y + (Standrec[i].height - CELL_SIZE) /2,
                        2 * CELL_SIZE , WALL_COLOR
                );
            }
                
                DrawLine(startx,y,endx,y , GROUND_COLOR);

            // Draw Medall Texture
            int x = WINDOW_DELTA + CELL_SIZE; int y = CELL_SIZE;
            for(int i = 0  ; i < MEDALL_LENGTH ; i++ )
                DrawTexture(MEDALL_NAME[i].texture, x += i * (3*CELL_SIZE) ,y , WHITE);
            
            // Draw Back To Menu Button
            

        EndDrawing();
    };
}