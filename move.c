#include "logic.c"


// Movements
void CheckMove(void);
void ProcessMove(Coordinate);
void MoveCharacter(Conduct *, Coordinate);
void FindNextTurn(void);
void MoveNPC(void);
void ReviveCharacter(Conduct, Coordinate);

// Face Character
void ConfrontCat(Coordinate);
bool ConfrontDog(Coordinate);
void ConfrontTrap(void);
void RefreshFish(Conduct);


// Check Board Movements
void CheckMove(void) {
    Coordinate endPoint = (
        ScoreBoard.Users[ScoreBoard.turn].userCat.secondary -> point
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
        !ScoreBoard.Users[ScoreBoard.turn].property.energy
    ) FindNextTurn();
}

// Process Each Movement
void ProcessMove(Coordinate endPoint) {
    User *currentUser = &ScoreBoard.Users[ScoreBoard.turn];

    // Facing a Character
    Conduct endConduct = Board[endPoint.y][endPoint.x].route;
    if (endConduct.primary) {
        switch (endConduct.primary -> type) {
            case 'P':
                currentUser -> property.strength ++;
                break;
            case 'F':
                int fishIndex = (
                    endConduct.secondary - endConduct.primary -> Characters
                );
                currentUser -> property.energy += (
                    fishIndex % PROPERTY_LENGTH + DIRECTION_COUNT
                );
                RefreshFish(endConduct);
                break;
            case 'M':
                currentUser -> property.score += (
                    (10 - endConduct.primary -> n) / 2
                );
                currentUser -> Mice[currentUser -> n] = endConduct;
                currentUser -> n ++;
                break;
            case 'T':
                ConfrontTrap();
                endPoint = RadiusRandCell(endPoint); // Cat New Position
                break;
            case 'D':
                if (ConfrontDog(endPoint))
                    endConduct.secondary -> inactive = true;
                else endPoint = RadiusRandCell(endPoint);
                break;
            case 'C':
                ConfrontCat(endPoint);
                break;
            default: return;
        }
    }
    ScoreBoard.walk ++;
    currentUser -> property.energy --;

    // Move Character
    Coordinate point = currentUser -> userCat.secondary -> point;
    Conduct tempConduct, *startConduct = &Board[point.y][point.x].route;

    // Middle Conduct Case
    if (currentUser -> userCat.secondary -> inactive) {
        tempConduct = currentUser -> userCat;
        startConduct = &tempConduct;
        currentUser -> userCat.secondary -> inactive = false;
    }

    MoveCharacter(startConduct, endPoint);
}

// Move Character
void MoveCharacter(Conduct *startConduct, Coordinate endPoint) {
    Conduct *endConduct = &Board[endPoint.y][endPoint.x].route;

    // Remove from Character Set
    if (endConduct -> primary) endConduct -> secondary -> inactive = true;
    
    // Move on Character Set
    startConduct -> secondary -> point = endPoint;

    // Move on Board
    *endConduct = *startConduct;

    // Remove Start Conduct from Board
    startConduct -> primary = NULL;
}

// Find Next Turn Base on Energy
void FindNextTurn(void) {
    ScoreBoard.turn ++;
    ScoreBoard.walk = 0;

    while (true) {
        for (;ScoreBoard.turn < USERS_NUMBER; ScoreBoard.turn ++) {
            if (ScoreBoard.Users[ScoreBoard.turn].property.energy > 0)
                return;
        }

        // Finish Turn
        ScoreBoard.round ++;
        ScoreBoard.turn = 0;

        // Dogs & Mice Movement
        MoveNPC();

        // Increase Every User Energy
        UserProperty *property;
        for (int i = 0; i < USERS_NUMBER; i ++) {
            property = &ScoreBoard.Users[i].property;
            property -> energy ++;

            // End of Freeze
            if (!property -> energy) {
                *property = DEFAULT_USER_PROPERTY;
            }
        }
    }
}

// Move Non-Character Players
void MoveNPC(void) {
    int MAX = 2 * USERS_NUMBER + PROPERTY_LENGTH;

    // Every Category Including Dogs & Mice
    for (int i = USERS_NUMBER; i < MAX; i++) {
        int length = CharacterSet[i].n;

        // Every Character
        for (int j = 0; j < length; j++) {
            if (CharacterSet[i].Characters[j].inactive) continue;

            Coordinate ePoint, sPoint = (
                CharacterSet[i].Characters[j].point
            );
            ePoint = sPoint;

            int speed;
            switch (CharacterSet[i].type) {
                case 'D': speed = Dogs[i - USERS_NUMBER].score; break;
                case 'M': speed = (10 - length) / 2; break;
                default: exit(1); // Unknown Operation
            }
            
            // Every Speed
            for (int k = 0; k < speed; k++) {
                ePoint = RadiusRandCell(sPoint);
                MoveCharacter(&Board[sPoint.y][sPoint.x].route, ePoint);
                
                sPoint = ePoint;
            }
        }
    }
}

// Revive Dead Character
void ReviveCharacter(Conduct character, Coordinate point) {
    point = RadiusRandCell(point);

    // Update Character Position
    *character.secondary = (Character){point, false};
    Board[point.y][point.x].route = character;
}


// Facing Cat
void ConfrontCat(Coordinate endPoint) { 
    User *winner, *loser;
    
    int catIndex = Board[endPoint.y][endPoint.x].route.primary - CharacterSet;
    
    winner = &ScoreBoard.Users[ScoreBoard.turn];
    loser = &ScoreBoard.Users[catIndex];
    
    if (
        loser -> property.energy / loser -> property.strength
        >
        winner -> property.energy / winner -> property.strength
    ) {
        User *tempUser = loser;
        winner = loser;
        loser = tempUser;
    }

    for (int i = 0; i < loser -> n; i ++) {
        winner -> Mice[winner -> n] = loser -> Mice[i];
        winner -> n ++;
        winner -> property.score += (
            (10 - loser -> Mice[i].primary -> n) / 2
        );
    }
    loser -> n = 0;

    int multiply, waste;
    multiply = loser -> property.strength * loser -> property.energy;
    waste = multiply / winner -> property.strength;

    if (waste > winner -> property.energy)
        winner -> property.energy = 1;
    else winner -> property.energy -= waste;
    
    loser -> property = (UserProperty){0, 1, -3};
    *loser -> userCat.secondary = (Character){
        MID_CELL, MID_CELL, true
    };
}

// Facing Dog
bool ConfrontDog(Coordinate endPoint) {
    User *currentUser = &ScoreBoard.Users[ScoreBoard.turn];
    UserProperty *catProperty, *dogProperty;
    
    int dogIndex = Board[endPoint.y][endPoint.x].route.primary - CharacterSet;
    
    catProperty = &currentUser -> property;
    dogProperty = &Dogs[dogIndex - USERS_NUMBER];

    if (
        (float) catProperty -> energy / catProperty -> strength
        >=
        (float) dogProperty -> energy / dogProperty -> strength
    ) {
        int multiply, waste;
        multiply = dogProperty -> strength * dogProperty -> energy;
        waste = multiply / catProperty -> strength;
        
        // Reduce Cat Energy
        if (waste > catProperty -> energy) 
            catProperty -> energy = 1; // Become Zero Later
        else catProperty -> energy -= waste;

        return true;
    } else {
        int multiply, waste;
        multiply = catProperty -> strength * catProperty -> energy;
        waste = multiply / dogProperty -> strength;

        dogProperty -> energy -= waste;

        for (int i = 0; i < currentUser -> n; i++) {
            ReviveCharacter(currentUser -> Mice[i], endPoint);
        }
        currentUser -> n = 0;
        *catProperty = (UserProperty){0, 1, -3};

        return false;
    }
}

// Facing Trap
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
        if (currentUser -> Mice[i].primary -> n < currentUser -> Mice[maxIndex].primary -> n)
            maxIndex = i;
    }

    // Return Mouse to Board
    ReviveCharacter(
        currentUser -> Mice[maxIndex],
        currentUser -> Mice[maxIndex].secondary -> point
    );

    // Reduce Score
    currentUser -> property.score -= (
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
    int fishN = fishConduct.primary -> n;

    for (int i = 0; i < fishN; i++) {
        if (!fishCharacters[i].inactive) fishCount ++;
    }

    // Reset Fishes
    if (fishCount < USERS_NUMBER) {

        // Revive Fishes
        for (int i = 0; i < fishN; i++) {
            if (!fishCharacters[i].inactive) continue;

            ReviveCharacter(
                (Conduct){fishConduct.primary, fishCharacters + i},
                fishCharacters[i].point
            );
        }
    }
}
