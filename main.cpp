#include <iostream>
#include <cstdio>

bool gameOver;
const char wallSymbol = '#', fruitSymbol = '*', snakeSymbol = 'o';
const unsigned int mapWidth = 40, mapHeight = 20;
unsigned int snakeX, snakeY, fruitX, fruitY, score, tailLength;
unsigned int tailX[100], tailY[100];

enum Direction {Stop, Left, Right, Up, Down};

Direction direction = Stop;

using namespace std;

void setup() {
    gameOver = false;
    snakeX = mapWidth / 2;
    snakeY = mapHeight / 2;
    fruitX = random() % mapWidth;
    fruitY = random() % mapHeight;
    score = 0;
    tailLength = 0;
}

void drawMap() {
    system("clear");
    for (int i = 0; i <= mapHeight; i++) {
        for (int j = 0; j < mapWidth; ++j) {
            if (i == 0 || i == mapHeight || j == 0 || j == mapWidth - 1)
                cout << wallSymbol;
            else if (i == fruitY && j == fruitX)
                cout << fruitSymbol;
            else if (i == snakeY && j == snakeX)
                cout << snakeSymbol;
            else {
                bool isTailHere = false;
                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << snakeSymbol;
                        isTailHere = true;
                    }
                }
                if (!isTailHere)
                    cout << " ";
            }
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
}

void input() {
    switch (getchar()) {
        case 'a':
            direction = Left;
            break;
        case 'd':
            direction = Right;
            break;
        case 'w':
            direction = Up;
            break;
        case 's':
            direction = Down;
            break;
        case 'x':
            direction = Stop;
            gameOver = true;
            break;
    }
}

void logic() {
    unsigned int prevX = tailX[0];
    unsigned int prevY = tailY[0];
    unsigned int prev2X, prev2Y;
    tailX[0] = snakeX;
    tailY[0] = snakeY;
    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (direction) {
        case Left:
            snakeX--;
            break;
        case Right:
            snakeX++;
            break;
        case Up:
            snakeY--;
            break;
        case Down:
            snakeY++;
            break;
        case Stop:
            break;
    }
    if (snakeX > mapWidth - 1 || snakeX <= 0 || snakeY > mapHeight - 1 || snakeY <= 0)
        gameOver = true;
    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == snakeX && tailY[i] == snakeY)
            gameOver = true;
    }
    if (snakeX == fruitX && snakeY == fruitY) {
        score++;
        fruitX = random() % mapWidth;
        fruitY = random() % mapHeight;
        tailLength++;
    }
}

int main() {
    setup();
    while (!gameOver) {
        drawMap();
        input();
        logic();
    }

    return 0;
}
