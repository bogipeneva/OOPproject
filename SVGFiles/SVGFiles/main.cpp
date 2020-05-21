#include<iostream>
#include<string>
#include<vector>
#include <sstream>
#include <cmath>
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

int convertStringToInteger(std::string toBeConverted) {
	int integerValue;
	std::stringstream geek(toBeConverted);
	geek >> integerValue;

	return integerValue;
}

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
		attributes.push_back(abs(numberValue));
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
	if (shapeIndex > *numberOfShapes) {
		std::cout << "There is no figure number"<<" "<<shapeIndex <<" !"<< std::endl;
	}
	else {
		Shape* toBeDeleted = shapes[shapeIndex - 1];

		char* shapeType = new char[10];
		strcpy_s(shapeType, strlen(toBeDeleted->getShapeType()) + 1, toBeDeleted->getShapeType());

		if (shapeIndex == *numberOfShapes) {
			delete shapes[shapeIndex - 1]; //because indexing starts from 0 not from 1
			(*numberOfShapes)--;
		}
		else {
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
			delete[10] shapeType;
		}
		std::cout << "Erased a " << shapeType << " (" << shapeIndex << ")" << std::endl;
	}

}

void translate(Shape** shapes,int numberOfShapes, int vertical, int horizontal, int shapeNumber = -1) {
	if (shapeNumber == -1) {
		for (int index = 0; index < numberOfShapes; index++) {
			shapes[index]->translate(vertical, horizontal);
		}
		std::cout << "Translated all figures" << std::endl;
	}
	else {
		shapes[shapeNumber - 1]->translate(vertical, horizontal);
		std::cout << "Translated figure  " <<'(' << shapeNumber << ')'<< std::endl;
	}
}

// TODO: write test this function
void withinRectangle(Shape** shapes, int numberOfShapes, int rectX, int rectY, int rectWidth, int rectHeight) {
	int numberOfShapesInRectangle = 0;
	for (int shapeIndex = 0; shapeIndex < numberOfShapes; shapeIndex++){
		if (shapes[shapeIndex]->withinRectangle(rectX, rectY, rectWidth, rectHeight)) {
			std::cout << shapeIndex + 1<<". ";
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
			std::cout << shapeIndex + 1<<". ";
			shapes[shapeIndex]->print();
			numberOfShapesInCircle++;
		}
	}
	if (numberOfShapesInCircle == 0) 
		std::cout << "No figures are located within circle"<<" " << x <<" "<< y<< " " << radius << std::endl;
}

void within(Shape** shapes, int numberOfShapes, std::string option, std::vector<int> optionArgs) {
	if (option == RECTANGLE) {
		withinRectangle(shapes, numberOfShapes, optionArgs[0], optionArgs[1], optionArgs[2], optionArgs[3]);
	}
	else if (option == CIRCLE) {
		withinCircle(shapes, numberOfShapes, optionArgs[2], optionArgs[0], optionArgs[1]);
	}
	else {
		std::cout << "" << std::endl;
	}
}

void appendNewShape(Shape** shapes,int shapeIndex, int numberOfShapes, const char* fileName) {
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file(fileName);

	pugi::xml_node svg = doc.child("svg");

	for (int index = shapeIndex; index < numberOfShapes; index++) {
		if (shapes[index]->getShapeType() == RECTANGLE) {
			pugi::xml_node newShape = svg.append_child("rect");
			std::vector<std::string> rectAttributes = split(shapes[index]->getShapeBaseAttributes(), " ");
			std::string fillAttr = shapes[index]->getFill();
			rectAttributes.push_back(fillAttr);
			newShape.append_attribute("x") = rectAttributes[0].c_str();
			newShape.append_attribute("y") = rectAttributes[1].c_str();
			newShape.append_attribute("width") = rectAttributes[2].c_str();
			newShape.append_attribute("height") = rectAttributes[3].c_str();
			newShape.append_attribute("fill") = rectAttributes[4].c_str();
		}
		else if (shapes[index]->getShapeType() == CIRCLE) {
			pugi::xml_node newShape = svg.append_child("circle");
			std::vector<std::string> rectAttributes = split(shapes[index]->getShapeBaseAttributes(), " ");
			std::string fillAttr = shapes[index]->getFill();
			rectAttributes.push_back(fillAttr);
			newShape.append_attribute("r") = rectAttributes[0].c_str();
			newShape.append_attribute("cx") = rectAttributes[1].c_str();
			newShape.append_attribute("cy") = rectAttributes[2].c_str();
			newShape.append_attribute("fill") = rectAttributes[3].c_str();
		}
		else if (shapes[index]->getShapeType() == ELLIPSE) {
			pugi::xml_node newShape = svg.append_child("ellipse");
			std::vector<std::string> rectAttributes = split(shapes[index]->getShapeBaseAttributes(), " ");
			std::string fillAttr = shapes[index]->getFill();
			rectAttributes.push_back(fillAttr);
			newShape.append_attribute("rx") = rectAttributes[0].c_str();
			newShape.append_attribute("ry") = rectAttributes[1].c_str();
			newShape.append_attribute("x") = rectAttributes[2].c_str();
			newShape.append_attribute("y") = rectAttributes[3].c_str();
			newShape.append_attribute("fill") = rectAttributes[4].c_str();
		}
		else if (shapes[index]->getShapeType() == LINE) {
			pugi::xml_node newShape = svg.append_child("line");
			std::vector<std::string> rectAttributes = split(shapes[index]->getShapeBaseAttributes(), " ");
			std::string fillAttr = shapes[index]->getFill();
			rectAttributes.push_back(fillAttr);
			newShape.append_attribute("x1") = rectAttributes[0].c_str();
			newShape.append_attribute("y1") = rectAttributes[1].c_str();
			newShape.append_attribute("x2") = rectAttributes[2].c_str();
			newShape.append_attribute("y2") = rectAttributes[3].c_str();
			newShape.append_attribute("fill") = rectAttributes[4].c_str();
		}
		else {
			std::cout << "Trying to add unknown shape" << std::endl;
		}

	}
	doc.save_file(fileName);
}

void saveFile(Shape** shapes, int numberOfShapes, const char* fileName) {
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file(fileName);

	//if there is no file with that fileName we create new file and save data in it.
	if (!result) {
		doc.append_child("svg");
		doc.save_file(fileName);

		appendNewShape(shapes, 0, numberOfShapes, fileName);
	}
	else {
		pugi::xml_node panels = doc.child("svg");

		int shapeIndex = 0;

		for (pugi::xml_node panel = panels.first_child(); panel;)
		{
			pugi::xml_node next = panel.next_sibling();

			if (strcmp(panel.name(), "rect") == 0) {
				if (shapeIndex >= numberOfShapes || shapes[shapeIndex]->getShapeType() != RECTANGLE) {
					panel.parent().remove_child(panel);
				}
				else {
					std::vector<std::string> rectAttributes = split(shapes[shapeIndex]->getShapeBaseAttributes(), " ");
					std::string fillAttr = shapes[shapeIndex]->getFill();
					rectAttributes.push_back(fillAttr);
					int attributeIndex = 0;
					for (pugi::xml_attribute attr : panel.attributes())
					{
						std::string attrValue = rectAttributes[attributeIndex];
						attr.set_value(attrValue.c_str());
						attributeIndex++;
					}
					shapeIndex++;
				}
			}
			else if (strcmp(panel.name(), "circle") == 0) {
				if (shapeIndex >= numberOfShapes || shapes[shapeIndex]->getShapeType() != CIRCLE) {
					panel.parent().remove_child(panel);
				}
				else {
					std::vector<std::string> rectAttributes = split(shapes[shapeIndex]->getShapeBaseAttributes(), " ");
					std::string fillAttr = shapes[shapeIndex]->getFill();
					rectAttributes.push_back(fillAttr);
					int attributeIndex = 0;
					for (pugi::xml_attribute attr : panel.attributes())
					{
						std::string attrValue = rectAttributes[attributeIndex];
						attr.set_value(attrValue.c_str());
						attributeIndex++;
					}
					shapeIndex++;
				}
			}
			else if (strcmp(panel.name(), "line") == 0) {
				if (shapeIndex >= numberOfShapes || shapes[shapeIndex]->getShapeType() != LINE) {
					panel.parent().remove_child(panel);
				}
				else {
					std::vector<std::string> rectAttributes = split(shapes[shapeIndex]->getShapeBaseAttributes(), " ");
					std::string fillAttr = shapes[shapeIndex]->getFill();
					rectAttributes.push_back(fillAttr);
					int attributeIndex = 0;
					for (pugi::xml_attribute attr : panel.attributes())
					{
						std::string attrValue = rectAttributes[attributeIndex];
						attr.set_value(attrValue.c_str());
						attributeIndex++;
					}
					shapeIndex++;
				}
			}
			else if (strcmp(panel.name(), "ellipse") == 0) {
				if (shapeIndex >= numberOfShapes || shapes[shapeIndex]->getShapeType() != ELLIPSE) {
					panel.parent().remove_child(panel);
				}
				else {
					std::vector<std::string> rectAttributes = split(shapes[shapeIndex]->getShapeBaseAttributes(), " ");
					std::string fillAttr = shapes[shapeIndex]->getFill();
					rectAttributes.push_back(fillAttr);
					int attributeIndex = 0;
					for (pugi::xml_attribute attr : panel.attributes())
					{
						std::string attrValue = rectAttributes[attributeIndex];
						attr.set_value(attrValue.c_str());
						attributeIndex;
					}
					shapeIndex++;
				}
			}
			panel = next;
		}

		doc.save_file(fileName);
		if (shapeIndex < numberOfShapes) {
			appendNewShape(shapes, shapeIndex, numberOfShapes, fileName);
		}

		std::cout << "Successfully saved the changes to" << " " << fileName << std::endl;
	}
}

void loadDataFromFile(Shape** shapes, int* numberOfShapes, const char* fileName) {
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file(fileName);

	if (!result) {
		std::cout << "Successfully created " <<fileName<< std::endl;
	}
	else {
		std::cout << "Successfully opened " << fileName << std::endl;

		pugi::xml_node panels = doc.child("svg");

		for (pugi::xml_node panel = panels.first_child(); panel; panel = panel.next_sibling())
		{
			if (strcmp(panel.name(), "rect") == 0) {
				shapes[*numberOfShapes] = new Rectangle(panel.attribute("x").as_int(), panel.attribute("y").as_int(), panel.attribute("width").as_int(), panel.attribute("height").as_int(), panel.attribute("fill").as_string());
			}
			else if (strcmp(panel.name(), "circle") == 0) {
				shapes[*numberOfShapes] = new Circle(panel.attribute("r").as_int(), panel.attribute("cx").as_int(), panel.attribute("cy").as_int(), panel.attribute("fill").as_string());

			}
			else if (strcmp(panel.name(), "line") == 0) {
				shapes[*numberOfShapes] = new Line(panel.attribute("x1").as_int(), panel.attribute("y1").as_int(), panel.attribute("x2").as_int(), panel.attribute("y2").as_int(), panel.attribute("fill").as_string());
			}
			else if (strcmp(panel.name(), "ellipse") == 0) {
				shapes[*numberOfShapes] = new Ellipse(panel.attribute("rx").as_int(), panel.attribute("ry").as_int(), panel.attribute("cx").as_int(), panel.attribute("cy").as_int(), panel.attribute("fill").as_string());

			}
			(*numberOfShapes)++;
		}
	}
	doc.save_file(fileName);
}

int main()
{ 
	Shape** shapes = new Shape*[MAX_NUMBER_OF_SHAPES];
	int numberOfShapes = 0;
	
	std::string userChoice;
	
	std::string selectedOperation = "";
	std::string fileName = "";

	while (selectedOperation != "exit")
	{
		std::getline(std::cin, userChoice);

		std::string delimiter = " ";
		std::vector<std::string> selectedOption = split(userChoice, delimiter);
		selectedOperation = selectedOption.front();


		if (selectedOperation == "open") {
			if (selectedOption.size() != 2) {
				std::cout << "This operation expects one argument filename" << std::endl;
			}
			else {
				fileName = selectedOption[1];
				loadDataFromFile(shapes, &numberOfShapes, selectedOption[1].c_str());
			}
		}
		else if (selectedOperation == "close") {
			if (fileName == "") std::cout << "There is no opened file that should be closed" << std::endl;
			else if (selectedOption.size() != 1) {
				std::cout << "This operation does not expect arguments" << std::endl;
			}
			else {
				std::cout << "Successfully closed" <<" "<<fileName<< std::endl;
				fileName = "";

				for (int index = 0; index < numberOfShapes; index++) {
					delete shapes[index];
				}
				numberOfShapes = 0;
			}
		}
		else if (selectedOperation == "save") {
			if (fileName == "") std::cout << "There is no opened file! You should first open one" << std::endl;
			else if (selectedOption.size() != 1) {
				std::cout << "This operation does not expect arguments" << std::endl;
			}
			else saveFile(shapes, numberOfShapes, fileName.c_str());
		}
		else if (selectedOperation == "saveas") {
			if (fileName == "") std::cout << "There is no opened file! You should first open one" << std::endl;
			else if (selectedOption.size() != 2) {
				std::cout << "This operation expects one argument filename" << std::endl;
			}
			else saveFile(shapes, numberOfShapes, selectedOption[1].c_str());
		}
		else if (selectedOperation == "help") {
			if (selectedOption.size() != 1) {
				std::cout << "This operation does not expect arguments" << std::endl;
			}
			else {
				std::cout << "The following commands are supported :" << std::endl;
				std::cout << "open <file>						opens <file> " << std::endl;
				std::cout << "close							closes currently opened file" << std::endl;
				std::cout << "save							saves the currently open file" << std::endl;
				std::cout << "saveas <file>						saves the currently open file in <file>" << std::endl;
				std::cout << "print							prints all shapes" << std::endl;
				std::cout << "create <shapeType> shapeAttributes			creates new shape" << std::endl;
				std::cout << "within <option> optionAttributes			prints all shapes that are in selected option range" << std::endl;
				std::cout << "erase <n>						deletes n-th shape" << std::endl;
				std::cout << "translate [<n>] vertical=number horizontal=number	transletes n-th shape if n is passed or transletes all shapes" << std::endl;
				std::cout << "help							prints this information" << std::endl;
			}
		}
		else if (selectedOperation == "exit") {
			if (selectedOption.size() != 1) {
				std::cout << "This operation does not expect arguments" << std::endl;
			}
			else std::cout << "Exiting the program..." << std::endl;
		}
		else if (selectedOperation == "print") {
			if (fileName == "") std::cout << "There is no opened file! You should first open one" << std::endl;
			else if (selectedOption.size() != 1) {
				std::cout << "This operation does not expect arguments" << std::endl;
			}
			else printShapes(shapes, numberOfShapes);
		}
		else if (selectedOperation == "create") {
			if (fileName == "") std::cout << "There is no opened file! You should first open one" << std::endl;
			else if (selectedOption[1] == RECTANGLE) {
				std::vector<std::string> attributes(selectedOption.begin() + 2, selectedOption.end());
				if (attributes.size() != 5) {
					std::cout << "Incorrect number of attribues.Rectangle expects 5 attributes" << std::endl;
				}
				else createNewShape(selectedOption[1], attributes, shapes, &numberOfShapes);
			}
			else if (selectedOption[1] == CIRCLE) {
				std::vector<std::string> attributes(selectedOption.begin() + 2, selectedOption.end());
				if (attributes.size() != 4) {
					std::cout << "Incorrect number of attribues.Circle expects 4 attributes" << std::endl;
				}
				else createNewShape(selectedOption[1], attributes, shapes, &numberOfShapes);
			}
			else if (selectedOption[1] == ELLIPSE) {
				std::vector<std::string> attributes(selectedOption.begin() + 2, selectedOption.end());
				if (attributes.size() != 5) {
					std::cout << "Incorrect number of attribues.Ellipse expects 5 attributes" << std::endl;
				}
				else createNewShape(selectedOption[1], attributes, shapes, &numberOfShapes);
			}
			else if (selectedOption[1] == LINE) {
				std::vector<std::string> attributes(selectedOption.begin() + 2, selectedOption.end());
				if (attributes.size() != 5) {
					std::cout << "Incorrect number of attribues.Line expects 5 attributes" << std::endl;
				}
				else createNewShape(selectedOption[1], attributes, shapes, &numberOfShapes);
			}
			else std::cout << "Can not create figure of that type! You should select from `rectangle`, `circle`, `ellipse` or `line`";
		}
		else if (selectedOperation == "erase") {
			if (fileName == "") std::cout << "There is no opened file! You should first open one" << std::endl;
			else if (selectedOption.size() != 2) {
				std::cout << "Erase option expects one argument: number of shape you want to delete!" << std::endl;
			}
			else {
				int shapeNumber = convertStringToInteger(selectedOption[1]);
				deleteShape(shapeNumber, shapes, &numberOfShapes);
			}
		}
		else if (selectedOperation == "within") {
			if (fileName == "") std::cout << "There is no opened file! You should first open one" << std::endl;
			else if (selectedOption.size() != 5 && selectedOption.size() != 6)  std::cout << "Incorect number of attributes for selected option!" << std::endl;
			else if (selectedOption[1] == RECTANGLE) {
				std::vector<std::string> attributes(selectedOption.begin() + 2, selectedOption.end());
				if (attributes.size() != 4) {
					std::cout << "Incorrect number of attribues.Rectangle expects 4 attributes" << std::endl;
				}
				else within(shapes, numberOfShapes, selectedOption[1], prepareShapeCordinates(attributes));
			}
			else if (selectedOption[1] == CIRCLE) {
				std::vector<std::string> attributes(selectedOption.begin() + 2, selectedOption.end());
				if (attributes.size() != 3) {
					std::cout << "Incorrect number of attribues.Circle expects 3 attributes" << std::endl;
				}
				else within(shapes, numberOfShapes, selectedOption[1], prepareShapeCordinates(attributes));
			}
		}
		else if (selectedOperation == "translate") {
			if (fileName == "") std::cout << "There is no opened file! You should first open one" << std::endl;
			else if (selectedOption.size() != 3 && selectedOption.size() != 4) std::cout << "Incorect input for translate option! Try again." << std::endl;
			else if (selectedOption.size() == 3) {
				// Converting vertical and horizontal arguments from string to integer 
				std::string vertical = split(selectedOption[1], "=").back(); 
				int verticalMove = convertStringToInteger(vertical);
				std::string horizontal = split(selectedOption[2], "=").back();
				int horizontlMove = convertStringToInteger(horizontal);
				translate(shapes, numberOfShapes, verticalMove, horizontlMove);
			}
			else if (selectedOption.size() == 4) {
				// Converting vertical and horizontal arguments from string to integer 
				std::string vertical = split(selectedOption[2], "=").back();
				int verticalMove = convertStringToInteger(vertical);
				std::string horizontal = split(selectedOption[3], "=").back();
				int horizontlMove = convertStringToInteger(horizontal);
				int shapeNumber = convertStringToInteger(selectedOption[1]);
				translate(shapes, numberOfShapes, verticalMove, horizontlMove, shapeNumber);
			}
		}
		else std::cout << "You have selected unsupported operation. Type  `help`  to see all supported operations!" << std::endl;
	}


	//deleting dynamic allocated data
	for (int index = 0; index < numberOfShapes; index++) {
	delete shapes[index];
	}

	delete[] shapes;



	system("pause");
	return 0;

}