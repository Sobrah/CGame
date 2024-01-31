#include "cgame.h"


#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)


// Initialize

// Randomize
Coordinate RadiusRandCell(Coordinate);
Coordinate RandCell(Coordinate, Coordinate, char);

void LoadPature(char *basePath, Pature *pature, int size) {
    const char *path[] = {basePath, pature -> path};

    Image picture = LoadImageSvg(
        TextJoin(path, sizeof(path) / sizeof(char *), "/"), size, size
    );
    
    pature -> texture = LoadTextureFromImage(picture);
    UnloadImage(picture);
}

// Initialize Board
void InitBoard() {
    Coordinate finish = {
        BOARD_SIZE - 1,
        BOARD_SIZE - 1
    }, start = {0, 0};
    
    // Initialize Characters
    for (int i = 0; i < SET_LENGTH; i++) {
        for (int j = 0; j < CharacterSet[i].n; j++) {            
            Coordinate *point = &CharacterSet[i].Characters[j].point;

            if (!CharacterSet[i].fix) 
                *point = RandCell(start, finish, 'P');

            // Add to Board
            Board[point -> y][point -> x].route = (Conduct){
                CharacterSet + i, 
                CharacterSet[i].Characters + j
            };
        }
    }

    // Initialize Walls
    for (int i = 0; i < BOARD_SIZE; i++) {
        
        // Zero Is Not Valid
        Coordinate point = RandCell((Coordinate){1, 1}, finish, 'W');
        Direction side = rand() % DIRECTION_COUNT ? WEST : NORTH;

        Walls[i].point = point;
        Walls[i].wall = side;
        
        Board[point.y][point.x].wall = side;
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
            DEFAULT_PROPERTY,
            (Conduct){
                CharacterSet + maxIndex, CharacterSet[maxIndex].Characters
            }
        };

        lastValue = Order[maxIndex];
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
