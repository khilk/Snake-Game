#pragma once

#include <GL/glew.h>
#include <GL/glut.h>

#include <deque>

#include "main.hpp"
#include "fruit.hpp"


enum Directions {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

class Fruit;

class Snake {
public:
    Snake();

    void Eat(Fruit &fruit);

    [[nodiscard]] bool Move(Fruit &fruit);

    void Draw() const;

    [[nodiscard]] Directions GetDirection() const noexcept;

    [[nodiscard]] std::deque<Coords> GetPartCoords() const noexcept;

    [[nodiscard]] int GetSpeed() const noexcept;

    [[nodiscard]] int GetScore() const noexcept;

    void ChangeMoving() noexcept;

    void ChangeDirection(Directions new_direction) noexcept;

private:
    bool is_moving_ = true;
    Directions direction_ = DOWN;
    int move_speed_ = 100;
    std::deque<Coords> part_coords_;
    bool growth_ = false;
    int score_ = 0;
};
