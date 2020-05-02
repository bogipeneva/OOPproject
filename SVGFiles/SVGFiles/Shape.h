#ifndef _SHAPE_H
#define _SHAPE_H
class Shape
{
private:
	char fill[50];
	char stroke[50];
	double fillOpacity;
	double strokeOpacity;
	int strokeWidth;
public:
	//constructor
	Shape(const char* _fill = "", const char* _stroke = "", double _fillOpacity = 0, double _strokeOpacity = 0, int _strokeWith = 20);

	//setters
	void setFill(const char*);
	void setStroke(const char*);
	void setFillOpacity(double);
	void setStrokeOpacity(double);
	void setStrokeWidth(int);

	//getters
	const char* getFill()const { return fill; };
	const char* getStroke()const { return stroke; };
	double getFillOpacity()const { return fillOpacity; };
	double getStrokeOpacity()const { return strokeOpacity; };
	int getStrokeWidth()const { return strokeWidth; };

	virtual void print()const;
	virtual void translate(int, int)=0;


};
#endif
