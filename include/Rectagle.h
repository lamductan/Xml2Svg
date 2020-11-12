#pragma once
#include "stdafx.h"
#include "Figure.h"
#include "Polygon.h"

class myRectangle : public FillFigure
{
public:
	myRectangle();
	myRectangle(myRectangle*);
	myRectangle(xml_node<>*);

	virtual void init();
	myPoint getTopLeft();
	void setTopLeft(myPoint);
	void setTopLeft(float, float);

	float getWidth();
	void setWidth(float);
	float getHeight();
	void setHeight(float);

	void setAttribute(char*, char*);

	virtual void draw(CImg<unsigned char>&);
	virtual void draw(HDC&);

	virtual char* className();
	virtual Figure* clone();
	void setByNode(xml_node<>*);
	void setByNodeAndAddTransform(xml_node<>*);

	virtual string getXmlCode();
	virtual ~myRectangle();
};