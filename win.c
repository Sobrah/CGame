#include "graphic.c"

Pature MEDALL_NAME[] = {
        {"silver medall.svg"},
        {"gold medall.svg"},
        {"bronze medall.svg"}
};

// Win Screen
void WinScreen() {

    char *BtnLable[] = {
        "Back to Menu"
    };
   
    const int MEDALL_LENGTH = sizeof(MEDALL_NAME) / sizeof(char *);
    const int BTNLABLE_LENGTH = sizeof(BtnLable) / sizeof(char *);

    char *StandNumber[MEDALL_LENGTH] ={
        "2",
        "1",
        "3"
    };

    // Stand Rectangle
    Rectangle StandOrButton[MEDALL_LENGTH ] , rectangle={
        WINDOW_DELTA + 3*CELL_SIZE,
        8 * CELL_SIZE,
        3 * CELL_SIZE,
        3 * CELL_SIZE
    };

    // Intialize Standrec
    for(int i = 0 ; i < MEDALL_LENGTH ; i++){
        StandOrButton[i] = rectangle;
        StandOrButton[i].x += i * ( 3 *CELL_SIZE); 
    }

    // Intialize Button
    Rectangle Button = { 
        WINDOW_DELTA + 5 * CELL_SIZE ,
        WINDOW_HEIGHT - (7/2) * CELL_SIZE ,
        5 * CELL_SIZE,
        3 * CELL_SIZE
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
                DrawRectangleRec(StandOrButton[i],BORDER_COLOR);

                //Draw Standrec Number
                int textwidth = MeasureText(StandNumber[i], 2 *CELL_SIZE);
                DrawText(
                        StandNumber[i],
                        StandOrButton[i].x + (StandOrButton[i].width - textwidth) / 2,
                        StandOrButton[i].y + (StandOrButton[i].height - CELL_SIZE) /2,
                        2 * CELL_SIZE , WALL_COLOR
                );
            }
                
                DrawLine(startx,y,endx,y , GROUND_COLOR);

            // Draw Medall Texture
            int medallx = WINDOW_DELTA + CELL_SIZE; int y = CELL_SIZE;
            for(int i = 0  ; i < MEDALL_LENGTH ; i++ )
                DrawTexture(MEDALL_NAME[i].texture, medallx += i * (3*CELL_SIZE) ,y , WHITE);
            
            // Draw Back To Menu Button
            DrawRectangleRec(Button,BORDER_COLOR);

                //Draw Text 
                int textwidth = MeasureText(BtnLable, 2 *CELL_SIZE);
                DrawText(
                    BtnLable[BTNLABLE_LENGTH],
                    Button.x + (Button.width - textwidth) / 2,
                    Button.y + Button.height - 
                );

        EndDrawing();
    };
}