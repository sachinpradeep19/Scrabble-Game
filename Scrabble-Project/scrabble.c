#include "scrabble.h"
#include "random.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define NUM_TILES 98

// Global game board and tile bag
char board[BOARD_SIZE][BOARD_SIZE] = {{0}};
char bag[NUM_TILES];
unsigned int tilesInBag = 0;

// Points and counts for each letter, in A-Z order
const int letterPoints[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
const int letterTiles[26] = {9, 2, 2, 4, 12, 2, 3, 2, 9, 1, 1, 4, 2, 6, 8, 2, 1, 6, 4, 6, 4, 2, 2, 1, 2, 1};

const char *dictionaryFileName; // Name of the dictionary file

// Initialize the game by setting up the board, filling the bag, and loading the dictionary
int scrabbleInit(const char* filename) {
    dictionaryFileName = filename;

    // Clear the board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = '\0';
        }
    }

    // Fill the bag with tiles based on letter frequency
    tilesInBag = 0;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < letterTiles[i]; j++) {
            bag[tilesInBag++] = 'a' + i;
        }
    }

    // Shuffle the tiles
    mixBag();

    // Verify dictionary file access
    FILE *file = fopen(dictionaryFileName, "r");
    if (file == NULL) {
        return -1;  // Couldn't open file
    }
    fclose(file);
    return 0;  // Initialization successful
}

// Choose tiles from the bag to fill the player's rack
int chooseTiles(char rack[]) {
    int count = 0;
    for (int i = 0; i < RACK_SIZE && tilesInBag > 0; i++) {
        if (rack[i] == '\0') {
            rack[i] = bag[--tilesInBag];  // Take a tile from the bag
            count++;
        }
    }
    return count;
}

// Check if the given selection can be created using tiles from the rack
int checkTiles(const char *selection, const char rack[]) {
    int rackCount[26] = {0};
    for (int i = 0; i < RACK_SIZE; i++) {
        if (rack[i] != '\0') {
            rackCount[rack[i] - 'a']++;
        }
    }

    for (const char *p = selection; *p; p++) {
        if (--rackCount[*p - 'a'] < 0) {
            return 0;  // Not enough tiles for the selection
        }
    }
    return 1;
}

// Calculate the score of a word
int scoreWord(const char *word) {
    int score = 0;
    for (const char *p = word; *p; p++) {
        score += letterPoints[*p - 'a'];
    }
    return score;
}

// Check if a word exists in the dictionary
int findInDictionary(const char *word) {
    FILE *file = fopen(dictionaryFileName, "r");
    if (file == NULL) {
        return 0;  // Dictionary not accessible
    }

    char line[16];
    while (fscanf(file, "%15s", line) == 1) {
        if (strcmp(word, line) == 0) {
            fclose(file);
            return 1;  // Word found
        }
    }
    fclose(file);
    return 0;  // Word not found
}

// Build a word by placing tiles at (row, col) in the specified direction
int buildWord(const char *selection, unsigned int row, unsigned int col, unsigned int dir, char *testWord) {
    int len = strlen(selection);
    if ((dir == 0 && col + len > BOARD_SIZE) || (dir == 1 && row + len > BOARD_SIZE)) {
        testWord[0] = '\0';  // Out of bounds
        return -1;
    }

    int index = 0;
    for (int i = 0; i < len; i++) {
        testWord[index++] = (dir == 0) ? (board[row][col + i] ? board[row][col + i] : selection[i]) : (board[row + i][col] ? board[row + i][col] : selection[i]);
    }
    testWord[index] = '\0';  // Null-terminate the test word
    return index;
}

// Place tiles on the board and update the player's rack
void placeWord(const char *selection, unsigned int row, unsigned int col, unsigned int dir, char rack[]) {
    for (int i = 0; selection[i] != '\0'; i++) {
        if (dir == 0) {
            board[row][col + i] = selection[i];
        } else {
            board[row + i][col] = selection[i];
        }

        // Remove the used tile from the rack
        for (int j = 0; j < RACK_SIZE; j++) {
            if (rack[j] == selection[i]) {
                rack[j] = '\0';
                break;
            }
        }
    }
}

// Remove selected tiles from the rack and refill it from the bag
void discardTiles(const char *selection, char rack[]) {
    for (const char *p = selection; *p; p++) {
        for (int i = 0; i < RACK_SIZE; i++) {
            if (rack[i] == *p) {
                rack[i] = '\0';  // Discard tile
                break;
            }
        }
    }
    chooseTiles(rack);  // Refill the rack
}

// Check if the board is empty (used for the first move)
int isBoardEmpty() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j]) return 0;  // Found a non-empty spot
        }
    }
    return 1;  // Board is empty
}

// Shuffle the tiles in the bag
void mixBag() {
    for (unsigned int i = tilesInBag - 1; i >= 1; i--) {
        unsigned int j = getRandom(i + 1);
        char tmp = bag[i];
        bag[i] = bag[j];
        bag[j] = tmp;
    }
}

// Calculate the score for a move
int scoreMove(const char *selection, unsigned int row, unsigned int col, unsigned int dir) {
    assert(row < BOARD_SIZE && col < BOARD_SIZE && dir <= 1 && selection);

    if (board[row][col] != 0) return -1;  // Starting position occupied

    char testWord[BOARD_SIZE + 1] = "";
    int score = 0;
    int tilesUsed = buildWord(selection, row, col, dir, testWord);

    if (strlen(testWord) < 2 || !findInDictionary(testWord)) return -2;  // Invalid word
    score += scoreWord(testWord);

    const char *wptr = selection;
    char single[2] = "";
    while (*wptr) {
        single[0] = *wptr++;
        tilesUsed += buildWord(single, row, col, !dir, testWord);
        if (strlen(testWord) > 1 && !findInDictionary(testWord)) {
            return -2;  // Invalid adjacent word
        }
        score += scoreWord(testWord);
        if (dir == 0) col++;
        else row++;
    }

    if (!tilesUsed && !isBoardEmpty()) return -1;
    return score;
}
