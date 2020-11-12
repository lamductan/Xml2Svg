#include "stdafx.h"
#include "Rectagle.h"
#include "General.h"

//myRectangle
myRectangle::myRectangle() : FillFigure()
{
	init();
	this->setTopLeft(0, 0);
	this->setHeight(50);
	this->setWidth(50);
	addSample(this);
}

myRectangle::myRectangle(myRectangle* p) : FillFigure(p)
{
	init();
	this->m_ownAttributes = p->m_ownAttributes;
}

myRectangle::myRectangle(xml_node<>* node)
{
	FillFigure::init();
	init();

	for (xml_attribute<> *attr = node->first_attribute();
		attr; attr = attr->next_attribute())
	{
		this->setAttribute(attr->name(), attr->value());
	}
}

void myRectangle::init()
{
	this->m_ownAttributes.insert(pair<char*, float>{"x", 0.0f});
	this->m_ownAttributes.insert(pair<char*, float>{"y", 0.0f});
	this->m_ownAttributes.insert(pair<char*, float>{"width", 0.0f});
	this->m_ownAttributes.insert(pair<char*, float>{"height", 0.0f});
}

myPoint myRectangle::getTopLeft()
{
	myPoint topLeft(this->m_ownAttributes["x"], this->m_ownAttributes["y"]);
	return topLeft;
}

void myRectangle::setTopLeft(myPoint topLeft)
{
	this->m_ownAttributes["x"] = topLeft.x;
	this->m_ownAttributes["y"] = topLeft.y;
}

void myRectangle::setTopLeft(float x, float y)
{
	this->m_ownAttributes["x"] = x;
	this->m_ownAttributes["y"] = y;
}

float myRectangle::getWidth() { return this->m_ownAttributes["width"]; }
void myRectangle::setWidth(float width) { this->m_ownAttributes["width"] = width; }
float myRectangle::getHeight() { return this->m_ownAttributes["height"]; }
void myRectangle::setHeight(float height) { this->m_ownAttributes["height"] = height; }

void myRectangle::draw(CImg<unsigned char>& img)
{
	vector<myPoint> v;
	v.push_back(this->getTopLeft());
	v.push_back(v.back().translate(this->getWidth(), 0));
	v.push_back(v.back().translate(0, this->getHeight()));
	v.push_back(v.back().translate(-this->getWidth(), 0));

	myPolygon* tmpPolygon = new myPolygon;
	tmpPolygon->setPointsData(v);
	tmpPolygon->setTransform(this->getTransform());
	tmpPolygon->setStroke(this->getStroke());
	tmpPolygon->setStrokeWidth(this->getStrokeWidth());
	tmpPolygon->setStrokeOpacity(this->getStrokeOpacity());
	tmpPolygon->setFill(this->getFill());
	tmpPolygon->setFillOpacity(this->getFillOpacity());

	tmpPolygon->draw(img);
	delete tmpPolygon;
}

void myRectangle::draw(HDC& hdc)
{
	vector<myPoint> v;
	v.push_back(this->getTopLeft());
	v.push_back(v.back().translate(this->getWidth(), 0));
	v.push_back(v.back().translate(0, this->getHeight()));
	v.push_back(v.back().translate(-this->getWidth(), 0));

	myPolygon* tmpPolygon = new myPolygon;
	tmpPolygon->setPointsData(v);
	tmpPolygon->setTransform(this->getTransform());
	tmpPolygon->setStroke(this->getStroke());
	tmpPolygon->setStrokeWidth(this->getStrokeWidth());
	tmpPolygon->setStrokeOpacity(this->getStrokeOpacity());
	tmpPolygon->setFill(this->getFill());
	tmpPolygon->setFillOpacity(this->getFillOpacity());

	tmpPolygon->draw(hdc);
	delete tmpPolygon;
}

void myRectangle::setAttribute(char* attr_name, char* attr_value)
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

void myRectangle::setByNode(xml_node<>* node)
{
	for (xml_attribute<> *attr = node->first_attribute();
		attr; attr = attr->next_attribute())
	{
		this->setAttribute(attr->name(), attr->value());
	}
}

void myRectangle::setByNodeAndAddTransform(xml_node<>* node)
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

char* myRectangle::className() { return "rect"; }

Figure* myRectangle::clone() { return new myRectangle(this); }

myRectangle::~myRectangle() {}