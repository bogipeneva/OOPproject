#ifndef _SHAPE_H
#define _SHAPE_H

class Shape
{
private:
	char fill[20];
public:
	//constructor
	Shape(const char* _fill = "");

	//setter
	void setFill(const char*);


	//getters
	const char* getFill()const { return fill; };
	virtual char* getShapeType()const = 0;

	virtual void print()const;
	virtual std::string getShapeBaseAttributes()const=0;
	virtual void translate(int, int)=0;
	virtual bool withinRectangle(int, int, int, int) = 0;
	virtual bool withinCircle(int, int, int) = 0;



};
#endif
