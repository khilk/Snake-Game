#include "fruit.hpp"


void Fruit::Appear(const Snake &snake) {
    while (true) {
        bool collides = false;

        fruit_coords_.x = static_cast<float>(rand() % 19) * 2 + 2.0f;
        fruit_coords_.z = static_cast<float>(rand() % 20) * 2;

        std::deque<Coords> snake_coords = snake.GetPartCoords();
        for (unsigned int i = 0; i < snake_coords.size(); i++) {
            if (fruit_coords_.x == snake_coords[i].x &&
                fruit_coords_.z == snake_coords[i].z) {
                collides = true;
            }
        }

        if (!collides) {
            has_appeared_ = true;
            break;
        }
    }
}

void Fruit::Disappear() {
    has_appeared_ = false;
}


void Fruit::Draw() const {
    if (has_appeared_) {
        glColor3f(0.0f, 0.74f, 1.0f);
        DrawCube(fruit_coords_.x, fruit_coords_.y, fruit_coords_.z);
    }
}

[[nodiscard]] Coords Fruit::GetCoords() const noexcept {
    return fruit_coords_;
}

[[nodiscard]] bool Fruit::GetExistence() const noexcept {
    return has_appeared_;
}
























