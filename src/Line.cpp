#include "stdafx.h"
#include "Line.h"
#include "General.h"

//myLine
myLine::myLine(): Figure() { 
	init();
	addSample(this);
}

myLine::myLine(myLine* p) : Figure(p)
{
	init();
	this->m_ownAttributes = p->m_ownAttributes;
}

myLine::myLine(xml_node<>* node)
{
	Figure::init();
	init();

	for (xml_attribute<> *attr = node->first_attribute();
		attr; attr = attr->next_attribute())
	{
		this->setAttribute(attr->name(), attr->value());
	}
}

myLine::myLine(Figure* p): Figure(p) {}

void myLine::init()
{
	this->m_ownAttributes.insert(pair<char*, float>{"x1", 0.0f});
	this->m_ownAttributes.insert(pair<char*, float>{"y1", 0.0f});
	this->m_ownAttributes.insert(pair<char*, float>{"x2", 0.0f});
	this->m_ownAttributes.insert(pair<char*, float>{"y2", 0.0f});
}

void myLine::setPoints(myPoint firstPoint, myPoint secondPoint)
{
	this->m_ownAttributes["x1"] = firstPoint.x;
	this->m_ownAttributes["y1"] = firstPoint.y;
	this->m_ownAttributes["x2"] = secondPoint.x;
	this->m_ownAttributes["y2"] = secondPoint.y;
}

myPoint myLine::getFirstPoint()
{
	myPoint firstPoint(this->m_ownAttributes["x1"], this->m_ownAttributes["y1"]);
	return firstPoint;
}

myPoint myLine::getSecondPoint()
{
	myPoint secondPoint(this->m_ownAttributes["x2"], this->m_ownAttributes["y2"]);
	return secondPoint;
}

void myLine::draw(CImg<unsigned char>& img)
{
	unsigned char color[3];
	convert_RGB_to_unsigned_char(color, this->getStroke());
	
	myPoint firstPoint = this->getFirstPoint().transform(this->getTransform());
	myPoint secondPoint = this->getSecondPoint().transform(this->getTransform());

	for (int i = 0; i < this->getStrokeWidth(); ++i)
		img.draw_line(firstPoint.x + i, firstPoint.y + i, secondPoint.x + i, secondPoint.y + i,
			color, this->getStrokeOpacity());
}

void myLine::draw(HDC& hdc)
{
	if (this->getStrokeWidth() != 0.0f)
	{
		Graphics graphics(hdc);

		Pen pen(Color(BYTE(this->getStrokeOpacity() * 255), this->getStroke().red, this->getStroke().green, this->getStroke().blue), this->getStrokeWidth());

		myPoint firstPoint = this->getFirstPoint().transform(this->getTransform());
		myPoint secondPoint = this->getSecondPoint().transform(this->getTransform());

		graphics.DrawLine(&pen, firstPoint.x, firstPoint.y, secondPoint.x, secondPoint.y);
	}
}

void myLine::setAttribute(char* attr_name, char* attr_value)
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

void myLine::setByNode(xml_node<>* node)
{
	for (xml_attribute<> *attr = node->first_attribute();
		attr; attr = attr->next_attribute())
	{
		this->setAttribute(attr->name(), attr->value());
	}
}

void myLine::setByNodeAndAddTransform(xml_node<>* node)
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

char* myLine::className() { return "line"; }

Figure* myLine::clone() { return new myLine(this); }

myLine::~myLine() {}
