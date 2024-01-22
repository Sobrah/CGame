#include "info.c"


// For Random Functionality
#include <stdlib.h>
#include <time.h>


// Movements
void CheckMove(void);
void ProcessMove(Coordinate);
void MoveCharacter(Cell *, Coordinate);

// Face Character
void RefreshFish(Cell);
void ConfrontTrap(void);
bool ConfrontDog(Coordinate);
void ReviveCharacter(Cell, Coordinate);


// Initialization
void InitBoard(int);
void InitScoreBoard(void);

// Randomness
int FindRadius(Coordinate);
Coordinate RadiusRandCell(Coordinate);
Coordinate RandCell(Coordinate, int, char);


// Check Board Movements
void CheckMove(void) {
    Coordinate endPoint = (
        ScoreBoard.Users[ScoreBoard.turn].userCat.secondary -> point
    );

    // Processing Pressed Key
    switch (GetKeyPressed()) {
        case KEY_NULL: return;
        case KEY_UP:
            if (Board[endPoint.y][endPoint.x].wall == NORTH) return;
            endPoint.y --; break;
        case KEY_LEFT:
            if (Board[endPoint.y][endPoint.x].wall == WEST) return;
            endPoint.x --; break;
        case KEY_DOWN:
            if (Board[endPoint.y + 1][endPoint.x].wall == NORTH) return;
            endPoint.y ++; break;
        case KEY_RIGHT:
            if (Board[endPoint.y][endPoint.x + 1].wall == WEST) return;
            endPoint.x ++; break;
        case KEY_ENTER:
            ScoreBoard.turn = (ScoreBoard.turn + 1) % USERS_NUMBER;
            return;
    }

    // Check Board Limit
    if (
        endPoint.x < 0 || endPoint.x >= BOARD_SIZE 
        ||
        endPoint.y < 0 || endPoint.y >= BOARD_SIZE
    ) return;
 
    ProcessMove(endPoint);
}

// Process Each Movement
void ProcessMove(Coordinate endPoint) {
    Cell endCell = Board[endPoint.y][endPoint.x];
    User *currentUser = &ScoreBoard.Users[ScoreBoard.turn];

    // Check Whether There Is Character
    if (endCell.primary) {
        switch (endCell.primary -> type) {
            case 'P':
                currentUser -> property.strength ++;
                endCell.secondary -> inactive = true;
                break;
            case 'F':
                
                // Index in the Character Array
                int fishIndex = (
                    endCell.secondary - endCell.primary -> Characters
                );
                currentUser -> property.energy += (
                    fishIndex % PROPERTY_LENGTH + 2
                );
                RefreshFish(endCell);
                endCell.secondary -> inactive = true;
                break;
            case 'M':
                currentUser -> property.score += (
                    (10 - endCell.primary -> n) / 2
                );
                currentUser -> rats[currentUser -> n] = endCell;
                currentUser -> n ++;
                endCell.secondary -> inactive = true;
                break;
            case 'T':
                ConfrontTrap();
                
                // New Cat Position
                endPoint = RadiusRandCell(endPoint);
                break;
            case 'D':
                if (ConfrontDog(endPoint)) {
                    endPoint = RadiusRandCell(endPoint);
                } else {
                    endCell.secondary -> inactive = true;
                }
                break;

            default: return;
        }
    }
    
    // Move Character
    Coordinate point = currentUser -> userCat.secondary -> point;
    Cell *startCell = &Board[point.y][point.x];
    
    // Middle Cell Case
    Cell tCell = currentUser -> userCat;
    if (currentUser -> userCat.secondary -> inactive) {
        currentUser -> userCat.secondary -> inactive = false;
        startCell = &tCell;
    }

    MoveCharacter(startCell, endPoint);
}

// Move Character
void MoveCharacter(Cell *startCell, Coordinate endPoint) {
    
    Cell *endCell = &Board[endPoint.y][endPoint.x];
    
    // Move on Character Set
    startCell -> secondary -> point = endPoint;

    // Move on Board
    endCell -> primary = startCell -> primary;
    endCell -> secondary = startCell -> secondary; 

    // Remove Start Cell from Board
    startCell -> primary = NULL;
}


// Revive Dead Character
void ReviveCharacter(Cell character, Coordinate point) {
    point = RadiusRandCell(point);

    // Update Character Position
    character.secondary -> point = point;
    character.secondary -> inactive = false;
    Board[point.y][point.x].primary = character.primary;
    Board[point.y][point.x].secondary = character.secondary;
}

// Cat Faces Dog
bool ConfrontDog(Coordinate endPoint) {
    User *currentUser = &ScoreBoard.Users[ScoreBoard.turn];
    UserProperty *catProperty = &currentUser -> property;
    
    Cell *dogCell = &Board[endPoint.y][endPoint.x];
    int dogIndex = dogCell -> primary - CharacterSet;
    UserProperty *dogProperty = &Dogs[dogIndex - USERS_NUMBER];
    
    if (
        (float) dogProperty -> energy / dogProperty -> strength
        >=
        (float) catProperty -> energy / catProperty -> strength
    ) {
        for (int i = 0; i < currentUser -> n; i++) {
            ReviveCharacter(currentUser -> rats[i], endPoint);
        }
        currentUser -> n = 0;
        catProperty -> score = 0;
        dogProperty -> energy -= (
            catProperty -> strength * catProperty -> energy / dogProperty -> strength
        );
        return true;  
    } else {
        catProperty -> energy -= (
            dogProperty -> strength * dogProperty -> energy / catProperty -> strength
        );
        return false;
    }
}

// Cat Faces Trap
void ConfrontTrap(void) {
    User *currentUser = &ScoreBoard.Users[ScoreBoard.turn];
    
    // No Mouse to Release
    if (!currentUser -> n) {
        if (currentUser -> property.strength > 2) 
            currentUser -> property.strength -= 2;
        else 
            currentUser -> property.energy -= 3;
        return;
    }
    
    // Find Best Mouse
    int maxIndex = 0;
    for (int i = 1; i < currentUser -> n; i++) {
        if (currentUser -> rats[i].primary -> n < currentUser -> rats[maxIndex].primary -> n)
            maxIndex = i;
    }

    // Return Mouse to Board
    ReviveCharacter(
        currentUser -> rats[maxIndex], 
        currentUser -> rats[maxIndex].secondary -> point
    );

    // Reduce Score
    currentUser -> property.score -= (
        (10 - currentUser -> rats[maxIndex].primary -> n) / 2
    );

    // Remove from Eaten Mice
    currentUser -> n --;
    currentUser -> rats[maxIndex] = currentUser -> rats[currentUser -> n];
}

// Check Fish Number Status
void RefreshFish(Cell fishCell) {    
    Character *fishCharacters = fishCell.primary -> Characters;

    // Count Active Fishes
    int fishCount = 0;
    int fishN = fishCell.primary -> n;

    for (int i = 0; i < fishN; i++) {
        if (!fishCharacters[i].inactive) fishCount ++;
    }
            
    // Reset Fishes
    if (fishCount <= USERS_NUMBER) {

        // Revive Fishes
        for (int i = 0; i < fishN; i++) {  
            if (!fishCharacters[i].inactive) continue;
            
            ReviveCharacter(
                (Cell){fishCell.primary, fishCharacters + i},
                fishCharacters[i].point
            );
        }
    }
}


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
                &CharacterSet[i], &CharacterSet[i].Characters[j]
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
            (Cell){
                &CharacterSet[i],
                &CharacterSet[i].Characters[0]
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
                if (!Board[row.x][col.x].primary) return radius;
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
            case 'P': value = Board[point.y][point.x].primary; break;
            case 'W': value = Board[point.y][point.x].wall; break;
            default: exit(1); // Unknown Factor
        }
    } while(value);

    return point;
}