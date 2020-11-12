#pragma once
#include "stdafx.h"
#include "RGB.h"
#include "Attribute.h"

class Stroke: public Attribute
{
protected:
	RGB_Color m_stroke;
public:
	Stroke();
	Stroke(RGB_Color color);
	virtual const char* getAttrName();
	RGB_Color getValue();	
	void setValue(RGB_Color);
	void setValue(int stroke = 255);
	void setValue(char*);
	string getStrokeCode();
	virtual ~Stroke();
};

class StrokeWidth : public Attribute
{
protected:
	float m_strokeWidth;
public:
	StrokeWidth(float width = 1.0f);
	virtual const char* getAttrName();
	float getValue();
	void setValue(float);
	void setValue(char*);
	string getStrokeWidthCode();
	virtual ~StrokeWidth();
};

class StrokeOpacity : public Attribute
{
protected:
	float m_strokeOpacity;
public:
	StrokeOpacity(float opacity = 1.0f);
	virtual const char* getAttrName();
	float getValue();
	void setValue(float);
	void setValue(char*);
	string getStrokeOpacityCode();
	virtual ~StrokeOpacity();
};