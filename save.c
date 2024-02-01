#include "cgame.h"

#include <stdio.h>


// Converts Pointers to Indexes
Coordinate Poindex(Conduct route) {
    int primary, secondary;

    primary = route.primary - CharacterSet;
    secondary = route.secondary - CharacterSet[primary].Characters;

    return (Coordinate){primary, secondary};
}

// Converts Indexes to Points
Conduct Inpoint(Coordinate point) {
    return (Conduct){
        CharacterSet + point.x,
        CharacterSet[point.x].Characters + point.y
    };
}


// Save Game State
void Save(void) {
    if (!ScoreBoard.Users[ScoreBoard.turn].cat.primary) return;

    FILE *file = fopen("Data/save", "wb");

    // File Error
    if (!file) return;
    
    // Save Character Set
    for (int i = 0; i < SET_LENGTH; i++) {
        fwrite(
            CharacterSet[i].Characters,
            sizeof(Character),
            CharacterSet[i].n,
            file
        );
    }

    // Save Score Board
    fwrite(&ScoreBoard.round, sizeof(int), 3, file); // Round, Turn, Walk

    for (int i = 0; i < USERS_NUMBER; i++) {
        fwrite(&ScoreBoard.Users[i].feature, sizeof(UserProperty), 1, file);

        Coordinate catPoint = Poindex(ScoreBoard.Users[i].cat);
        fwrite(&catPoint, sizeof(Coordinate), 1, file);

        int miceN = ScoreBoard.Users[i].n;
        fwrite(&miceN, sizeof(int), 1, file);

        for (int j = 0; j < miceN; j++) {
            Coordinate ratPoint = Poindex(
                ScoreBoard.Users[i].Mice[j]
            );
            fwrite(&ratPoint, sizeof(Coordinate), 1, file);
        }
    }

    // Save Dogs
    fwrite(Dogs, sizeof(UserProperty), DOGS_NUMBER, file);

    // Save Walls
    fwrite(Walls, sizeof(Wall), BOARD_SIZE, file);

    fclose(file);
}

// Load Game State
void Load(void) {
    FILE *file = fopen("Data/save", "rb");

    // File Error
    if (!file) return;

    // Empty Board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Board[i][j] = (Cell){};
        }
    }

    // Load Character Set
    for (int i = 0; i < SET_LENGTH; i++) {
        fread(
            CharacterSet[i].Characters,
            sizeof(Character),
            CharacterSet[i].n,
            file
        );
        
        // Add Characters to Board
        for (int j = 0; j < CharacterSet[i].n; j++) {
            if (CharacterSet[i].Characters[j].inactive) continue;
            
            Coordinate point = CharacterSet[i].Characters[j].point;
            Board[point.y][point.x].route = (Conduct){
                CharacterSet + i,
                CharacterSet[i].Characters + j
            };
        }
    }


    // Load Score Board
    fread(&ScoreBoard.round, sizeof(int), 3, file); // Round, Turn, Walk

    for (int i = 0; i < USERS_NUMBER; i++) {
        fread(&ScoreBoard.Users[i].feature, sizeof(UserProperty), 1, file);
        
        Coordinate catPoint;
        fread(&catPoint, sizeof(Coordinate), 1, file);
        ScoreBoard.Users[i].cat = Inpoint(catPoint);

        int miceN;
        fread(&miceN, sizeof(int), 1, file);
        ScoreBoard.Users[i].n = miceN;

        for (int j = 0; j < miceN; j++) {
            Coordinate ratPoint;
            fread(&ratPoint, sizeof(Coordinate), 1, file);
            ScoreBoard.Users[i].Mice[j] = Inpoint(ratPoint);
        }
    }

    // Save Dogs
    fread(Dogs, sizeof(UserProperty), DOGS_NUMBER, file);

    // Save Walls
    fread(Walls, sizeof(Wall), BOARD_SIZE, file);
    for (int i = 0; i < BOARD_SIZE; i++) {
        Coordinate point = Walls[i].point;
        
        Board[point.y][point.x].wall = Walls[i].wall;
    }

    fclose(file);
}