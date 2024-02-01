#include "cgame.h"


// Movements
void CheckMove(void);
void ProcessMove(Coordinate);
void MoveCharacter(Conduct *, Coordinate);
void FindNextTurn(void);
void MoveNPC(void);

// Face Character
bool ConfrontCat(Coordinate);
bool ConfrontDog(Coordinate);
void ConfrontTrap(void);
void RefreshFish(Conduct);


// Check Board Movements
void CheckMove(void) {
    Coordinate endPoint = (
        ScoreBoard.Users[ScoreBoard.turn].cat.secondary -> point
    );

    // Processing Pressed Key
    switch (GetKeyPressed()) {
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
            FindNextTurn();
        default: return;
    }

    // Check Board Limit
    if (
        endPoint.x < 0 || endPoint.x >= BOARD_SIZE
        ||
        endPoint.y < 0 || endPoint.y >= BOARD_SIZE
    ) return;

    ProcessMove(endPoint);
    
    if (
        ScoreBoard.walk == PROPERTY_LENGTH 
        || 
        ScoreBoard.Users[ScoreBoard.turn].feature.energy <= 0
    ) FindNextTurn();
}

// Process Each Movement
void ProcessMove(Coordinate endPoint) {
    User *currentUser = &ScoreBoard.Users[ScoreBoard.turn];

    ScoreBoard.walk ++;
    currentUser -> feature.energy --;

    // Facing a Character
    Conduct endConduct = Board[endPoint.y][endPoint.x].route;

    if (endConduct.primary) switch (endConduct.primary -> type) {
        case 'P':
            currentUser -> feature.strength ++;
            break;
        case 'F':
            int fishIndex = (
                endConduct.secondary - endConduct.primary -> Characters
            );
            currentUser -> feature.energy += (
                fishIndex % PROPERTY_LENGTH + DIRECTION_COUNT
            );
            RefreshFish(endConduct);
            break;
        case 'M':
            currentUser -> feature.score += (
                (10 - endConduct.primary -> n) / 2
            );
            currentUser -> Mice[currentUser -> n ++] = endConduct;
            break;
        case 'T':
            ConfrontTrap();
            endPoint = RadiusRandCell(endPoint); // User New Position
            break;
        case 'D':
            if (!ConfrontDog(endPoint))
                endPoint = RadiusRandCell(endPoint);
            break;
        case 'C':
            if (!ConfrontCat(endPoint))
                endPoint = RadiusRandCell(endPoint);
            break;
        default:
            ScoreBoard.walk --;
            currentUser -> feature.energy ++;
            return;
    }

    // Move Character
    Coordinate sPoint = currentUser -> cat.secondary -> point;
    Conduct *startConduct = &Board[sPoint.y][sPoint.x].route;

    // Middle Cell Case
    if (currentUser -> cat.secondary -> inactive) {
        startConduct = &currentUser -> cat;
        currentUser -> cat.secondary -> inactive = false;
    }

    MoveCharacter(startConduct, endPoint);
}

// Move Character
void MoveCharacter(Conduct *sConduct, Coordinate ePoint) {
    Conduct *endConduct = &Board[ePoint.y][ePoint.x].route;

    // Remove from Character Set
    if (endConduct -> primary) endConduct -> secondary -> inactive = true;
    
    // Move on Character Set
    sConduct -> secondary -> point = ePoint;

    // Move on Board
    *endConduct = *sConduct;

    // Remove Start Conduct from Board
    if (
        sConduct >= &Board[0][0].route
        &&
        sConduct <= &Board[14][14].route
    ) sConduct -> primary = NULL;
}

// Find Next Turn Base on Energy
void FindNextTurn(void) {
    ScoreBoard.turn ++;
    ScoreBoard.walk = 0;

    while (true) {
        for (; ScoreBoard.turn < USERS_NUMBER; ScoreBoard.turn ++) {
            if (ScoreBoard.Users[ScoreBoard.turn].feature.energy > 0)
                return;
        }

        // Finish Turn
        if (ScoreBoard.round == BOARD_SIZE) {
            ScreenState = WIN;
            return;
        }

        ScoreBoard.round ++;
        ScoreBoard.turn = 0;

        // Dogs & Mice Movement
        MoveNPC();

        // Increase Every User Energy
        UserProperty *property;
        for (int i = 0; i < USERS_NUMBER; i ++) {
            property = &ScoreBoard.Users[i].feature;
            property -> energy ++;

            // End of Freeze
            if (!property -> energy) *property = DEFAULT_PROPERTY;
        }
    }
}

// Move Non-Player Characters
void MoveNPC(void) {
    int MAX = USERS_NUMBER + DOGS_NUMBER + PROPERTY_LENGTH;

    // Move Dogs & Mice
    for (int i = USERS_NUMBER; i < MAX; i++) {
        for (int j = 0; j < CharacterSet[i].n; j++) {
            if (CharacterSet[i].Characters[j].inactive) continue;

            Coordinate ePoint, sPoint = (
                CharacterSet[i].Characters[j].point
            ); ePoint = sPoint;

            int speed;
            switch (CharacterSet[i].type) {
                case 'D': speed = Dogs[i - USERS_NUMBER].score; break;
                case 'M': speed = (10 - CharacterSet[i].n) / 2; break;
                default: exit(1); // Unknown Operation
            }
            
            // Every Speed
            for (int k = 0; k < speed; k++) {
                ePoint = RadiusRandCell(sPoint);
                MoveCharacter(
                    &Board[sPoint.y][sPoint.x].route, ePoint
                );
                sPoint = ePoint;
            }
        }
    }
}

// Facing Cat
bool ConfrontCat(Coordinate endPoint) { 
    User *winner, *loser;
    
    int catIndex = (
        Board[endPoint.y][endPoint.x].route.primary - CharacterSet
    );
    winner = ScoreBoard.Users + ScoreBoard.turn;
    loser = ScoreBoard.Users + catIndex;
    
    bool status = true;
    if (
        (float) loser -> feature.energy / loser -> feature.strength
        >
        (float) winner -> feature.energy / winner -> feature.strength
    ) {
        User *swapUser = winner;
        winner = loser;
        loser = swapUser;
        status = false;
    }

    // Lose Mice
    for (; loser -> n > 0; loser -> n --) {
        winner -> Mice[winner -> n ++] = loser -> Mice[loser -> n];
    }
    winner -> feature.score += loser -> feature.score;

    // Lose Winner Energy
    int multiply = loser -> feature.strength * loser -> feature.energy;
    winner -> feature.energy -= multiply / winner -> feature.strength;
    
    if (winner -> feature.energy < 0) winner -> feature.energy = 0;
    
    // Freeze Loser
    loser -> feature = (UserProperty){0, 1, -3};
    
    // Move Loser
    if (status) MoveCharacter(
        &Board[endPoint.y][endPoint.x].route, RadiusRandCell(endPoint)
    );

    return status;
}

// Facing Dog
bool ConfrontDog(Coordinate endPoint) {
    UserProperty *winner, *loser;

    int dogIndex = (
        Board[endPoint.y][endPoint.x].route.primary - CharacterSet
    );
    winner = &ScoreBoard.Users[ScoreBoard.turn].feature;
    loser = Dogs + dogIndex;

    bool status = true;
    if (
        (float) loser -> energy / loser -> strength
        >
        (float) winner -> energy / winner -> strength
    ) {
        UserProperty *swapProperty = winner;
        winner = loser;
        loser = swapProperty;
        status = false;
    }

    // Reduce Winner Energy
    int multiply = loser -> strength * loser -> energy;
    winner -> energy -= multiply / winner -> strength;

    if (winner -> energy < 0) winner -> energy = 0;

    if (!status) {
        User *currentUser = ScoreBoard.Users + ScoreBoard.turn;
        for (int i = 0; i < currentUser -> n; i++) {
            MoveCharacter(
                currentUser -> Mice + i, RadiusRandCell(endPoint)
            );
        }
        currentUser -> n = 0;
        currentUser -> feature = (UserProperty){0, 1, -3};
    }

    return status;
}

// Facing Trap
void ConfrontTrap(void) {
    User *currentUser = &ScoreBoard.Users[ScoreBoard.turn];

    // No Mouse to Release
    if (!currentUser -> n) {
        if (currentUser -> feature.strength > 2)
            currentUser -> feature.strength -= 2;
        else
            if (currentUser -> feature.energy -= 3 < 0) {
                currentUser -> feature.energy = 0;
            }
        return;
    }

    // Find Best Mouse
    int maxIndex = 0;
    for (int i = 1; i < currentUser -> n; i++) {
        if (
            currentUser -> Mice[i].primary -> n
            <
            currentUser -> Mice[maxIndex].primary -> n
        ) maxIndex = i;
    }

    // Return Mouse to Board
    Coordinate point = currentUser -> Mice[maxIndex].secondary -> point;
    MoveCharacter(
        currentUser -> Mice + maxIndex, RadiusRandCell(point)
    );

    // Reduce Score
    currentUser -> feature.score -= (
        (10 - currentUser -> Mice[maxIndex].primary -> n) / 2
    );

    // Remove from Eaten Mice
    currentUser -> n --;
    currentUser -> Mice[maxIndex] = currentUser -> Mice[currentUser -> n];
}

// Check Fish Number Status
void RefreshFish(Conduct fishConduct) {
    Character *fishCharacters = fishConduct.primary -> Characters;

    // Count Active Fishes
    int fishCount = 0;
    for (int i = 0; i < fishConduct.primary -> n; i++) {
        if (!fishCharacters[i].inactive) fishCount ++;
    }

    // Reset Fishes
    if (fishCount < USERS_NUMBER) {
        for (int i = 0; i < fishConduct.primary -> n; i++) {
            if (!fishCharacters[i].inactive) continue;

            Conduct fish = {
                fishConduct.primary, fishCharacters + i
            };
            MoveCharacter(&fish, fishCharacters[i].point);
        }
    }
}
