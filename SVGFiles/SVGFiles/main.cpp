#include<iostream>
#include<string.h>
#include "lib/src/pugixml.hpp"
#include "lib/src/pugixml.cpp"
#include "Rectangle.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Line.h"   

int main()
{

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

	for (int index = 0; index < shapesIndex; index++) {
		shapes[index]->print();
	}

	//deleting dynamic allocated data
	for (int index = 0; index < shapesIndex; index++) {
		delete shapes[index];
	}

	delete[] shapes;

	std::cout << std::endl;
	

	system("pause");
	return 0;

}