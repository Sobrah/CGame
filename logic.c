#include "info.c"

// Save & Load Functionality
#include <stdio.h>

// Random Functionality
#include <stdlib.h>
#include <time.h>


#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)


// Initialize
void InitBoard(char *, int);

// Randomize
Coordinate RadiusRandCell(Coordinate);
Coordinate RandCell(Coordinate, Coordinate, char);




void LoadPatures(char *basePath, Pature *Patures, int n, int size) {
    for (int i = 0; i < n; i++) {
        const char *path[] = {basePath, Patures[i].path};
        
        Image picture = LoadImageSvg(
            TextJoin(path, sizeof(path) / sizeof(char *), ""), 
            size,
            size
        );
        Patures[i].texture = LoadTextureFromImage(picture);
        UnloadImage(picture);
    }
}

// Check Repetitive Dice
int CheckRepeat(int *Dice) {
    for (int i = 0; i < USERS_NUMBER; i++) {
        for (int j = i + 1; j < USERS_NUMBER; j++) {
            if (Dice[i] == Dice[j]) return i;
        }
    }
    return USERS_NUMBER;
}




// Initialize Board
void InitBoard(char *basePath, int walls) {
    Coordinate finish = {
        BOARD_SIZE - 1,
        BOARD_SIZE - 1
    }, start = {0, 0};

    // Initialize Characters
    for (int i = 0; i < SET_LENGTH; i++) {
        for (int j = 0; j < CharacterSet[i].n; j++) {            
            Coordinate *point = &CharacterSet[i].Characters[j].point;

            if (!point -> x) *point = RandCell(start, finish, 'P');

            // Add to Board
            Board[point -> y][point -> x].route = (Conduct){
                CharacterSet + i, 
                CharacterSet[i].Characters + j
            };
        }

        // Initialize Texture
        const char *path[] = {basePath, CharacterSet[i].pature.path};
        Image itemImage = LoadImageSvg(
            TextJoin(path, sizeof(path) / sizeof(char *), ""),
            CELL_SIZE, CELL_SIZE
        );
        CharacterSet[i].pature.texture = LoadTextureFromImage(itemImage);
        UnloadImage(itemImage);
    }

    // Initialize Walls
    for (int i = 0; i < walls; i++) {
        
        // Zero Is Not Valid
        Coordinate point = RandCell((Coordinate){1, 1}, finish, 'W');
        
        Board[point.y][point.x].wall = (
            rand() % DIRECTION_COUNT ? WEST : NORTH
        );
    }
}

// Initialize Score Board
void InitScoreBoard(char *basePath, int *Order) {
    
    // Initialize Users
    int lastValue = __INT_MAX__;

    for (int i = 0; i < USERS_NUMBER; i++) {
        int maxIndex = 0;

        for (int j = 0; j < USERS_NUMBER; j++) {
            if (Order[maxIndex] < Order[j] && Order[j] < lastValue)
                maxIndex = j;
        }

        ScoreBoard.Users[i] = (User) {
            DEFAULT_USER_PROPERTY,
            (Conduct){
                CharacterSet + maxIndex, CharacterSet[maxIndex].Characters
            }
        };

        lastValue = Order[maxIndex];
    }

    // Load Textures
    for (int i = 0; i < PROPERTY_LENGTH; i++) {
        const char *path[] = {basePath, ScoreBoard.Patures[i].path};
        
        Image itemImage = LoadImageSvg(
            TextJoin(path, sizeof(path) / sizeof(char *), ""),
            CELL_SIZE, CELL_SIZE
        );
        ScoreBoard.Patures[i].texture = LoadTextureFromImage(itemImage);
        UnloadImage(itemImage);
    }
}

// Find Random Cell Base on Coordinate
Coordinate RadiusRandCell(Coordinate point) {    
    for (int radius = 0; radius < BOARD_SIZE; radius ++) {
        Coordinate start = {
            MAX(point.x - radius, 0),
            MAX(point.y - radius, 0)
        }, finish = {
            MIN(point.x + radius, BOARD_SIZE - 1),
            MIN(point.y + radius, BOARD_SIZE - 1)
        }, current = start;
        
        for (; current.y <= finish.y; current.y ++) {
            for (; current.x <= finish.x; current.x ++) {
                
                // Find Empty Cell
                if (!Board[current.y][current.x].route.primary)
                    return RandCell(start, finish, 'P');
            }
        }
    }

    // Unkown Behavior
    exit(1);
}

// Find Empty Cell Base On Wall Or Primary
Coordinate RandCell(Coordinate start, Coordinate finish, char factor) {
    Coordinate point, range = {
        finish.x - start.x + 1,
        finish.y - start.y + 1
    }; bool value;

    do {
        point.x = rand() % range.x + start.x;
        point.y = rand() % range.y + start.y;

        switch (factor) {
            case 'P': value = Board[point.y][point.x].route.primary; break;
            case 'W': value = Board[point.y][point.x].wall; break;
            default: exit(1); // Unknown Factor
        }
    } while(value);

    return point;
}
