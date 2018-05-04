#pragma once
#include "stdafx.h"
#include "Figure.h"
#include "Polygon.h"

class myRectangle : public FillFigure
{
protected:
	myPoint m_topLeft;
	int m_width;
	int m_height;
public:
	myRectangle();

	myRectangle(myPoint, int, int,
		RGB_Color stroke = 0,
		int strokeWidth = 0,
		float strokeOpacity = 1.0,
		RGB_Color fill = 0,
		float fillOpacity = 1.0,
		int transformOrder = 0,
		myPoint translate = 0,
		int rotate = 0);

	myRectangle(myPoint, int, int,
		const vector<char>& transformOrder,
		const vector<myPoint>& translate,
		const vector<char>& rotate,
		RGB_Color stroke = 0,
		int strokeWidth = 0,
		float strokeOpacity = 1.0,
		RGB_Color fill = 0,
		float fillOpacity = 1.0);

	myRectangle(xml_node<>*);

	myPoint getTopLeft();
	void setTopLeft(myPoint);
	void setTopLeft(int, int);

	virtual void convertFromCString(xml_attribute<>*);

	virtual void draw(CImg<unsigned char>&);
	virtual void draw(HDC&);

	virtual string getXmlCode();
	virtual ~myRectangle();
};