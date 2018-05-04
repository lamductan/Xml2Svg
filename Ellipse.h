#pragma once
#include "Figure.h"

class myEllipse : public FillFigure
{
protected:
	myPoint m_center;
	int m_rx;
	int m_ry;
public:
	myEllipse();

	myEllipse(myPoint center, int rx, int ry,
		RGB_Color stroke = 0,
		int strokeWidth = 0,
		float strokeOpacity = 1.0,
		RGB_Color fill = 0,
		float fillOpacity = 1.0,
		int transformOrder = 0,
		myPoint translate = 0,
		int rotate = 0);

	myEllipse(myPoint center, int rx, int ry,
		const vector<char>& transformOrder,
		const vector<myPoint>& translate,
		const vector<char>& rotate,
		RGB_Color stroke = 0,
		int strokeWidth = 0,
		float strokeOpacity = 1.0,
		RGB_Color fill = 0,
		float fillOpacity = 1.0);

	myEllipse(xml_node<>*);

	myPoint getCenter();
	void setCenter(myPoint);
	void setCenter(int, int);
	int getRx();
	void setRx(int);
	int getRy();
	void setRy(int);

	virtual void convertFromCString(xml_attribute<>*);

	virtual void draw(CImg<unsigned char>&);
	virtual void draw(HDC&);

	virtual string getXmlCode();
	virtual ~myEllipse();
};