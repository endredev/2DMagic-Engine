#include "Vector2D.h"

Vector2D::Vector2D() {
	x = 0.0f;
	y = 0.0f;
}

Vector2D::Vector2D(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2D& Vector2D::Add(const Vector2D& vec) {
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2D& Vector2D::Substract(const Vector2D& vec) {
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vec) {
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vec) {
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

Vector2D& operator+(Vector2D& v1, Vector2D& v2) {
	return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, Vector2D& v2) {
	return v1.Substract(v2);
}

Vector2D& operator*(Vector2D& v1, Vector2D& v2) {
	return v1.Multiply(v2);
}

Vector2D& operator/(Vector2D& v1, Vector2D& v2) {
	return v1.Divide(v2);
}

std::ostream& operator<< (std::ostream& stream, const Vector2D vector) {
	stream << "(" << vector.x << ", " << vector.y << ")";
	return stream;
}

Vector2D& Vector2D::operator+=(const Vector2D& vector) {
	return this->Add(vector);
}

Vector2D& Vector2D::operator-=(const Vector2D& vector) {
	return this->Substract(vector);
}

Vector2D& Vector2D::operator*=(const Vector2D& vector) {
	return this->Multiply(vector);
}

Vector2D& Vector2D::operator/=(const Vector2D& vector) {
	return this->Divide(vector);
}

Vector2D& Vector2D::operator*(const int& i) {
	this->x *= i;
	this->y *= i;
	return *this;
}

Vector2D& Vector2D::Zero() {
	this->x = 0;
	this->y = 0;
	return *this;
}