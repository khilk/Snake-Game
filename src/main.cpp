#include "snake.hpp"
#include "fruit.hpp"
#include "main.hpp"
#include <iostream>
#include <cmath>
#include <ctime>

int64_t frame_count;
double sync_time;
int width, height;
bool is_paused = false;
Snake snake;
Fruit fruit;

void Reshape(int w, int h) {
    if (h == 0) {
        h = 1;
    }
    float ratio = w * 1.0f / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}


void DrawCube(float dx, float dy, float dz) {
    glBegin(GL_POLYGON);
    glVertex3f(1.0f + dx, -1.0f + dy, -1.0f + dz);
    glVertex3f(1.0f + dx, 1.0f + dy, -1.0f + dz);
    glVertex3f(-1.0f + dx, 1.0f + dy, -1.0f + dz);
    glVertex3f(-1.0f + dx, -1.0f + dy, -1.0f + dz);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.0f + dx, -1.0f + dy, 1.0f + dz);
    glVertex3f(1.0f + dx, 1.0f + dy, 1.0f + dz);
    glVertex3f(-1.0f + dx, 1.0f + dy, 1.0f + dz);
    glVertex3f(-1.0f + dx, -1.0f + dy, 1.0f + dz);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.0f + dx, -1.0f + dy, -1.0f + dz);
    glVertex3f(1.0f + dx, 1.0f + dy, -1.0f + dz);
    glVertex3f(1.0f + dx, 1.0f + dy, 1.0f + dz);
    glVertex3f(1.0f + dx, -1.0f + dy, 1.0f + dz);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.0f + dx, -1.0f + dy, 1.0f + dz);
    glVertex3f(-1.0f + dx, 1.0f + dy, 1.0f + dz);
    glVertex3f(-1.0f + dx, 1.0f + dy, -1.0f + dz);
    glVertex3f(-1.0f + dx, -1.0f + dy, -1.0f + dz);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.0f + dx, 1.0f + dy, 1.0f + dz);
    glVertex3f(1.0f + dx, 1.0f + dy, -1.0f + dz);
    glVertex3f(-1.0f + dx, 1.0f + dy, -1.0f + dz);
    glVertex3f(-1.0f + dx, 1.0f + dy, 1.0f + dz);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(1.0f + dx, -1.0f + dy, -1.0f + dz);
    glVertex3f(1.0f + dx, -1.0f + dy, 1.0f + dz);
    glVertex3f(-1.0f + dx, -1.0f + dy, 1.0f + dz);
    glVertex3f(-1.0f + dx, -1.0f + dy, -1.0f + dz);
    glEnd();
}


void MoveSnake(int) {
    if (!snake.Move(fruit)) {
        std::cout << "score: " << snake.GetScore() << std::endl;
        exit(1);
    }
    glutTimerFunc(snake.GetSpeed(), MoveSnake, 0);
}

void DrawWalls() {
    glColor3f(1.0f, 0.55f, 0.0f);
    Coords vect = {0.0f, 0.0f, 0.0f};
    for (int j = 0; j < 2; j++) {
        vect.z -= 2.0f;
        for (int i = 0; i < 20; i++) {
            vect.x += 2.0f;
            DrawCube(vect.x, vect.y, vect.z);
        }
        vect.x -= 40.0f;
        vect.z += 42.0f;
        for (int i = 0; i < 20; i++) {
            vect.x += 2.0f;
            DrawCube(vect.x, vect.y, vect.z);
        }
        vect.x = 0.0f;
        vect.z = -4.0f;
        for (int i = 0; i < 22; i++) {
            vect.z += 2.0f;
            DrawCube(vect.x, vect.y, vect.z);
        }
        vect.x = 42.0f;
        vect.z = -4.0f;
        for (int i = 0; i < 22; i++) {
            vect.z += 2.0f;
            DrawCube(vect.x, vect.y, vect.z);

        }
        vect.x = 0.0f;
        vect.z = 0.0f;
        vect.y += 2.0f;
    }
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(22.0f, 80.0f, 40.0f,
              22.0f, 1.0f, 20.0f,
              0.0f, 1.0f, 0.0f);
    Coords vect = {0.0f, 0.0f, 0.0f};
    bool flag = true;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (!flag) {
                glColor3f(0.0f, 1.0f, 0.5f);
                flag = true;
            } else {
                glColor3f(0.0f, 0.5f, 0.0f);
                flag = false;
            }
            vect.x += 2.0f;
            DrawCube(vect.x, vect.y, vect.z);
        }
        flag = !flag;
        vect.x -= 40.0f;
        vect.z += 2.0f;
    }
    DrawWalls();

    snake.Draw();
    fruit.Draw();

    glutSwapBuffers();
}


void Idle() {
    int64_t time;
    static int64_t old_time = -1, start_time;
    static char buf[100];

    if (old_time == -1) {
        start_time = old_time = clock();
    } else {
        time = clock();
        sync_time = static_cast<double>(time - start_time) / CLOCKS_PER_SEC;
        time = time - old_time;
        if (time > CLOCKS_PER_SEC) {
            old_time = clock();
            sprintf(buf, "%s. FPS: %.3f", "", frame_count / (static_cast<double>(time) / CLOCKS_PER_SEC));
            frame_count = 0;
            glutSetWindowTitle(buf);
        }
    }
    glutPostRedisplay();
}

void Keyboard(unsigned char key, int, int) {
    if (key == 27) {
        std::cout << "score: " << snake.GetScore() << std::endl;
        exit(0);
    }
}

void SpecialKeyboard(int key, int, int) {
    static int is_full_screen = 0, save_w = 5000, save_h = 5000;
    switch (key) {
        case GLUT_KEY_F10:
            if (is_full_screen) {
                glutReshapeWindow(save_w, save_h);
            } else {
                save_w = width;
                save_h = height;
                glutFullScreen();
            }
            is_full_screen = !is_full_screen;
            break;
        case GLUT_KEY_LEFT:
            if ((snake.GetDirection() != Directions::RIGHT) && !is_paused) {
                snake.ChangeDirection(Directions::LEFT);
            }
            break;
        case GLUT_KEY_RIGHT:
            if ((snake.GetDirection() != Directions::LEFT) && !is_paused) {
                snake.ChangeDirection(Directions::RIGHT);
            }
            break;
        case GLUT_KEY_UP:
            if ((snake.GetDirection() != Directions::DOWN) && !is_paused) {
                snake.ChangeDirection(Directions::UP);
            }
            break;
        case GLUT_KEY_DOWN:
            if ((snake.GetDirection() != Directions::UP) && !is_paused) {
                snake.ChangeDirection(Directions::DOWN);
            }
            break;
        case GLUT_KEY_F2:
            snake.ChangeMoving();
            is_paused = !is_paused;
    }
}

void Mouse(int, int, int, int) {
}

int main(int argc, char **argv) {
    srand(time(nullptr));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(width = 1000, height = 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Game");
    glClearColor(0, 0, 0, 0);
    fruit.Appear(snake);
    glutReshapeFunc(Reshape);
    glutDisplayFunc(Display);
    glutIdleFunc(Idle);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SpecialKeyboard);
    glutMouseFunc(Mouse);
    glutTimerFunc(snake.GetSpeed(), MoveSnake, 0);

    glutMainLoop();

    return 0;
}



































