#include "Trap.hpp"

Trap::Trap()
{
	FaceDown();
}

void Trap::FaceLeft() { dir = Vec2D::left; }
void Trap::FaceRight() { dir = Vec2D::right; }
void Trap::FaceUp() { dir = Vec2D::up; }
void Trap::FaceDown() { dir = Vec2D::down; }
