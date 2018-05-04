#pragma once
#include "stdafx.h"
#include "Figure.h"
#include "Polyline.h"

class myPolygon : public myPolyline
{
public:
	myPolygon();

	myPolygon(const vector<myPoint>&,
		RGB_Color stroke = 0,
		int strokeWidth = 1,
		float strokeOpacity = 1.0,
		RGB_Color fill = 0,
		float fillOpacity = 1.0,
		int transformOrder = 0,
		myPoint translate = 0,
		int rotate = 0);

	myPolygon(const vector<myPoint>&,
		const vector<char>& transformOrder,
		const vector<myPoint>& translate,
		const vector<char>& rotate,
		RGB_Color stroke = 0,
		int strokeWidth = 1,
		float strokeOpacity = 1.0,
		RGB_Color fill = 0,
		float fillOpacity = 1.0);

	myPolygon(xml_node<>*);

	virtual void setPointsData(const vector<myPoint>&);
	virtual void setPointsData(char*);
	virtual void convertFromCString(xml_attribute<>*);

	virtual void draw(CImg<unsigned char>&);
	virtual void draw(HDC&);

	virtual string getXmlCode();
	virtual ~myPolygon();
};