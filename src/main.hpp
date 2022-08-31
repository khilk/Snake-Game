#pragma once

struct Coords {
	float x;
	float y;
	float z;
};

void Reshape(int w, int h);
void Display();
void Idle();
void Keyboard(unsigned char Key, int MouseX, int MouseY);
void SpecialKeyboard(int key, int x, int y);
void Mouse(int Buttom, int State, int MouseX, int MouseY);
void Init();
void DrawCube(float dx, float dy, float dz);