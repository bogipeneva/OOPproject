#include<iostream>
#include "lib/src/pugixml.hpp"
#include "lib/src/pugixml.cpp"
#include "Rectangle.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Line.h"   

int main()
{
	/*
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("fig.svg");

	pugi::xml_node panels = doc.child("svg");

	std::cout << panels.name() << std::endl;
	for (pugi::xml_node panel = panels.first_child(); panel; panel = panel.next_sibling())
	{
		std::cout << panel.name() << std::endl;

		for (pugi::xml_attribute attr = panel.first_attribute(); attr; attr = attr.next_attribute())
		{
			std::cout << " " << attr.name() << "=" << attr.value() << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	*/

	Line e;
	e.print();
	system("pause");
	return 0;

}