#include "stdafx.h"
#include "Ellipse.h"
#include "General.h"

//myEllipse
myEllipse::myEllipse() : FillFigure()
{
	init();
	this->setCenter(0);
	this->setRx(50);
	this->setRy(50);
	addSample(this);
}

myEllipse::myEllipse(myEllipse* p) : FillFigure(p)
{
	init();
	this->m_ownAttributes = p->m_ownAttributes;
}

myEllipse::myEllipse(xml_node<>* node)
{
	FillFigure::init();
	init();

	for (xml_attribute<> *attr = node->first_attribute();
		attr; attr = attr->next_attribute())
	{
		this->setAttribute(attr->name(), attr->value());
	}
}

void myEllipse::init()
{
	this->m_ownAttributes.insert(pair<char*, float>{"cx", 0});
	this->m_ownAttributes.insert(pair<char*, float>{"cy", 0});
	this->m_ownAttributes.insert(pair<char*, float>{"rx", 0});
	this->m_ownAttributes.insert(pair<char*, float>{"ry", 0});
}

myPoint myEllipse::getCenter()
{
	myPoint center(this->m_ownAttributes["cx"], this->m_ownAttributes["cy"]);
	return center;
}
void myEllipse::setCenter(myPoint center)
{
	this->m_ownAttributes["cx"] = center.x;
	this->m_ownAttributes["cy"] = center.y;
}

void myEllipse::setCenter(float x, float y)
{
	this->m_ownAttributes["cx"] = x;
	this->m_ownAttributes["cy"] = y;
}

float myEllipse::getRx() { return this->m_ownAttributes["rx"]; }
void myEllipse::setRx(float rx) { this->m_ownAttributes["rx"] = rx; }

float myEllipse::getRy() { return this->m_ownAttributes["ry"]; }
void myEllipse::setRy(float ry) { this->m_ownAttributes["ry"] = ry; }

void myEllipse::draw(CImg<unsigned char>& img)
{
	unsigned char fillColor[3];
	convert_RGB_to_unsigned_char(fillColor, this->getFill());

	unsigned char strokeColor[3];
	convert_RGB_to_unsigned_char(strokeColor, this->getStroke());

	myPoint center(this->getCenter().transform(this->getTransform()));
	myPoint A(this->getCenter().translate(-this->getRx(), 0).transform(this->getTransform()));
	myPoint B(this->getCenter().translate(0, -this->getRy()).transform(this->getTransform()));

	float angle = atan((1.0*(center.y - A.y)) / (1.0*(center.x - A.x))) * 180.0 / acos(-1);
	float r1 = center.calcDistance(A);
	float r2 = center.calcDistance(B);

	img.draw_ellipse(center.x, center.y, r1 - this->getStrokeWidth(), r2 - this->getStrokeWidth(), angle, fillColor, this->getFillOpacity());
	for (int i = 0; i < this->getStrokeWidth(); ++i)
		img.draw_ellipse(center.x, center.y, r1 - i, r2 - i, angle, strokeColor, this->getStrokeOpacity(), 1);
}

void myEllipse::draw(HDC& hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(BYTE(this->getStrokeOpacity() * 255), this->getStroke().red, this->getStroke().green, this->getStroke().blue), this->getStrokeWidth());
	SolidBrush solidBrush(Color(BYTE(this->getFillOpacity() * 255), this->getFill().red, this->getFill().green, this->getFill().blue));

	myPoint topLeft = this->getCenter().translate(-this->getRx(), -this->getRy());

	Matrix* rTransMatrix = dynamic_cast<ListTransform*>(this->m_attributes["transform"])->getReverseMatrix();
	Matrix* transMatrix = dynamic_cast<ListTransform*>(this->m_attributes["transform"])->getMatrix();

	graphics.SetTransform(transMatrix);
	graphics.DrawEllipse(&pen, topLeft.x, topLeft.y, 2 * this->getRx(), 2 * this->getRy());
	graphics.FillEllipse(&solidBrush, topLeft.x, topLeft.y, 2 * this->getRx(), 2 * this->getRy());
	graphics.SetTransform(rTransMatrix);

	delete rTransMatrix;
	delete transMatrix;
}

void myEllipse::setAttribute(char* attr_name, char* attr_value)
{
	map<char*, Attribute*>::iterator it1;
	map<char*, float>::iterator      it2;

	it1 = this->m_attributes.find(attr_name);
	if (it1 != this->m_attributes.end())
	{
		it1->second->setValue(attr_value);
	}
	else
	{
		it2 = this->m_ownAttributes.find(attr_name);
		if (it2 != this->m_ownAttributes.end())
		{
			it2->second = atof(attr_value);
		}
	}
}

void myEllipse::setByNode(xml_node<>* node)
{
	for (xml_attribute<> *attr = node->first_attribute();
		attr; attr = attr->next_attribute())
	{
		this->setAttribute(attr->name(), attr->value());
	}
}

void myEllipse::setByNodeAndAddTransform(xml_node<>* node)
{
	for (xml_attribute<> *attr = node->first_attribute();
		attr; attr = attr->next_attribute())
	{
		if (strcmp(attr->name(), "transform") != 0)
			this->setAttribute(attr->name(), attr->value());
		else
		{
			Figure* pFig = Figure::createObject("line");
			pFig->setAttribute(attr->name(), attr->value());
			this->addTransform(pFig->getTransform());
			delete pFig;
		}
	}
}

char* myEllipse::className() { return "ellipse"; }

Figure* myEllipse::clone() { return new myEllipse(this); }

myEllipse::~myEllipse() {}