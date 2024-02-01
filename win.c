#include "cgame.h"

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
   
   char *StandNumber[] ={
        "2",
        "1",
        "3"
    };
    const int MEDALL_LENGTH = sizeof(StandNumber) / sizeof(char *);
    const int BTNLABLE_LENGTH = sizeof(BtnLable) / sizeof(char *);

    

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
                "Images/Medalls/",
                MEDALL_NAME,
                MEDALL_LENGTH,
                3 * CELL_SIZE
            );

    //Check Winers
    //TO DO
    
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
            int x = WINDOW_DELTA + CELL_SIZE; int y = CELL_SIZE;
            for(int i = 0  ; i < MEDALL_LENGTH ; i++ )
                DrawTexture(MEDALL_NAME[i].texture, x += i * (3*CELL_SIZE) ,y , WHITE);
            
            // Draw Back To Menu Button And Info
            DrawRectangleRec(Button,BORDER_COLOR);


            int fontSize = 2 * CELL_SIZE;
                
                Vector2 point = GetMousePosition();
                if(CheckCollisionPointRec(point , Button)) 
                fontSize = 2.1 * CELL_SIZE;

                //Draw Text 
                int textwidth = MeasureText(BtnLable, fontSize);
                DrawText(
                    BtnLable[BTNLABLE_LENGTH],
                    Button.x + (Button.width - textwidth) * 0.5,
                    Button.y + (Button.height - textwidth) * 0.5,
                    2 * CELL_SIZE,
                    GOLD
                );

                // Draw Win Cats
                //TO DO
                
        EndDrawing();

        //Check Click
        if(CheckCollisionPointRec(point , Button))
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                MenuScreen();
            }
    };

    // Unload Texture From Memory
    for(int i = 0 ; i < MEDALL_LENGTH ; i++){
        UnloadTexture(MEDALL_NAME[i].texture);
    }
}
