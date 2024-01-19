#include "info.c"


// For Random Functionality
#include <stdlib.h>
#include <time.h>


// To Do: RandCell Return Coordinate Out of Board


// Logical Function Prototypes
void InitBoard(void);
void CheckMove(void);
void RefreshFish(Cell);
void InitScoreBoard(void);
void ReviveCharacter(Cell);
void ProcessMove(Coordinate);
Coordinate ConfrontTrap(Coordinate);
void MoveCharacter(Coordinate, Coordinate);
Coordinate RandCell(Coordinate, int, char);


void ConfrontCat(Coordinate endPoint) {
    User *currentUser = &ScoreBoard.Users[ScoreBoard.turn];
    User *secondUser;

    // Find the Second Cat
    int i;
    for (i = 0; i < USERS_NUMBER; i++) {
        if (
            ScoreBoard.Users[i].cat.secondary -> point.x == currentUser -> cat.secondary -> point.x
            &&
            ScoreBoard.Users[i].cat.secondary -> point.y == currentUser -> cat.secondary -> point.y
        ) break;
    }
    secondUser = &ScoreBoard.Users[i];

    if (currentUser -> strength / currentUser -> energy > secondUser -> strength / secondUser -> energy) {
        for (;secondUser -> counter > 0; secondUser -> counter --, currentUser -> counter ++) {
            currentUser -> mice[currentUser -> counter] = secondUser -> mice[secondUser -> counter];
        }
    }
}


void ProcessMove(Coordinate endPoint) {
    Cell *endCell = &Board[endPoint.y][endPoint.x];
    User *currentUser = &ScoreBoard.Users[ScoreBoard.turn];

    // Process Each Movement
    if (endCell -> primary) {
        switch (endCell -> primary -> type) {
            case 'P':
                currentUser -> strength ++;
                endCell -> secondary -> inactive = true;
                break;
            case 'F':
                // Index in the Character Array
                int fishIndex = (
                    endCell -> secondary - endCell -> primary -> Characters
                );
                currentUser -> energy += (
                    fishIndex % SCORE_TYPE_COUNT + 2
                );
                RefreshFish(*endCell);
                endCell -> secondary -> inactive = true;
                break;
            case 'M':
                currentUser -> score += (
                    (10 - endCell -> primary -> n) / 2
                );
                currentUser -> mice[currentUser -> counter] = *endCell;
                currentUser -> counter ++;
                endCell -> secondary -> inactive = true;
                break;
            case 'T':
                endPoint = ConfrontTrap(endPoint);
                endCell = &Board[endPoint.y][endPoint.x];
                break;
            case 'C':
                ConfrontCat(endPoint);
                break;
            default: return;
        }
    }

    // Move Character
    Cell userCat = ScoreBoard.Users[ScoreBoard.turn].cat;

    // Still in Middle Cell
    if (userCat.secondary -> inactive) { 
        userCat.secondary -> inactive = false;
    } 

    // Remove from Last Cell
    else {
        Coordinate point = userCat.secondary -> point;
        Board[point.y][point.x].primary = NULL;
    }
    
    // Move on Character Set
    userCat.secondary -> point = endPoint;

    // Move on Board
    endCell -> primary = userCat.primary;
    endCell -> secondary = userCat.secondary; 
}


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


Coordinate ConfrontTrap(Coordinate endPoint) {
    User *currentUser = &ScoreBoard.Users[ScoreBoard.turn];
    
    // No Mouse to Release
    if (!currentUser -> counter) {
        if (currentUser -> strength > 2) 
            currentUser -> strength -= 2;
        else 
            currentUser -> energy -= 3;
    } else {
        int maxIndex = 0;
        for (int i = 1; i < currentUser -> counter; i++) {
            if (currentUser -> mice[i].primary -> n < currentUser -> mice[maxIndex].primary -> n)
                maxIndex = i;
        }

        // Return Mouse to Board
        ReviveCharacter(currentUser -> mice[maxIndex]);

        // Reduce Score
        currentUser -> score -= (
            (10 - currentUser -> mice[maxIndex].primary -> n) / 2
        );

        // Remove from Eaten Mice
        currentUser -> counter --;
        currentUser -> mice[maxIndex] = currentUser -> mice[currentUser -> counter];
    }

    // New Cat Position
    return RandCell(
        (Coordinate){endPoint.x - 1, endPoint.y - 1},
        SCORE_TYPE_COUNT, 'P'
    );
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
                (Cell){fishCell.primary, fishCharacters + i}
            );
        }
    }
}


// Revive Dead Character
void ReviveCharacter(Cell character) {
    Coordinate point = character.secondary -> point; 

    // Check Previous Position Status
    if (Board[point.y][point.x].primary) {
                
        // Random Cell Around Previous Position
        point = RandCell(
            (Coordinate){point.x - 1, point.y - 1},
            SCORE_TYPE_COUNT, 'P'
        );
    }

    // Update Character Position
    character.secondary -> point = point;
    character.secondary -> inactive = false;
    Board[point.y][point.x].primary = character.primary;
    Board[point.y][point.x].secondary = character.secondary;
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