#include "snake.hpp"

using namespace std;

#include <iostream>

[[nodiscard]] bool Snake::Move(Fruit &fruit) {
    if (is_moving_) {
        Coords new_head = part_coords_[0];
        if (direction_ == UP) {
            for (unsigned int i = 0; i < part_coords_.size(); i++) {
                if (part_coords_[0].x == part_coords_[i].x &&
                    part_coords_[0].z - 2.0f == part_coords_[i].z) {
                    return false;
                }
            }
            new_head.z = part_coords_[0].z - 2.0f;
        } else if (direction_ == DOWN) {
            for (unsigned int i = 0; i < part_coords_.size(); i++) {
                if (part_coords_[0].x == part_coords_[i].x &&
                    part_coords_[0].z + 2.0f == part_coords_[i].z) {
                    return false;
                }
            }

            new_head.z = part_coords_[0].z + 2.0f;
        } else if (direction_ == LEFT) {
            for (unsigned int i = 0; i < part_coords_.size(); i++) {
                if (part_coords_[0].x - 2.0f == part_coords_[i].x &&
                    part_coords_[0].z == part_coords_[i].z) {
                    return false;
                }
            }
            new_head.x = part_coords_[0].x - 2.0f;
        } else if (direction_ == RIGHT) {
            for (unsigned int i = 0; i < part_coords_.size(); i++) {
                if (part_coords_[0].x + 2.0f == part_coords_[i].x &&
                    part_coords_[0].z == part_coords_[i].z) {
                    return false;
                }
            }
            new_head.x = part_coords_[0].x + 2.0f;
        }


        part_coords_.push_front(new_head);
        if (fruit.GetExistence()) {
            if (new_head.x == fruit.GetCoords().x && new_head.z == fruit.GetCoords().z) {
                Eat(fruit);
            }
        }
        if (!growth_) {
            part_coords_.pop_back();
        }
        growth_ = false;
        if (new_head.x < 2.0f || new_head.x > 40.0f || new_head.z < 0.0f || new_head.z > 38.0f) {
            return false;
        }
        glutPostRedisplay();
    }
    return true;
}

Snake::Snake() {
    for (int i = 0; i < 10; i++) {
        part_coords_.push_back({6.0f + 2.0f * i, 0.0f, 0.0f});
    }
}

void Snake::Draw() const {
    glColor3f(1.0f, 0.08f, 0.57f);
    for (unsigned int i = 0; i < part_coords_.size(); i++) {
        DrawCube(part_coords_[i].x, part_coords_[i].y, part_coords_[i].z);
    }
}

void Snake::ChangeDirection(Directions new_direction) noexcept {
    direction_ = new_direction;
}

[[nodiscard]] Directions Snake::GetDirection() const noexcept {
    return direction_;
}

[[nodiscard]] deque<Coords> Snake::GetPartCoords() const noexcept {
    return part_coords_;
}


void Snake::Eat(Fruit &fruit) {
    score_ += 1;
    move_speed_ += 5;
    fruit.Disappear();
    fruit.Appear(*this);
    growth_ = true;
}

[[nodiscard]] int Snake::GetSpeed() const noexcept {
    return move_speed_;
}

[[nodiscard]] int Snake::GetScore() const noexcept {
    return score_;
}

void Snake::ChangeMoving() noexcept {
    is_moving_ = !is_moving_;
}
