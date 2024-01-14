#include "info.c"

// To Do: Fish Random Out of Board

// Logical Function Prototypes
void InitBoard(void);
void CheckMove(void);
void RefreshFish(Cell *);
void ProcessMove(Coordinate, Coordinate);
void MoveCharacter(Coordinate, Coordinate);
Coordinate RandCell(Coordinate, int, char);


// Check Board Movements
void CheckMove(void) {
    Coordinate catPoint, endPoint;
    endPoint = catPoint = (
        CharacterSet[ScoreBoard.turn].Characters[0].point
    );

    // Processing Pressed Key
    switch (GetKeyPressed()) {
        case KEY_NULL: return;
        case KEY_UP:
            if (Board[catPoint.y][catPoint.x].wall == NORTH) return;
            endPoint.y --; break;
        case KEY_LEFT:
            if (Board[catPoint.y][catPoint.x].wall == WEST) return;
            endPoint.x --; break;
        case KEY_DOWN:
            if (Board[catPoint.y + 1][catPoint.x].wall == NORTH) return;
            endPoint.y ++; break;
        case KEY_RIGHT:
            if (Board[catPoint.y][catPoint.x + 1].wall == WEST) return;
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
 
    ProcessMove(catPoint, endPoint);
}


void ProcessMove(Coordinate catPoint, Coordinate endPoint) {
    Cell *catCell = &Board[catPoint.y][catPoint.x];
    Cell *endCell = &Board[endPoint.y][endPoint.x];
    User *currentUser = &ScoreBoard.Users[ScoreBoard.turn];

    // Process Each Movement
    if (endCell -> primary) {
        switch (endCell -> primary -> type) {
            case 'P':
                endCell -> secondary -> inactive = true;
                currentUser -> strength ++; break;
            case 'F':
                endCell -> secondary -> inactive = true;
                
                // Update Score Base on Fish Index
                currentUser -> energy += (
                    (endCell -> secondary - endCell -> primary -> Characters) %3 + 2
                );

                RefreshFish(endCell);
                break;
            case 'M': 
                endCell -> secondary -> inactive = true;
                currentUser -> score ++; break;
            default: return;
        }
    }

    // Move on Character Set
    catCell -> secondary -> point = endPoint;

    // Move on Board
    endCell -> primary = catCell -> primary;
    endCell -> secondary = catCell -> secondary;

    // Remove from Last Cell
    catCell -> primary = NULL;
}

// User's Cat Faces Fish
void RefreshFish(Cell *fishCell) {    
    Character *fishCharacters = fishCell -> primary -> Characters;

    // Count Active Fishes
    int fishCount = 0;
    int fishN = fishCell -> primary -> n;

    for (int i = 0; i < fishN; i++) {
        if (!fishCharacters[i].inactive) fishCount ++;
    }
            
    // Reset Fishes
    if (fishCount < USERS_NUMBER) {

        // Revive Fishes
        for (int i = 0; i < fishN; i++) {  
            if (!fishCharacters[i].inactive) continue;
            
            Coordinate point = fishCharacters[i].point;

            // Check Previous Position Status
            if (Board[point.y][point.x].primary) {
                point = RandCell(
                    (Coordinate){point.x - 1, point.y - 1}, 3, 'P'
                );
            }

            // Update Fish Position
            fishCharacters[i] = (Character){point};
            Board[point.y][point.x].primary = fishCell -> primary;
            Board[point.y][point.x].secondary = &fishCharacters[i];
        }
    }
}


// Find Empty Cell Base On Wall Or Primary
Coordinate RandCell(Coordinate start, int range, char factor) {
    int x, y;
    bool value;

    do {
        x = rand() % range + start.x;
        y = rand() % range + start.y;

        switch (factor) {
            case 'P': value = Board[y][x].primary; break;
            case 'W': value = Board[y][x].wall; break;
        }
    } while(value);

    return (Coordinate){x, y};
}

// Initialize Board
void InitBoard(void) {
    for (int i = 0; i < SET_LENGTH; i++) {
        for (int j = 0; j < CharacterSet[i].n; j++) {            
            Coordinate *point = &CharacterSet[i].Characters[j].point;

            if (!CharacterSet[i].fix) 
                *point = RandCell((Coordinate){0, 0}, BOARD_SIZE, 'P');

            Board[point -> y][point -> x] = (Cell){
                &CharacterSet[i], &CharacterSet[i].Characters[j]
            };
        }
    }

    // Initialize Walls
    for (int i = 0; i < BOARD_SIZE; i++) {
        
        // Zero Is Not Valid
        Coordinate point = RandCell((Coordinate){1, 1}, BOARD_SIZE - 1, 'W');
        
        Board[point.y][point.x].wall = (
            rand() % DIRECTION_COUNT ? WEST : NORTH
        );
    }
}