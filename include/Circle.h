#pragma once
#include "stdafx.h"
#include "Figure.h"

class myCircle : public FillFigure
{
public:
	myCircle();
	myCircle(myCircle*);
	myCircle(xml_node<>*);

	virtual void init();
	myPoint getCenter();
	void setCenter(myPoint);
	void setCenter(float, float);
	float getR();
	void setR(float);

	virtual void draw(CImg<unsigned char>&);
	virtual void draw(HDC&);

	virtual Figure* clone();
	virtual char* className();
	void setAttribute(char*, char*);
	void setByNode(xml_node<>*);
	void setByNodeAndAddTransform(xml_node<>*);

	virtual string getXmlCode();
	virtual ~myCircle();
};
