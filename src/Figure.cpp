#include "stdafx.h"
#include "Figure.h"
#include "General.h"

//Figure
vector<Figure*> Figure::sampleObjects;

void Figure::addSample(Figure* pFig)
{
	if (pFig == NULL)
		return;
	int pos = sampleObjects.size();
	while (--pos >= 0)
	{
		Figure* obj = sampleObjects[pos];
		if (strcmp(pFig->className(), obj->className()) == 0)
			break;
	}
	if (pos < 0) sampleObjects.push_back(pFig);
}

void Figure::init()
{
	Attribute* stroke = new Stroke;
	Attribute* strokeOpacity = new StrokeOpacity;
	Attribute* strokeWidth = new StrokeWidth;
	Attribute* transform = new ListTransform;

	this->m_attributes.clear();
	this->m_attributes.insert(pair<char*, Attribute*>("stroke", stroke));
	this->m_attributes.insert(pair<char*, Attribute*>("stroke-opacity", strokeOpacity));
	this->m_attributes.insert(pair<char*, Attribute*>("stroke-width", strokeWidth));
	this->m_attributes.insert(pair<char*, Attribute*>("transform", transform));
}

Figure::Figure()
{
	this->init();
	this->setStroke();
	this->setStrokeOpacity(1.0f);
	this->setStrokeWidth(0.0f);
}

Figure::Figure(Figure* p)
{
	init();
	this->setAttribute(p);
}

//Getter/Setter

RGB_Color Figure::getStroke()
{
	return dynamic_cast<Stroke*>(this->m_attributes["stroke"])->getValue(); 
}

void Figure::setStroke(RGB_Color stroke) 
{ 
	dynamic_cast<Stroke*>(this->m_attributes["stroke"])->setValue(stroke); 
}

void Figure::setStroke(int stroke)
{
	dynamic_cast<Stroke*>(this->m_attributes["stroke"])->setValue(stroke);
}

float Figure::getStrokeWidth()
{ 
	return dynamic_cast<StrokeWidth*>(this->m_attributes["stroke-width"])->getValue(); 
}

void Figure::setStrokeWidth(float strokeWidth) 
{
	dynamic_cast<StrokeWidth*>(this->m_attributes["stroke-width"])->setValue(strokeWidth); 
}

float Figure::getStrokeOpacity()
{
	return dynamic_cast<StrokeOpacity*>(this->m_attributes["stroke-opacity"])->getValue(); 
}

void Figure::setStrokeOpacity(float strokeOpacity) 
{
	dynamic_cast<StrokeOpacity*>(this->m_attributes["stroke-opacity"])->setValue(strokeOpacity); 
}

const vector<Transform*>& Figure::getTransform()
{
	return dynamic_cast<ListTransform*>(this->m_attributes["transform"])->getValue();
}

void Figure::setTransform(const vector<Transform*>& listTransform)
{
	dynamic_cast<ListTransform*>(this->m_attributes["transform"])->setValue(listTransform);
}

void Figure::addTransform(const vector<Transform*>& listTransform)
{
	dynamic_cast<ListTransform*>(this->m_attributes["transform"])->addValue(listTransform);
}

void Figure::setAttribute(Figure* p)
{
	this->setStroke(p->getStroke());
	this->setStrokeOpacity(p->getStrokeOpacity());
	this->setStrokeWidth(p->getStrokeWidth());
	this->setTransform(p->getTransform());
}

//End Getter/Setter

Figure::~Figure() 
{
	for (map<char*, Attribute*>::iterator it = this->m_attributes.begin(); it != this->m_attributes.end(); ++it)
	{
		delete it->second;
	}
	this->m_attributes.clear();
}

//Fill Figure
FillFigure::FillFigure() : Figure()
{
	init();
	this->setFill();
	this->setFillOpacity(1.0f);
}

FillFigure::FillFigure(FillFigure* p) : Figure(p)
{
	init();
	this->setFill(p->getFill());
	this->setFillOpacity(p->getFillOpacity());
}

void FillFigure::init()
{
	Fill* pfill = new Fill;
	FillOpacity* pfillOpacity = new FillOpacity;
	this->m_attributes.insert(pair<char*, Attribute*>("fill", pfill));
	this->m_attributes.insert(pair<char*, Attribute*>("fill-opacity", pfillOpacity));
}

//Getter/Setter
RGB_Color FillFigure::getFill()
{
	return dynamic_cast<Fill*>(this->m_attributes["fill"])->getValue();
}

void FillFigure::setFill(RGB_Color fill)
{
	dynamic_cast<Fill*>(this->m_attributes["fill"])->setValue(fill);
}

void FillFigure::setFill(int fill)
{
	dynamic_cast<Fill*>(this->m_attributes["fill"])->setValue(fill);
}

float FillFigure::getFillOpacity()
{
	return dynamic_cast<FillOpacity*>(this->m_attributes["fill-opacity"])->getValue();
}

void FillFigure::setFillOpacity(float fillOpacity)
{
	dynamic_cast<FillOpacity*>(this->m_attributes["fill-opacity"])->setValue(fillOpacity);
}
//End Getter/Setter

Figure* Figure::createObject(char* clsName)
{
	if (clsName == NULL)
		return NULL;
	int pos = sampleObjects.size();
	while (--pos >= 0)
	{
		Figure* obj = sampleObjects[pos];
		if (obj == NULL)
			continue;
		if (strcmp(clsName, obj->className()) == 0)
			break;
	}
	if (pos >= 0)
		return sampleObjects[pos]->clone();
	else
		return NULL;
}

void FillFigure::setAttribute(FillFigure* p)
{
	Figure::setAttribute(p);
	this->setFill(p->getFill());
	this->setFillOpacity(p->getFillOpacity());
}

void FillFigure::setAttribute(Figure* p)
{
	if (dynamic_cast<FillFigure*>(p))
		this->setAttribute(dynamic_cast<FillFigure*>(p));
	else Figure::setAttribute(p);
}

FillFigure::~FillFigure() {}