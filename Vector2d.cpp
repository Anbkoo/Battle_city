#include "Vector2D.h"
#include <iostream>

Vector2d& Vector2d::Add(const Vector2d& vec) {
	x += vec.x;
	y += vec.y;

	return *this;
}

Vector2d& Vector2d::Minus(const Vector2d& vec) {
	x -= vec.x;
	y -= vec.y;

	return *this;
}

Vector2d& Vector2d::Multiply(const Vector2d& vec) {
	x *= vec.x;
	y *= vec.y;

	return *this;
}

Vector2d& Vector2d::Divide(const Vector2d& vec) {
	x /= vec.x;
	y /= vec.y;

	return *this;
}

Vector2d& Vector2d::operator*(const int i) {
	x *= i;
	y *= i;

	return *this;
}
Vector2d& Vector2d::Zero() {
	x = y = 0;

	return *this;
}

Vector2d& Vector2d::operator+=(const Vector2d& vec1) {
	return this->Add(vec1);
}
Vector2d& Vector2d::operator-=(const Vector2d& vec1) {
	return this->Minus(vec1);
}
Vector2d& Vector2d::operator*=(const Vector2d& vec1) {
	return this->Multiply(vec1);
}
Vector2d& Vector2d::operator/=(const Vector2d& vec1) {
	return this->Divide(vec1);
}

Vector2d& operator+(Vector2d& vec1, const Vector2d& vec2) {
	return vec1.Add(vec2);
}

Vector2d& operator-(Vector2d& vec1, const Vector2d& vec2) {
	return vec1.Minus(vec2);
}

Vector2d& operator*(Vector2d& vec1, const Vector2d& vec2) {
	return vec1.Multiply(vec2);
}

Vector2d& operator/(Vector2d& vec1, const Vector2d& vec2) {
	return vec1.Divide(vec2);
}

std::ostream& operator<<(std::ostream& stream, const Vector2d& vec1) {
	stream << vec1.x << " " << vec1.y;
	return stream;
}

