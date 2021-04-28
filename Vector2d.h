#pragma once
#include <iostream>

class Vector2d {
public:
	Vector2d() : x(0), y(0) {};
	Vector2d(int pos_x, int pos_y) : x(pos_x), y(pos_y) {};
	~Vector2d() {}

	Vector2d& Add(const Vector2d& vec);
	Vector2d& Minus(const Vector2d& vec);
	Vector2d& Multiply(const Vector2d& vec);
	Vector2d& Divide(const Vector2d& vec);

	Vector2d& operator+=(const Vector2d& vec1);
	Vector2d& operator-=(const Vector2d& vec1);
	Vector2d& operator*=(const Vector2d& vec1);
	Vector2d& operator/=(const Vector2d& vec1);

	Vector2d& operator*(const int i);
	Vector2d& Zero();

	int x, y;
};

Vector2d& operator+(Vector2d& vec1, const Vector2d& vec2);
Vector2d& operator-(Vector2d& vec1, const Vector2d& vec2);
Vector2d& operator*(Vector2d& vec1, const Vector2d& vec2);
Vector2d& operator/(Vector2d& vec1, const Vector2d& vec2);
std::ostream& operator<<(std::ostream& stream, const Vector2d& vec1);