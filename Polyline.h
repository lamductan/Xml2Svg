#pragma once
#include "stdafx.h"
#include "Figure.h"
#include "Line.h"

class myPolyline : public FillFigure
{
protected:
	vector<myPoint> m_pointData;
public:
	myPolyline();

	myPolyline(const vector<myPoint>&,
		RGB_Color stroke = 0,
		int strokeWidth = 1,
		float strokeOpacity = 1.0,
		RGB_Color fill = 0,
		float fillOpacity = 1.0,
		int transformOrder = 0,
		myPoint translate = 0,
		int rotate = 0);

	myPolyline(const vector<myPoint>&,
		const vector<char>& transformOrder,
		const vector<myPoint>& translate,
		const vector<char>& rotate,
		RGB_Color stroke = 0,
		int strokeWidth = 1,
		float strokeOpacity = 1.0,
		RGB_Color fill = 0,
		float fillOpacity = 1.0);

	myPolyline(xml_node<>*);

	virtual void setPointsData(const vector<myPoint>&);
	virtual void setPointsData(char*);
	virtual void convertFromCString(xml_attribute<>*);

	virtual void draw(CImg<unsigned char>&);
	virtual void draw(HDC&);
	virtual string getXmlCode();
	virtual ~myPolyline();

	friend ostream& operator<<(ostream&, const myPolyline&);
};