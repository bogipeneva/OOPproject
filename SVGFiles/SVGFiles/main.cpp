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

std::string rectangle = "rectangle";



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

void createNewShape(std::string shapeType, std::vector<std::string> shapeAttributes) {
	// creating object from the class stringstream in order to convert string to number
	std::stringstream geek;

	if (shapeType == rectangle) {
		if (shapeAttributes.size() < 4) {
			std::cout << "Maybe you have missed some of the basic attributes.Please Try again" << std::endl;
		}
		else {
			
		}
	}

	std::cout << shapeType << std::endl;
	for (auto i : shapeAttributes) std::cout << i << std::endl;
}

int main()
{
	/*
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("fig.svg");

	pugi::xml_node panels = doc.child("svg");

	Shape** shapes = new Shape*[5];
	int shapesIndex = 0;

	for (pugi::xml_node panel = panels.first_child(); panel; panel = panel.next_sibling())
	{
		if (strcmp(panel.name(),"rect")== 0) {
			shapes[shapesIndex] = new Rectangle(panel.attribute("x").as_int(), panel.attribute("y").as_int(), panel.attribute("width").as_int(), panel.attribute("height").as_int(), panel.attribute("fill").as_string(), panel.attribute("stroke").as_string(), panel.attribute("fill_opacity").as_double(), panel.attribute("stroke_opacity").as_double(), panel.attribute("stroke_width").as_int());
			shapesIndex++;
		}
		else if (strcmp(panel.name(), "circle") == 0) {
			shapes[shapesIndex] = new Circle(panel.attribute("r").as_int(), panel.attribute("cx").as_int(), panel.attribute("cy").as_int(), panel.attribute("fill").as_string(), panel.attribute("stroke").as_string(), panel.attribute("fill_opacity").as_double(), panel.attribute("stroke_opacity").as_double(), panel.attribute("stroke_width").as_int());
			shapesIndex++;
		}
		else if (strcmp(panel.name(), "line") == 0) {
			shapes[shapesIndex] = new Line(panel.attribute("x1").as_int(), panel.attribute("y1").as_int(), panel.attribute("x2").as_int(), panel.attribute("y").as_int(), panel.attribute("fill").as_string(), panel.attribute("stroke").as_string(), panel.attribute("fill_opacity").as_double(), panel.attribute("stroke_opacity").as_double(), panel.attribute("stroke_width").as_int());
			shapesIndex++;
		}
		else if (strcmp(panel.name(), "ellipse") == 0) {
			shapes[shapesIndex] = new Ellipse(panel.attribute("rx").as_int(), panel.attribute("ry").as_int(), panel.attribute("cx").as_int(), panel.attribute("cy").as_int(), panel.attribute("fill").as_string(), panel.attribute("stroke").as_string(), panel.attribute("fill_opacity").as_double(), panel.attribute("stroke_opacity").as_double(), panel.attribute("stroke_width").as_int());
			shapesIndex++;
		}
	}

	printShapes(shapes, shapesIndex);
	

	//deleting dynamic allocated data
	for (int index = 0; index < shapesIndex; index++) {
		delete shapes[index];
	}

	delete[] shapes;
	*/
	std::string userChoice;
	std::cout << "Enter choice: ";
	std::cout << std::endl;
	std::getline(std::cin, userChoice);
	
	std::string delimiter = " ";
	std::vector<std::string> selectedOption = split(userChoice, delimiter);

	std::string selectedOperation = selectedOption.front();
	std::cout << selectedOperation << std::endl;

	std::string selectedShapeType = selectedOption[1];

	std::vector<std::string> attributes(selectedOption.begin() + 2, selectedOption.end());

	createNewShape(selectedShapeType, attributes);

	

	// The object has the value 145 and stream 
	// it to the integer x 


	system("pause");
	return 0;

}