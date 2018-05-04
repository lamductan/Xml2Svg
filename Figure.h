#pragma once
#include "stdafx.h"
#include "CImg.h"
#include "Stroke.h"
#include "Fill.h"
#include "Transformer.h"
using namespace std;
using namespace cimg_library;

#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
using namespace rapidxml;

void removeLastCharacters(char* fileName, int charsToDelete = 7);

class Figure : public Stroke, public Transformer
{
public:
	Figure(RGB_Color stroke = 0,
		int strokeWidth = 1,
		float strokeOpacity = 1.0f,
		char transformOrder = 0,
		myPoint translate = 0,
		char rotate = 0);

	Figure( const vector<char>& transformOrder,
		const vector<myPoint>& translate,
		const vector<char>& rotate,
		RGB_Color stroke = 0,
		int strokeWidth = 1,
		float strokeOpacity = 1.0f);

	Figure(xml_node<>*);

	virtual void convertFromCString(xml_attribute<>*);

	virtual void draw(CImg<unsigned char>&) = 0;
	virtual void draw(HDC&) = 0;

	//virtual Figure* clone() = 0;

	virtual string getXmlCode();
	bool drawToFile(char*);
	bool removeFromFile(char*);
	virtual ~Figure();
};

class FillFigure : public Figure, public Fill
{
public:
	FillFigure(RGB_Color stroke = 0,
		int strokeWidth = 1,
		float strokeOpacity = 1.0f,
		RGB_Color fill = 0,
		float fillOpacity = 1.0f,
		char transformOrder = 0,
		myPoint translate = 0,
		char rotate = 0);

	FillFigure(const vector<char>& transformOrder,
		const vector<myPoint>& translate,
		const vector<char>& rotate,
		RGB_Color stroke = 0,
		int strokeWidth = 1,
		float strokeOpacity = 1.0f,
		RGB_Color fill = 0,
		float fillOpacity = 1.0f);

	virtual void convertFromCString(xml_attribute<>*);

	virtual string getXmlCode();
	virtual ~FillFigure();
};