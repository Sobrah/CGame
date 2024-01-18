#include "info.c"


// To Do: Fish Random Out of Board


// Logical Function Prototypes
void InitBoard(void);
void CheckMove(void);
void RefreshFish(Cell *);
void InitScoreBoard(void);
void ProcessMove(Coordinate);
void MoveCharacter(Coordinate, Coordinate);
Coordinate RandCell(Coordinate, int, char);


// Check Board Movements
void CheckMove(void) {
    Coordinate endPoint = (
        ScoreBoard.Users[ScoreBoard.turn].cat.secondary -> point
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


void ProcessMove(Coordinate endPoint) {
    Cell *endCell = &Board[endPoint.y][endPoint.x];
    User *currentUser = &ScoreBoard.Users[ScoreBoard.turn];

    // Process Each Movement
    if (endCell -> primary) {
        
        // Index in the Character Array
        int characterIndex = endCell -> secondary - endCell -> primary -> Characters;

        switch (endCell -> primary -> type) {
            case 'P':
                currentUser -> strength ++;
                break;
            case 'F':
                currentUser -> energy += (
                    characterIndex % SCORE_TYPE_COUNT + 2
                );
                RefreshFish(endCell);
                break;
            case 'M': 
                // Update Score Base on Mouse Index
                currentUser -> score += (
                    characterIndex % SCORE_TYPE_COUNT + 1
                );
                break;
            default: return;
        }
        endCell -> secondary -> inactive = true;
    }

    // Move Character
    Cell catScoreBoard = ScoreBoard.Users[ScoreBoard.turn].cat;

    // Still in Middle Cell
    if (catScoreBoard.secondary -> inactive) { 
        catScoreBoard.secondary -> inactive = false;
    } 

    // Remove from Last Cell
    else {
        Coordinate point = catScoreBoard.secondary -> point;
        Board[point.y][point.x].primary = NULL;
    }
    
    // Move on Character Set
    catScoreBoard.secondary -> point = endPoint;

    // Move on Board
    endCell -> primary = catScoreBoard.primary;
    endCell -> secondary = catScoreBoard.secondary; 
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
    if (fishCount <= USERS_NUMBER) {

        // Revive Fishes
        for (int i = 0; i < fishN; i++) {  
            if (!fishCharacters[i].inactive) continue;
            
            Coordinate point = fishCharacters[i].point;

            // Check Previous Position Status
            if (Board[point.y][point.x].primary) {
                point = RandCell(
                    (Coordinate){point.x - 1, point.y - 1},
                    SCORE_TYPE_COUNT, 'P'
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


// Initialize Score Board
void InitScoreBoard(void) {
    for (int i = 0; i < USERS_NUMBER; i++) {
        ScoreBoard.Users[i] = DEFAULT_USER;
        ScoreBoard.Users[i].cat = (Cell){
            &CharacterSet[i],
            &CharacterSet[i].Characters[0]
        };
    }
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