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
	myPolyline(myPolyline*);
	myPolyline(xml_node<>*);

	virtual void setPointsData(const vector<myPoint>&);
	virtual void setPointsData(char*);

	virtual void draw(CImg<unsigned char>&);
	virtual void draw(HDC&);
	virtual string getXmlCode();
	virtual ~myPolyline();

	virtual char* className();
	virtual Figure* clone();
	void setAttribute(char*, char*);
	void setByNode(xml_node<>*);
	void setByNodeAndAddTransform(xml_node<>*);

	friend ostream& operator<<(ostream&, const myPolyline&);
};