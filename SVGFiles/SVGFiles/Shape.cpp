#include <string>
#include <iostream>

#include "Shape.h"

void Shape::setFill(char const* _fill)
{
	int len = strlen(_fill) + 1;
	if (len < 20)
		strcpy_s(this->fill, len, _fill);
	else
		std::cout << "Too much length!";
}


Shape::Shape(const char* _fill) {
	setFill(_fill);
}

void Shape::print()const {
	std::cout << this->fill << " " << std::endl;
}



