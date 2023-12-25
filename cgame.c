#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Const Global Variables
#define SIZE 10 // Width & Height of the Board
#define Users 4 // Number of Users

// Global board array
char Board[SIZE][SIZE] = {0};

// Prototypes
void printBoard();

int main(void) {
    // Initialize Seed
    srand(time(NULL));

    // Put User Cats in Board
    for (int i = 0; i < Users; i++) {
        Board[rand() % SIZE][rand() % SIZE] = 'C';
    }

    printBoard();
}

void printBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c  ", Board[i][j] ? Board[i][j] : '0');
        }
        puts("");
    }
}