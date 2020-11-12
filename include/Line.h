#pragma once
#include "stdafx.h"
#include "Figure.h"

class myLine : public Figure
{
public:
	myLine();
	myLine(myLine*);
	myLine(xml_node<>*);
	myLine(Figure*);

	virtual void init();

	virtual void setPoints(myPoint, myPoint);
	myPoint getFirstPoint();
	myPoint getSecondPoint();
	
	void setAttribute(char*, char*);
	void setByNode(xml_node<>*);
	void setByNodeAndAddTransform(xml_node<>*);

	virtual void draw(CImg<unsigned char>&);
	virtual void draw(HDC&);

	virtual char* className();
	virtual Figure* clone();
	virtual string getXmlCode();
	virtual ~myLine();
};