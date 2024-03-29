#ifndef VECTOR2D_H
#define VECTOR2D_H

#include<iostream>
#include<math.h>
#include "Common.h"

class Vector2D {
private:

	float pi = 3.141592654;

public:

	float x,y;
	Vector2D(float x_, float y_);  // constructor
	Vector2D(); // default constructor

	bool onMap();

    float dist(float x_, float y_);
	float dist(Vector2D v);

	float angleTo(Vector2D v);

	float magnitude();

	void normalise();
	void rotate(float angle);

	friend std::ostream& operator<<(std::ostream& ioOut, const Vector2D& obj);
};


#endif