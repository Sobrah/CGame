#include "logic.c"

Coordinate CondToCoor(Conduct route) {
    int primary, secondary;
    primary = route.primary - CharacterSet;
    secondary = route.secondary - CharacterSet[primary].Characters;

    return (Coordinate){primary, secondary};
}

void save(void) {
    FILE *file = fopen("Data/save", "wb");
    
    // Save Character Set
    for (int i = 0; i < SET_LENGTH; i++) {
        fwrite(CharacterSet + i, sizeof(Character), CharacterSet[i].n, file);
    }

    // Save Score Board
    fwrite(&ScoreBoard, sizeof(int), 3, file);
    for (int i = 0; i < USERS_NUMBER; i++) {
        fwrite(&ScoreBoard.Users[i].feature, sizeof(UserProperty), 1, file);
        Coordinate cat = CondToCoor(ScoreBoard.Users[i].cat);
        fwrite(&cat, sizeof(Coordinate), 1, file);
        int n = ScoreBoard.Users[i].n;
        fwrite(&n, sizeof(int), 1, file);
        for (int j = 0; j < n; j++) {
            Coordinate rat = CondToCoor(ScoreBoard.Users[i].Mice[j]);
            fwrite(&rat, sizeof(Coordinate), 1, file);
        }
    }

    // Save Dogs
    fwrite(Dogs, sizeof(UserProperty), DOGS_NUMBER, file);

    // Save Walls
    fwrite(Walls, sizeof(WallType), BOARD_SIZE, file);

    fclose(file);
}

void load(void) {
    FILE *file = fopen("Data/save", "rb");

    // Empty Board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Board[i][j] = (Cell){};
        }
    }

    // Load Character Set
    for (int i = 0; i < SET_LENGTH; i++) {
        fread(CharacterSet + i, sizeof(Character), CharacterSet[i].n, file);
        
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
    fread(&ScoreBoard, sizeof(int), 3, file);
    for (int i = 0; i < USERS_NUMBER; i++) {
        fread(&ScoreBoard.Users[i].feature, sizeof(UserProperty), 1, file);
        
        Coordinate cat;
        fread(&cat, sizeof(Coordinate), 1, file);

        ScoreBoard.Users[i].cat = (Conduct) {
            CharacterSet + cat.x,
            CharacterSet[cat.x].Characters + cat.y
        };

        int n;
        fread(&n, sizeof(int), 1, file);

        ScoreBoard.Users[i].n = n;

        for (int j = 0; j < n; j++) {
            Coordinate rat;
            fread(&rat, sizeof(Coordinate), 1, file);

            ScoreBoard.Users[i].Mice[j] = (Conduct){
                CharacterSet + rat.x,
                CharacterSet[rat.x].Characters + rat.y
            };
        }
    }

    // Save Dogs
    fread(Dogs, sizeof(UserProperty), DOGS_NUMBER, file);

    // Save Walls
    fread(Walls, sizeof(WallType), BOARD_SIZE, file);
    for (int i = 0; i < BOARD_SIZE; i++) {
        Coordinate point = Walls[i].point;
        Board[point.y][point.x].wall = Walls[i].wall;
    }

    fclose(file);
}