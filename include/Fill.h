#pragma once
#include "stdafx.h"
#include "RGB.h"
#include "Attribute.h"

class Fill: public Attribute
{
protected:
	RGB_Color m_fill;	
public:
	Fill();
	Fill(RGB_Color color);
	virtual const char* getAttrName();
	RGB_Color getValue();
	void setValue(RGB_Color);
	void setValue(int fill = 255);
	void setValue(char*);
	string getFillCode();
	virtual ~Fill();
};

class FillOpacity: public Attribute
{
protected:
	float m_fillOpacity;
public:
	FillOpacity(float opacity = 1.0f);
	virtual const char* getAttrName();
	float getValue();
	void setValue(float);
	void setValue(char*);
	string getFillOpacityCode();
	virtual ~FillOpacity();
};