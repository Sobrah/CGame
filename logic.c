#include "info.c"

// For Random Functionality
#include <stdlib.h>
#include <time.h>


// Initialization
void InitBoard(int);
void InitScoreBoard(void);

// Randomness
int FindRadius(Coordinate);
Coordinate RadiusRandCell(Coordinate);
Coordinate RandCell(Coordinate, int, char);


// Initialize Board
void InitBoard(int walls) {
    for (int i = 0; i < SET_LENGTH; i++) {
        
        // Initialize Characters
        for (int j = 0; j < CharacterSet[i].n; j++) {            
            Coordinate *point = &CharacterSet[i].Characters[j].point;

            if (!CharacterSet[i].fix) {
                *point = RandCell((Coordinate){0, 0}, BOARD_SIZE, 'P');
            }

            Board[point -> y][point -> x] = (Cell){
                CharacterSet + i, 
                CharacterSet[i].Characters + j
            };
        }

        // Initialize Texture
        Image itemImage = LoadImageSvg(
            CharacterSet[i].pathTexture.path,
            CELL_SIZE,
            CELL_SIZE
        );
        CharacterSet[i].pathTexture.texture = LoadTextureFromImage(itemImage);
        UnloadImage(itemImage);
    }

    // Initialize Walls
    for (int i = 0; i < walls; i++) {
        
        // Zero Is Not Valid
        Coordinate point = RandCell((Coordinate){1, 1}, BOARD_SIZE - 1, 'W');
        
        Board[point.y][point.x].wall = (
            rand() % DIRECTION_COUNT ? WEST : NORTH
        );
    }
}

// Initialize Score Board
void InitScoreBoard(void) {
    
    // Initialize Users
    for (int i = 0; i < USERS_NUMBER; i++) {
        ScoreBoard.Users[i] = (User) {
            DEFAULT_USER_PROPERTY,
            (Conduct){
                CharacterSet + i, CharacterSet[i].Characters
            }
        };
    }

    // Load Textures
    for (int i = 0; i < PROPERTY_LENGTH; i++) {
        Image itemImage = LoadImageSvg(
            ScoreBoard.PathTextures[i].path,
            CELL_SIZE,
            CELL_SIZE
        );
        ScoreBoard.PathTextures[i].texture = LoadTextureFromImage(itemImage);
        UnloadImage(itemImage);
    }
}


// Find Empty Random Cell Base on Coordinate
Coordinate RadiusRandCell(Coordinate point) {
    int radius = FindRadius(point);

    return RandCell(
        (Coordinate) {
            point.x - radius, point.y - radius
        }, 2 * radius + 1, 'P'
    );
}

// Find the First Empty Radius
int FindRadius(Coordinate point) {
    int radius, last = BOARD_SIZE - 1;
    
    for (int radius = 0; radius < BOARD_SIZE; radius ++) {
        Coordinate row = {
            point.y - radius > 0 ? point.y - radius : 0,
            point.y + radius < last ? point.y + radius : last
        }, col = {
            point.x - radius > 0 ? point.x - radius : 0,
            point.x + radius < last ? point.x + radius : last
        };
        
        for (; row.x <= row.y; row.x ++) {
            for (; col.x <= col.y; col.x ++) {
                if (!Board[row.x][col.x].route.primary) return radius;
            }
        }
    }
}

// Find Empty Cell Base On Wall Or Primary
Coordinate RandCell(Coordinate start, int range, char factor) {
    bool value;
    Coordinate point, end = {
        start.x + range - 1,
        start.y + range - 1
    }, radius = {
        end.x < BOARD_SIZE ? range : BOARD_SIZE - start.x,
        end.y < BOARD_SIZE ? range : BOARD_SIZE - start.x
    };

    do {
        point.x = rand() % radius.x + start.x;
        point.y = rand() % radius.y + start.y;

        switch (factor) {
            case 'P': value = Board[point.y][point.x].route.primary; break;
            case 'W': value = Board[point.y][point.x].wall; break;
            default: exit(1); // Unknown Factor
        }
    } while(value);

    return point;
}