#pragma once
#include <iostream>

class Vector2D
{
public:
	float x;
	float y;

	Vector2D();
	Vector2D& operator*(const int& i);
	Vector2D(float x, float y);


	Vector2D& Add(const Vector2D& vec);
	Vector2D& Substract(const Vector2D& vec);
	Vector2D& Multiply(const Vector2D& vec);
	Vector2D& Divide(const Vector2D& vec);
	Vector2D& Zero();

	friend Vector2D& operator+(Vector2D vector1, const Vector2D vector2);
	friend Vector2D& operator-(Vector2D vector1, const Vector2D vector2);
	friend Vector2D& operator*(Vector2D vector1, const Vector2D vector2);
	friend Vector2D& operator/(Vector2D vector1, const Vector2D vector2);
	friend std::ostream& operator<<(std::ostream& stream, const Vector2D vector);

	Vector2D& operator+=(const Vector2D& vector);
	Vector2D& operator-=(const Vector2D& vector);
	Vector2D& operator*=(const Vector2D& vector);
	Vector2D& operator/=(const Vector2D& vector);
};