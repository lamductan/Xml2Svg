#pragma once
#include "Figure.h"

class myEllipse : public FillFigure
{
public:
	myEllipse();
	myEllipse(myEllipse*);
	myEllipse(xml_node<>*);

	virtual void init();
	myPoint getCenter();
	void setCenter(myPoint);
	void setCenter(float, float);
	float getRx();
	void setRx(float);
	float getRy();
	void setRy(float);

	void setAttribute(char*, char*);
	void setByNode(xml_node<>*);
	void setByNodeAndAddTransform(xml_node<>*);

	virtual void draw(CImg<unsigned char>&);
	virtual void draw(HDC&);

	virtual Figure* clone();
	virtual char* className();

	virtual string getXmlCode();
	virtual ~myEllipse();
};