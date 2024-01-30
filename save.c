#include "logic.c"

Coordinate CtoC(Conduct route) {
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
        Coordinate cat = CtoC(ScoreBoard.Users[i].cat);
        fwrite(&cat, sizeof(Coordinate), 1, file);
        int n = ScoreBoard.Users[i].n;
        fwrite(&n, sizeof(int), 1, file);
        for (int j = 0; j < n; j++) {
            Coordinate rat = CtoC(ScoreBoard.Users[i].Mice[j]);
            fwrite(&rat, sizeof(Coordinate), 1, file);
        }
    }

    // Save Dogs
    fwrite(Dogs, sizeof(UserProperty), DOGS_NUMBER, file);

    // Save Walls
    fwrite(Walls, sizeof(WallType), BOARD_SIZE, file);

    fclose(file);
}