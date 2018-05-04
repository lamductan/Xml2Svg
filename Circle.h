#pragma once
#include "stdafx.h"
#include "Figure.h"

class myCircle : public FillFigure
{
protected:
	myPoint m_center;
	int m_r;
public:
	myCircle();

	myCircle(myPoint, int,
		RGB_Color stroke = 0,
		int strokeWidth = 0,
		float strokeOpacity = 1.0,
		RGB_Color fill = 0,
		float fillOpacity = 1.0,
		int transformOrder = 0,
		myPoint translate = 0,
		int rotate = 0);

	myCircle(myPoint, int,
		const vector<char>& transformOrder,
		const vector<myPoint>& translate,
		const vector<char>& rotate,
		RGB_Color stroke = 0,
		int strokeWidth = 0,
		float strokeOpacity = 1.0,
		RGB_Color fill = 0,
		float fillOpacity = 1.0);

	myCircle(xml_node<>*);

	myPoint getCenter();
	void setCenter(myPoint);
	void setCenter(int, int);
	int getR();
	void setR(int);

	virtual void convertFromCString(xml_attribute<>*);

	virtual void draw(CImg<unsigned char>&);
	virtual void draw(HDC&);

	virtual string getXmlCode();
	virtual ~myCircle();
};
