#include <iostream>
#include<string>

#include "Rectangle.h"


Rectangle::Rectangle(int _x, int _y, int _width, int _height, const char* _fill)
	:Shape(_fill) {
	setX(_x);
	setY(_y);
	setWidth(_width);
	setHeight(_height);
}

void Rectangle::setX(int _x) {
	this->x = _x;
}

void Rectangle::setY(int _y) {
	this->y = _y;
}

void Rectangle::setWidth(int _width) {
	if (_width < 0) {
		std::cout << "Rectangle width can not be negative!";
	}
	else
		this->width = _width;
}

void Rectangle::setHeight(int _height) {
	if (_height < 0) {
		std::cout << "Rectangle height can not be negative!";
	}
	else
		this->height = _height;
}

void Rectangle::print()const {
	std::cout << "rectangle" << " " << this->x << " " << this->y << " " <<this->width << " " << this->height<<" ";
	Shape::print();
}

void Rectangle:: translate(int vertical, int horizontal) {
	setX(this->x + horizontal);
	setY(this->y + vertical);
}

bool Rectangle::withinRectangle(int rectX, int rectY, int rectWidth, int rectHeight) {
	return this->x <= rectX + rectWidth
		&& this->x >= rectX
		&& this->y <= rectY + rectHeight
		&& this->y >= rectY
		&& this->x + this->width <= rectX + rectWidth
		&& this->y + this->height <= rectY + rectHeight;
}

bool Rectangle::withinCircle(int radius, int x, int y) {
	bool topLeftVertexIsInCircle =
		sqrt((this->x - x)*(this->x - x) + (this->y - y)*(this->y - y)) <= radius;
	bool topRightVertexIsInCircle =
		sqrt(((this->x + this->width) - x)*((this->x + this->width) - x) + (this->y - y)*(this->y - y)) <= radius;
	bool bottomLeftVertexIsInCircle =
		sqrt((this->x - x)*(this->x - x) + ((this->y + this->height) - y)*((this->y + this->height) - y)) <= radius;
	
	return topLeftVertexIsInCircle && topRightVertexIsInCircle && bottomLeftVertexIsInCircle;
}

std::string Rectangle::getShapeBaseAttributes()const {
	return std::to_string(this->x) + " " + std::to_string(this->y) + " "
		+ std::to_string(this->width)  + " " + std::to_string(this->height);
}
