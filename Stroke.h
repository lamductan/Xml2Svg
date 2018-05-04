#pragma once
#include "stdafx.h"
#include "RGB.h"

class Stroke
{
protected:
	RGB_Color m_stroke;
	int m_strokeWidth;
	float m_strokeOpacity;
public:
	Stroke(RGB_Color color = 0, int width = 1, float opacity = 1.0f);
	RGB_Color getStroke();
	void setStroke(RGB_Color);
	int getStrokeWidth();
	void setStrokeWidth(int);
	float getStrokeOpacity();
	void setStrokeOpacity(float);
	string getStrokeCode();
	virtual ~Stroke();
};