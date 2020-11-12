#pragma once
#include "stdafx.h"
#include "Figure.h"
#include "Polyline.h"

class myPolygon : public myPolyline
{
public:
	myPolygon();
	myPolygon(myPolygon*);
	myPolygon(xml_node<>*);

	virtual void setPointsData(const vector<myPoint>&);
	virtual void setPointsData(char*);

	virtual void draw(CImg<unsigned char>&);
	virtual void draw(HDC&);

	virtual char* className();
	virtual Figure* clone();

	virtual string getXmlCode();
	virtual ~myPolygon();
};