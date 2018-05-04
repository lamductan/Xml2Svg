#pragma once
#include "stdafx.h"
#include "Figure.h"

class myLine : public Figure
{
protected:
	myPoint m_firstPoint;
	myPoint m_secondPoint;
public:
	myLine();

	myLine(myPoint, myPoint,
		RGB_Color stroke = 0,
		int strokeWidth = 1,
		float strokeOpacity = 1.0,
		int transformOrder = 0,
		myPoint translate = 0,
		int rotate = 0);

	myLine(myPoint, myPoint,
		const vector<char>& transformOrder,
		const vector<myPoint>& translate,
		const vector<char>& rotate,
		RGB_Color stroke = 0,
		int strokeWidth = 1,
		float strokeOpacity = 1.0);

	myLine(xml_node<>*);

	virtual void setPoints(myPoint, myPoint);
	virtual void convertFromCString(xml_attribute<>*);

	virtual void draw(CImg<unsigned char>&);
	virtual void draw(HDC&);

	virtual string getXmlCode();
	virtual ~myLine();
};