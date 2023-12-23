#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Const Global Variables
#define SIZE 5 // Width & Height of the Board
#define Users 2 // Number of Users

// Global board array
char Board[SIZE][SIZE] = {0};

// Prototypes
void printBoard();

int main(void) {
    // Initialize Seed
    srandom(time(NULL));

    // Put User Cats in Board
    for (int i = 0; i < Users; i++) {
        Board[random() % SIZE][random() % SIZE] = 'C';
    }

    printBoard();
}

void printBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c\t", Board[i][j] ? Board[i][j] : '0');
        }
        puts("");
    }
}