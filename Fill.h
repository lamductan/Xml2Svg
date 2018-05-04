#pragma once
#include "stdafx.h"
#include "RGB.h"
#include "Attribute.h"

class Fill: public Attribute
{
protected:
	RGB_Color m_fill;
	float m_fillOpacity;
public:
	Fill(RGB_Color color = 0, float opacity = 1.0f);
	RGB_Color getFill();
	void setFill(RGB_Color);
	float getFillOpacity();
	void setFillOpacity(float);
	string getFillCode();
	virtual ~Fill();
};