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



// Initialize Score Board
void InitScoreBoard(int *Order) {
    
    // Initialize Users
    int lastValue = __INT_MAX__;

    for (int i = 0; i < USERS_NUMBER; i++) {
        int maxIndex;
        for (int j = 0; j < USERS_NUMBER; j++) {
            if (Order[j] < lastValue) {
                maxIndex = j;
                break;
            }
        }

        for (int j = 0; j < USERS_NUMBER; j++) {
            if (Order[maxIndex] < Order[j] && Order[j] < lastValue)
                maxIndex = j;
        }

        ScoreBoard.Users[i].cat = (Conduct){
            CharacterSet + maxIndex, CharacterSet[maxIndex].Characters
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
