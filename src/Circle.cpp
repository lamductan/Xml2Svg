#include "stdafx.h"
#include "Circle.h"
#include "Ellipse.h"
#include "General.h"

//myCircle
myCircle::myCircle() : FillFigure()
{
	init();
	this->setCenter(0.0f);
	this->setR(50.0f);
	addSample(this);
}

myCircle::myCircle(myCircle* p): FillFigure(p)
{
	this->m_ownAttributes = p->m_ownAttributes;
}

myCircle::myCircle(xml_node<>* node)
{
	FillFigure::init();
	init();

	for (xml_attribute<> *attr = node->first_attribute();
		attr; attr = attr->next_attribute())
	{
		this->setAttribute(attr->name(), attr->value());
	}
	addSample(this);
}

void myCircle::init()
{
	this->m_ownAttributes.insert(pair<char*, float>{"cx", 0.0f});
	this->m_ownAttributes.insert(pair<char*, float>{"cy", 0.0f});
	this->m_ownAttributes.insert(pair<char*, float>{"r", 0.0f});
}

myPoint myCircle::getCenter()
{
	myPoint center(this->m_ownAttributes["cx"], this->m_ownAttributes["cy"]);
	return center;
}
void myCircle::setCenter(myPoint center)
{
	this->m_ownAttributes["cx"] = center.x;
	this->m_ownAttributes["cy"] = center.y;
}

void myCircle::setCenter(float x, float y)
{
	this->m_ownAttributes["cx"] = x;
	this->m_ownAttributes["cy"] = y;
}

float myCircle::getR() { return this->m_ownAttributes["r"]; }
void myCircle::setR(float r) { this->m_ownAttributes["r"] = r; }

void myCircle::draw(CImg<unsigned char>& img)
{
	myEllipse* ellipse = new myEllipse;
	ellipse->setFill(this->getFill());
	ellipse->setFillOpacity(this->getFillOpacity());
	ellipse->setStroke(this->getStroke());
	ellipse->setStrokeOpacity(this->getStrokeOpacity());
	ellipse->setStrokeWidth(this->getStrokeWidth());
	ellipse->setTransform(this->getTransform());
	ellipse->setRx(this->getR());
	ellipse->setRy(this->getR());
	ellipse->setCenter(this->getCenter());

	ellipse->draw(img);
	delete ellipse;
}

void myCircle::draw(HDC& hdc)
{
	myEllipse* ellipse = new myEllipse;
	ellipse->setFill(this->getFill());
	ellipse->setFillOpacity(this->getFillOpacity());
	ellipse->setStroke(this->getStroke());
	ellipse->setStrokeOpacity(this->getStrokeOpacity());
	ellipse->setStrokeWidth(this->getStrokeWidth());
	ellipse->setTransform(this->getTransform());
	ellipse->setRx(this->getR());
	ellipse->setRy(this->getR());
	ellipse->setCenter(this->getCenter());

	ellipse->draw(hdc);
	delete ellipse;
}

void myCircle::setAttribute(char* attr_name, char* attr_value)
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

void myCircle::setByNode(xml_node<>* node)
{
	for (xml_attribute<> *attr = node->first_attribute();
		attr; attr = attr->next_attribute())
	{
		this->setAttribute(attr->name(), attr->value());
	}
}

void myCircle::setByNodeAndAddTransform(xml_node<>* node)
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

char* myCircle::className() { return "circle"; }

Figure* myCircle::clone() { return new myCircle(this); }

myCircle::~myCircle() {}