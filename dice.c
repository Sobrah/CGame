#include "graphic.c"

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


    while (!WindowShouldClose()) {
        
        // Set Textures Coordination
        int xspace = (WINDOW_WIDTH - 4 * TEXTURE_SIZE) / 5;
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
                BROWN
             );

            // CheckCollision
            

             if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

                Vector2 mouse = GetMousePosition();

                //If Click Button
                if(CheckCollisionPointRec(mouse , 
                (Rectangle){
                xbtn , ybtn ,
                TEXTURE_SIZE ,TEXTURE_SIZE}
                )){
                    
                    // Set Dices Texture 
                    int number = rand() % 6 + 1 ;
                    
                    int x = xspace;
                    int y =  2 * TEXTURE_SIZE;

                    if(!sizeof(diceNumbers)){

                        diceNumbers[0] = number;
                        DrawTexture(DICE_TEXTURES[number], x , y , WHITE);
                    }
                    else {
                        // Search Repetitious Numbers & Load Dices Texture
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