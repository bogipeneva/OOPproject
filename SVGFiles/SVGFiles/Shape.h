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


	virtual void print()const;
	virtual void translate(int, int)=0;


};
#endif
