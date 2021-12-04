#include "Vector2D.h"


	Vector2D::Vector2D(float x_, float y_) { x = x_; y = y_; }  // constructor
	Vector2D::Vector2D() { x = -1.0; y = -1.0; } // default constructor

	float Vector2D::dist(float x_, float y_) {
		return sqrt( (x - x_)*(x - x_) + (y - y_)*(y - y_) );
	}

	float Vector2D::dist(Vector2D v) {
		return sqrt( (x - v.x)*(x - v.x) + (y - v.y)*(y - v.y) );
	}

	bool Vector2D::onMap() {
		return x >= 0 && y >= 0 && x <= MAP_X && y <= MAP_Y;
	}

	std::ostream& operator<<(std::ostream& ioOut, const Vector2D& obj) {
		ioOut << obj.x << " " << obj.y;
		return ioOut;
	}

	float Vector2D::magnitude() {
		return dist(0.0,0.0);
	}

	float Vector2D::angleTo(Vector2D v) {
		return atan2(v.x - x,v.y - y);
	}

	void Vector2D::normalise() {
		float m = magnitude();
		if (m>0.0) {
			x = x / m;
			y = y / m;
		}
	}

