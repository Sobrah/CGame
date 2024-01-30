#include "graphic.c"


void new(void) {

    // Reset Board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Board[i][j] = (Cell){};
        }
    }

    // Reset Character Set
    for (int i = 0; i < USERS_NUMBER; i++) {
        int length = CharacterSet[i].n;
        
        for (int j = 0; j < length; j++) {
            CharacterSet[i].Characters[j] = DEFAULT_CAT;
        }
    }
    InitBoard(BOARD_SIZE);

    // Reset Score Board
    ScoreBoard.round = ScoreBoard.turn = ScoreBoard.walk = 0;
    for (int i = 0; i < USERS_NUMBER; i++) {
        ScoreBoard.Users[i] = (User){DEFAULT_PROPERTY};
    }

    // Reset Dogs
    for (int i = 0; i < DOGS_NUMBER; i++) {
        Dogs[i] = DEFAULT_DOGS[i];
    }
}