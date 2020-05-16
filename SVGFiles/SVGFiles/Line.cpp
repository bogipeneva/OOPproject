#include "Line.h"
#include<iostream>

Line::Line(int _x1, int _y1, int _x2, int _y2, const char* _fill)
	:Shape(_fill) {
	setX1(_x1);
	setY1(_y1);
	setX2(_x2);
	setY2(_y2);
}

void Line::setX1(int _x1) {
	this->x1 = _x1;
}

void Line::setY1(int _y1) {
	this->y1 = _y1;
}

void Line::setX2(int _x2) {
	this->x2 = _x2;
}

void Line::setY2(int _y2) {
	this->y2 = _y2;
}
void Line::print()const {
	std::cout << "line" << " " << this->x1 << " " << this->y1 << " " << this->x2 << " " << this->y2 << " ";
	Shape::print();
}

void Line::translate(int vertical, int horizontal) {
	setX1(this->x1 + horizontal);
	setY1(this->y1 + vertical);
	setX2(this->x2 + horizontal);
	setY2(this->y2 + vertical);
}

bool Line::withinRectangle(int rectX, int rectY, int rectWidth, int rectHeight) {
	return this->x1 <= rectX + rectWidth
		&& this->x1 >= rectX
		&& this->x2 <= rectX + rectWidth
		&& this->x2 >= rectX
		&& this->y1 <= rectY + rectHeight
		&& this->y1 >= rectY
		&& this->y2 <= rectY + rectHeight
		&& this->y2 >= rectY;
}

bool Line::withinCircle(int radius, int x, int y) {
	bool lineStartIsInCircle =
		sqrt((this->x1 - x)*(this->x1 - x) + (this->y1 - y)*(this->y1 - y)) <= radius;
	bool lineEndIsInCircle =
		sqrt((this->x2 - x)*(this->x2 - x) + (this->y2 - y)*(this->y2 - y)) <= radius;
	return lineStartIsInCircle && lineEndIsInCircle;
}
