#pragma once

#include "main.hpp"
#include "snake.hpp"

class Snake;

class Fruit {
public:
    void Appear(const Snake &snake);

    void Disappear();

    void Draw() const;

    [[nodiscard]] bool GetExistence() const noexcept;

    [[nodiscard]] Coords GetCoords() const noexcept;

private:
    bool has_appeared_ = false;
    Coords fruit_coords_ = {2.0f, 0.0f, 0.0f};
};
