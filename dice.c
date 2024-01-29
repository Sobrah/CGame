#include "graphic.c"
#include <stdio.h>

#define TEXTURE_SIZE (3 * CELL_SIZE)
#define CAT_LENGTH (sizeof(CAT_PATHS) / sizeof(char *))
#define DICE_LENGTH (sizeof(DICE_PATHS) / sizeof(char *))

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

Texture DICE_TEXTURES[DICE_LENGTH];
Texture CAT_TEXTURES[CAT_LENGTH];


// Find Same DiceNumber
int SameNumber(int diceNumbers[CAT_LENGTH], int cat_lenght , int *i , int *j){

            int m ,n ;
            for(m = 0 ; m < cat_lenght ; m++)
                for(n = 0 ; n < cat_lenght ; n++){
                    if(n != m && diceNumbers[m] == diceNumbers[n]){ *i = m ; *j = n; return 1;} 
                }

            return 0;

}

void DiceScreen(void) {
    
    // Load Dice Textures
    for (int i = 0; i < DICE_LENGTH; i++) {
        Image itemImage = LoadImageSvg(
            DICE_PATHS[i], TEXTURE_SIZE, TEXTURE_SIZE
        );
        DICE_TEXTURES[i] = LoadTextureFromImage(itemImage);
        UnloadImage(itemImage);
    }
    
    // Cat Textures
    for(int i = 0; i < CAT_LENGTH; i++){
        Image itemImage = LoadImageSvg(
            CAT_PATHS[i], TEXTURE_SIZE, TEXTURE_SIZE
        );
        CAT_TEXTURES[i] = LoadTextureFromImage(itemImage);
        UnloadImage(itemImage);
    }


    int diceNumbers[CAT_LENGTH];
    int index = 0 ;
    int i  = 0 , j = 0 ;

    while (!WindowShouldClose()) {
        
        // Set Textures Coordination
        int xspace = (WINDOW_WIDTH - CAT_LENGTH * TEXTURE_SIZE) / (CAT_LENGTH+1);
        int x = xspace;
        int y = TEXTURE_SIZE /2 ;

        
        BeginDrawing();
            ClearBackground(BROWN);
            
            // Draw Cat Textures
            for (int i = 0 ; i < CAT_LENGTH; i++) {
                DrawTexture(CAT_TEXTURES[i], x, y, WHITE);
                x += xspace +TEXTURE_SIZE;
            }

            // Draw Dice Button

            int xbtn = (WINDOW_WIDTH - TEXTURE_SIZE) / 2;
            int ybtn = (4 * TEXTURE_SIZE) - CELL_SIZE;

            DrawTexture(DICE_TEXTURES[0], xbtn , ybtn, WHITE);
            DrawRectangleLines(
                xbtn , ybtn ,
                TEXTURE_SIZE , TEXTURE_SIZE ,
                BLACK
             );

            // CheckCollision

                x = xspace;
                y =  2 * TEXTURE_SIZE;
                Vector2 mouse = GetMousePosition();

                // Draw Dice Textrue
                    for(int i = 0 ; i < CAT_LENGTH && diceNumbers[i];x += xspace +TEXTURE_SIZE , i++){
                        DrawTexture(DICE_TEXTURES[diceNumbers[i]], x,y,WHITE);
                    }
                

                if(CheckCollisionPointRec(mouse , 
                  (Rectangle){
                   xbtn , ybtn , 
                   TEXTURE_SIZE ,TEXTURE_SIZE}
                ))
                {

                //If Click Button 
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    int number = (rand() % 6) +1;

                    if(!diceNumbers[index]){

                        diceNumbers[index] = number;
                        index = (index+1) % CAT_LENGTH;
                    }
                    else if(!SameNumber(diceNumbers,CAT_LENGTH,&i,&j) && diceNumbers[CAT_LENGTH-1]) PlayScreen();
                    else{
                        do
                        {
                        SameNumber(diceNumbers,CAT_LENGTH,&i,&j);
                        number = (rand() % 6) +1;
                        diceNumbers[i] = number;
                        } while (SameNumber(diceNumbers,CAT_LENGTH,&i,&j));
                        
                    }
                    
                }
             }

        EndDrawing();
    }
}


// Do Not Touch Here
int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mr. Clobber's Backyard");

    DiceScreen();
}