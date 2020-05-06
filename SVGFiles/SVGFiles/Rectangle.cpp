#include "Rectangle.h"

#include <iostream>


Rectangle::Rectangle(int _x, int _y, int _width, int _height, const char* _fill, const char* _stroke, double _fillOpacity, double _strokeOpacity, int _strokeWith)
	:Shape(_fill, _stroke, _fillOpacity, _strokeOpacity, _strokeWith) {
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



