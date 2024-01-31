#include "cgame.h"


// Game Board
Cell Board[BOARD_SIZE][BOARD_SIZE];
Wall Walls[BOARD_SIZE];

// Character Categories Storage
CharacterType CharacterSet[] = {
    
    // Cats
    {'C', {"Purple Cat.svg"}, 1, true},
    {'C', {"Green Cat.svg"}, 1, true},
    {'C', {"Blue Cat.svg"}, 1, true},
    {'C', {"Yellow Cat.svg"}, 1, true},
    
    // Dogs
    {'D', {"Poodle.svg"}, 1},
    {'D', {"Dog.svg"}, 1},
    {'D', {"Fox.svg"}, 1},
    {'D', {"Wolf.svg"}, 1},
    
    // Mice
    {'M', {"White Mouse.svg"}, 8},
    {'M', {"Blue Mouse.svg"}, 6},
    {'M', {"Purple Mouse.svg"}, 4},

    // House
    {'H', {"House.svg"}, 1, true,
        {MID_CELL, MID_CELL}
    },

    // Traps, Fish & Chocolates
    {'T', {"Trap.svg"}, 8},
    {'F', {"Fish.svg"}, 10},
    {'P', {"Chocolate.svg"}, 8}
};
const Character DEFAULT_CAT = {MID_CELL, MID_CELL, true};

// Score Board Information
ScoreType ScoreBoard = {
    {{"Score.svg"}, {"Strength.svg"}, {"Energy.svg"}}
};
const UserProperty DEFAULT_PROPERTY = {0, 2, 5};

// Dogs Information
const UserProperty DEFAULT_DOGS[] = {
    {5, 5, 30},
    {2, 2, 15},
    {3, 2, 20},
    {1, 1, 5}
};
UserProperty Dogs[USERS_NUMBER];

// Initialize Board
void InitBoard() {
    Coordinate finish = {
        BOARD_SIZE - 1,
        BOARD_SIZE - 1
    }, startZero = {0, 0}, startOne = {1, 1};
    
    // Initialize Characters
    for (int i = 0; i < SET_LENGTH; i++) {
        for (int j = 0; j < CharacterSet[i].n; j++) {            
            Coordinate *point = &CharacterSet[i].Characters[j].point;

            if (!CharacterSet[i].fix) 
                *point = RandCell(startZero, finish, 'P');

            // Add to Board
            Board[point -> y][point -> x].route = (Conduct){
                CharacterSet + i, 
                CharacterSet[i].Characters + j
            };
        }
    }

    // Initialize Walls _ Zero Is Not Valid
    for (int i = 0; i < BOARD_SIZE; i++) {
        Coordinate point; Direction side;
        Walls[i] = (Wall){
            point = RandCell(startOne, finish, 'W'),
            side = rand() % DIRECTION_COUNT ? WEST : NORTH
        };
        Board[point.y][point.x].wall = side;
    }
}

// Start New
void New(void) {

    // Reset Board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Board[i][j] = (Cell){};
        }
    }

    // Reset Cats Positions
    for (int i = 0; i < USERS_NUMBER; i++) {
        for (int j = 0; j < CharacterSet[i].n; j++) {
            CharacterSet[i].Characters[j] = DEFAULT_CAT;
        }
    }

    // Reset Character Set
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