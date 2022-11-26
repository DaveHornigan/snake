//
// Created by dave on 26.11.22.
//

#ifndef SNAKE_GAME_MAIN_H
#define SNAKE_GAME_MAIN_H

#include <iostream>
#include <random>

const int MAP_WIDTH = 40;
const int MAP_HEIGHT = 20;

enum Direction {
    Stop, Left, Right, Up, Down
};

struct Coord {
    int x, y;
    Coord(int x, int y) {
        this->x = x;
        this->y = y;
    }
    bool equal(Coord coord) const {
        return x == coord.x && y == coord.y;
    }
};

class Tail {
    friend class Snake;

    int x[MAP_WIDTH * MAP_HEIGHT]{}, y[MAP_WIDTH * MAP_HEIGHT]{};
    int length = 0;
private:
    void move(Coord coord) {
        int prevX = x[0];
        int prevY = y[0];
        int prev2X, prev2Y;
        x[0] = coord.x;
        y[0] = coord.y;
        for (int i = 1; i < getLength(); i++) {
            prev2X = x[i];
            prev2Y = y[i];
            x[i] = prevX;
            y[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }
    }
public:
    bool isTailOnCoord(Coord coord) {
        for (int k = 0; k < length; k++) {
            if (x[k] == coord.x && y[k] == coord.y) {
                return true;
            }
        }

        return false;
    }

    int getLength() const {
        return length;
    }
};

class Fruit {
    friend class Map;

private:
    Coord coord = newCoord();

    static Coord newCoord() {
        return {static_cast<int>(random() % MAP_WIDTH), static_cast<int>(random() % MAP_HEIGHT)};
    }

    void eat() {
        coord = newCoord();
    }
public:
    bool isFruitOnCoord(int coordX, int coordY) const {
        return Coord(coordX, coordY).equal(coord);
    }
};

class Snake {
    friend class Map;

private:
    Coord coord = Coord(MAP_WIDTH / 2, MAP_HEIGHT / 2);
    Tail tail = Tail();
    Direction direction = Stop;
    bool dead = false;
public:
    void kill() {
        dead = true;
    }

    bool isDead() const {
        return dead;
    }

    Coord getHeadCoord() {
        return coord;
    }

    void move() {
        switch (direction) {
            case Left:
                coord.x--;
                break;
            case Right:
                coord.x++;
                break;
            case Up:
                coord.y--;
                break;
            case Down:
                coord.y++;
                break;
            case Stop:
                break;
        }
        tail.move(coord);
    }

    void setDirection(Direction newDirection) {
        direction = newDirection;
    }

    bool tryEatFruit(Fruit fruit) {
        if (fruit.isFruitOnCoord(coord.x, coord.y)) {
            tail.length++;

            return true;
        }

        return false;
    }
    bool isHeadOnCoord(int coordX, int coordY) const {
        return Coord(coordX, coordY).equal(coord);
    }

    void tryEatTail() {
        if (tail.isTailOnCoord(coord)) {
            kill();
        }
    }
};

class Map {
    friend class Game;

    const char WALL = '#';
    const char FRUIT = '@';
    const char SNAKE_HEAD = 'O';
    const char SNAKE_TAIL = 'o';
private:
    int width = 40;
    int height = 20;
    Snake snake = Snake();
    Fruit fruit = Fruit();
public:
    bool isWallOnCoord(int coordX, int coordY) const {
        return coordY == 0 || coordY == height || coordX == 0 || coordX == width - 1;
    }
    bool isWallOnCoord(Coord mapCoord) const {
        return mapCoord.y == 0 || mapCoord.y == height || mapCoord.x == 0 || mapCoord.x == width - 1;
    }

    void eatFruit() {
        fruit.eat();
    }

    void draw() {
        system("clear");
        for (int y = 0; y <= height; y++) {
            for (int x = 0; x < width; ++x) {
                if (isWallOnCoord(x, y))
                    std::cout << WALL;
                else if (fruit.isFruitOnCoord(x, y))
                    std::cout << FRUIT;
                else if (snake.isHeadOnCoord(x, y))
                    std::cout << SNAKE_HEAD;
                else {
                    if (snake.tail.isTailOnCoord(Coord(x, y)))
                        std::cout << SNAKE_TAIL;
                    else
                        std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }
};

class Input {
public:
    void pressButton(int ch, Snake &snake) {
        switch (ch) {
            case 'a':
                snake.setDirection(Left);
                break;
            case 'd':
                snake.setDirection(Right);
                break;
            case 'w':
                snake.setDirection(Up);
                break;
            case 's':
                snake.setDirection(Down);
                break;
            case 'x':
                snake.kill();
                break;
            default:
                break;
        }
    }
};

class Game {
    friend int main();

    int score = 0;
    bool gameOver = false;
    Map map = Map();
    Input input = Input();

    void update() {
        map.draw();
        std::cout << "Score: " << score << std::endl;
        input.pressButton(getchar(), map.snake);
        map.snake.move();
        if (map.isWallOnCoord(map.snake.getHeadCoord())) {
            map.snake.kill();
        }
        map.snake.tryEatTail();
        if (map.snake.isDead())
            exit();
        if (map.snake.tryEatFruit(map.fruit)) {
            score++;
            map.eatFruit();
        }
    }

    void exit() {
        gameOver = true;
    }
};


#endif //SNAKE_GAME_MAIN_H
