#include<iostream>
#include<string.h>
#include<vector>
#include <sstream>
#include "lib/src/pugixml.hpp"
#include "lib/src/pugixml.cpp"
#include "Rectangle.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Line.h"   

const std::string RECTANGLE = "rectangle";
const std::string CIRCLE = "circle";
const std::string ELLIPSE = "ellipse";
const std::string LINE = "line";

const int MAX_NUMBER_OF_SHAPES = 50;


void printShapes(Shape** shapes, int numberOfShapes) {
	for (int index = 0; index < numberOfShapes; index++) {
		std::cout << index+1<<". ";
		shapes[index]->print();
	}
}

std::vector<std::string> split(std::string string, std::string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> result;

	while ((pos_end = string.find(delimiter, pos_start)) != std::string::npos) {
		token = string.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		result.push_back(token);
	}

	result.push_back(string.substr(pos_start));
	return result;
}

std::vector<int> prepareShapeCordinates(std::vector<std::string> shapeAttributes) {
	std::vector<int> attributes;
	int numberValue = 0;

	for (auto attr : shapeAttributes) {
		// creating object from the class stringstream in order to convert string to number;
		// Assign attribute value to the object of stringstream class
		std::stringstream geek(attr);
		// stream it to the integer numberValue
		geek >> numberValue;
		attributes.push_back(numberValue);
	}

	return attributes;
}

void createNewShape(std::string shapeType, std::vector<std::string> shapeAttributes, Shape** shapes, int *numberOfShapes) {
	std::string fillStringValue = shapeAttributes.back();
	shapeAttributes.pop_back();

	char* fill = new char[20];
	strcpy_s(fill,20, fillStringValue.c_str());

	std::vector<int> integerAttributes;
	integerAttributes = prepareShapeCordinates(shapeAttributes);


	if (shapeType == RECTANGLE) {
		shapes[*numberOfShapes] = new Rectangle(integerAttributes[0], integerAttributes[1], integerAttributes[2], integerAttributes[3], fill);
	}
	else if (shapeType == CIRCLE) {
		shapes[*numberOfShapes] = new Circle(integerAttributes[0], integerAttributes[1], integerAttributes[2], fill);
	}
	else if (shapeType == ELLIPSE) {
		shapes[*numberOfShapes] = new Ellipse(integerAttributes[0], integerAttributes[1], integerAttributes[2], integerAttributes[3], fill);
	}
	else if (shapeType == LINE) {
		shapes[*numberOfShapes] = new Line(integerAttributes[0], integerAttributes[1], integerAttributes[2], integerAttributes[3], fill);
	}

	(*numberOfShapes)++;
	std::cout << "Successfully created " << shapeType << '(' << *numberOfShapes << ')' << std::endl;
}

void deleteShape(int shapeIndex, Shape** shapes, int* numberOfShapes) {
	
	if (shapeIndex == *numberOfShapes - 1) {
		delete shapes[shapeIndex];
		(*numberOfShapes)--;
	}
	else if (shapeIndex >= *numberOfShapes) {
		std::cout << "There is no figure number"<<" "<<shapeIndex << std::endl;
	}
	else {
		Shape* toBeDeleted = shapes[shapeIndex - 1];
		toBeDeleted->print();
		int startIdex = shapeIndex - 1;
		while (startIdex < *numberOfShapes - 1)
		{
			shapes[startIdex] = shapes[startIdex + 1];
			startIdex++;
		}
		(*numberOfShapes)--;
		shapes[startIdex] = nullptr;
		delete shapes[startIdex];
		delete toBeDeleted;
	}
	
	printShapes(shapes, *numberOfShapes);

}

void translate(Shape** shapes,int numberOfShapes, int vertical, int horizontal, int shapeIndex = -1) {
	if (shapeIndex == -1) {
		for (int index = 0; index < numberOfShapes; index++) {
			shapes[index]->translate(vertical, horizontal);
		}
		std::cout << "Translated all figures" << std::endl;
	}
	else {
		shapes[shapeIndex]->translate(vertical, horizontal);
		std::cout << "Translated (" << shapeIndex << ')' << " figure" << std::endl;
	}
}

// TODO: write test this function
void withinRectangle(Shape** shapes, int numberOfShapes, int rectX, int rectY, int rectWidth, int rectHeight) {
	int numberOfShapesInRectangle = 0;
	for (int shapeIndex = 0; shapeIndex < numberOfShapes; shapeIndex++){
		if (shapes[shapeIndex]->withinRectangle(rectX, rectY, rectWidth, rectHeight)) {
			shapes[shapeIndex]->print();
			numberOfShapesInRectangle++;
		}
	}
	if (numberOfShapesInRectangle == 0)
		std::cout << "No figures are located within rectangle"<<" "
			<< rectX <<" "<< rectY << " " << rectWidth << " " << rectHeight << std::endl;
} 

// TODO: write test this function
void withinCircle(Shape** shapes, int numberOfShapes, int radius, int x, int y) {
	int numberOfShapesInCircle = 0;
	for (int shapeIndex = 0; shapeIndex < numberOfShapes; shapeIndex++) {
		if (shapes[shapeIndex]->withinCircle(radius, x, y)) {
			shapes[shapeIndex]->print();
			numberOfShapesInCircle++;
		}
	}
	if (numberOfShapesInCircle == 0) 
		std::cout << "No figures are located within rectangle"<<" "<< radius<<" " << x<<" "<< y<< std::endl;
}

void within(Shape** shapes, int numberOfShapes, std::string option, std::vector<int> optionArgs) {
	if (option == RECTANGLE) {
		withinRectangle(shapes, numberOfShapes, optionArgs[0], optionArgs[1], optionArgs[2], optionArgs[3]);
	}
	else if (option == CIRCLE) {
		withinCircle(shapes, numberOfShapes, optionArgs[0], optionArgs[1], optionArgs[2]);
	}
	else {
		std::cout << "" << std::endl;
	}
}

int main()
{ 
	
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("fig.svg");

	pugi::xml_node panels = doc.child("svg");

	Shape** shapes = new Shape*[MAX_NUMBER_OF_SHAPES];
	int numberOfShapes = 0;

	for (pugi::xml_node panel = panels.first_child(); panel; panel = panel.next_sibling())
	{
		if (strcmp(panel.name(),"rect")== 0) {
			shapes[numberOfShapes] = new Rectangle(panel.attribute("x").as_int(), panel.attribute("y").as_int(), panel.attribute("width").as_int(), panel.attribute("height").as_int(), panel.attribute("fill").as_string());
			numberOfShapes++;
		}
		else if (strcmp(panel.name(), "circle") == 0) {
			shapes[numberOfShapes] = new Circle(panel.attribute("r").as_int(), panel.attribute("cx").as_int(), panel.attribute("cy").as_int(), panel.attribute("fill").as_string());
			numberOfShapes++;
		}
		else if (strcmp(panel.name(), "line") == 0) {
			shapes[numberOfShapes] = new Line(panel.attribute("x1").as_int(), panel.attribute("y1").as_int(), panel.attribute("x2").as_int(), panel.attribute("y").as_int(), panel.attribute("fill").as_string());
			numberOfShapes++;
		}
		else if (strcmp(panel.name(), "ellipse") == 0) {
			shapes[numberOfShapes] = new Ellipse(panel.attribute("rx").as_int(), panel.attribute("ry").as_int(), panel.attribute("cx").as_int(), panel.attribute("cy").as_int(), panel.attribute("fill").as_string());
			numberOfShapes++;
		}
	}

	printShapes(shapes, numberOfShapes);
	
	std::string userChoice;
	std::cout << "Enter choice: ";
	std::cout << std::endl;
	std::getline(std::cin, userChoice);
	
	std::string delimiter = " ";
	std::vector<std::string> selectedOption = split(userChoice, delimiter);

	std::string selectedOperation = selectedOption.front();

	std::string selectedShapeType = selectedOption[1];

	std::vector<std::string> attributes(selectedOption.begin() + 2, selectedOption.end());

	createNewShape(selectedShapeType, attributes, shapes, &numberOfShapes);
	printShapes(shapes, numberOfShapes);

	//translate(shapes, numberOfShapes, 2, 3);
	//withinRectangle(shapes, numberOfShapes, 3, 4, 50, 50);
	//withinCircle(shapes, numberOfShapes, 2, 10, 10);
	std::cout << std::endl;

	//printShapes(shapes, numberOfShapes);

	deleteShape(5, shapes, &numberOfShapes);

	printShapes(shapes, numberOfShapes);

	//deleting dynamic allocated data
	for (int index = 0; index < numberOfShapes; index++) {
	delete shapes[index];
	}

	delete[] shapes;


	system("pause");
	return 0;

}