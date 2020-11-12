#pragma once
#include "stdafx.h"
#include "Stroke.h"
#include "Fill.h"
#include "Transformer.h"
using namespace std;

#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
using namespace rapidxml;

struct cmp_str
{
	bool operator()(char const *a, char const *b) const
	{
		return strcmp(a, b) < 0;
	}
};

class Figure
{
protected:
	static vector<Figure*> sampleObjects;
	map<char*, Attribute*, cmp_str> m_attributes;
	map<char*, float, cmp_str> m_ownAttributes;

	static void addSample(Figure*);
public:
	Figure();
	Figure(Figure*);
	//Figure(xml_node<>*);

	virtual void init();

	//Getter/Setter
	RGB_Color getStroke();
	void setStroke(RGB_Color);
	void setStroke(int stroke = 255);
	
	float getStrokeWidth();
	void setStrokeWidth(float);

	float getStrokeOpacity();
	void setStrokeOpacity(float);

	const vector<Transform*>& getTransform();
	void setTransform(const vector<Transform*>&);
	void addTransform(const vector<Transform*>&);
	//End Getter/Setter

	virtual void draw(CImg<unsigned char>&) = 0;
	virtual void draw(HDC&) = 0;

	//
	static Figure* createObject(char*);
	virtual char* className() = 0;
	virtual Figure* clone() = 0;
	//

	virtual void setAttribute(char*, char*) = 0;
	virtual void setByNode(xml_node<>*) = 0;
	virtual void setByNodeAndAddTransform(xml_node<>*) = 0;
	virtual void setAttribute(Figure*);

	virtual string getXmlCode();
	bool drawToFile(char*);
	bool removeFromFile(char*);
	virtual ~Figure();
};

class FillFigure : public Figure
{
public:
	FillFigure();
	FillFigure(FillFigure*);

	virtual void init();

	//Getter/Setter
	RGB_Color getFill();
	void setFill(RGB_Color);
	void setFill(int fill = 0);

	float getFillOpacity();
	void setFillOpacity(float);

	virtual void setAttribute(FillFigure*);
	virtual void setAttribute(Figure*);
	virtual void setByNode(xml_node<>*) = 0;

	virtual string getXmlCode();
	virtual ~FillFigure();
};