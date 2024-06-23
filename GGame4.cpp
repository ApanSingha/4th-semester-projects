
#include <graphics.h>
//#include <conio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <time.h>

#define MAX_WORDS 10
#define MAX_WORD_LENGTH 40
#define MAX_LIVES 2
#include <bits/stdc++.h>
using namespace std;
using namespace chrono;


const char *words[MAX_WORDS] = {
    "Computer Science & Engineering", "banana", "cherry", "date", "strawberry",
    "fig", "grape", "mango", "kiwi", "lemon"
};

char currentWord[MAX_WORD_LENGTH];
char userInput[MAX_WORD_LENGTH];
int score = 0;
int lives = MAX_LIVES;
int wordX, wordY;
time_t startTime;

void getRandomWord() {
    int index = rand() % MAX_WORDS;
    strcpy(currentWord, words[index]);
    wordX = rand() % (getmaxx() - strlen(currentWord) * 8);
    wordY = 0;  // Start from the top of the screen
}

void displayText( char *text, int x, int y, int color, int font, int direction, int size) {
    setcolor(color);
    settextstyle(font, direction, size);
    outtextxy(x, y, text);
}

void updateDisplay() {
    cleardevice();
    char scoreText[20];
    sprintf(scoreText, "Score: %d", score);
    displayText(scoreText, 10, 10, WHITE, DEFAULT_FONT, HORIZ_DIR, 2);

    char livesText[20];
    sprintf(livesText, "Lives: %d", lives);
    displayText(livesText, getmaxx() - 150, 10, WHITE, DEFAULT_FONT, HORIZ_DIR, 2);

    displayText(currentWord, wordX, wordY, YELLOW, TRIPLEX_FONT, HORIZ_DIR, 3);
    displayText(userInput, 10, getmaxy() - 50, GREEN, TRIPLEX_FONT, HORIZ_DIR, 2);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    srand(time(NULL));
    getRandomWord();
    userInput[0] = '\0';
    startTime = time(NULL);

    while (lives > 0) {
        updateDisplay();

        if (kbhit()) {
            char ch = getch();
            if (ch == '\r') {  // Enter key
                if (strcmp(userInput, currentWord) == 0) {
                    score += 10;
                    getRandomWord();
                } else {
                    lives--;
                }
                userInput[0] = '\0';
            } else if (ch == '\b') {  // Backspace key
                int len = strlen(userInput);
                if (len > 0) {
                    userInput[len - 1] = '\0';
                }
            } else if (ch >= ' ' && ch <= '~') { // Ensure valid ASCII input
                int len = strlen(userInput);
                if (len < MAX_WORD_LENGTH - 1) { // Ensure there's room for the new character
                    userInput[len] = ch;
                    userInput[len + 1] = '\0';
                }
            }
        }

        wordY += 5;
        if (wordY > getmaxy()) {
            lives--;
            getRandomWord();
        }

        delay(200);
    }

    cleardevice();
    char endText[50];
    sprintf(endText, "Game Over! Final Score: %d", score);
    displayText(endText, getmaxx() / 2 - strlen(endText) * 8, getmaxy() / 2, WHITE, TRIPLEX_FONT, HORIZ_DIR, 3);

    getch();

    closegraph();
    return 0;
}
