#include "stdafx.h"
#include "Fill.h"

//Fill
Fill::Fill(RGB_Color color, float opacity)
{
	this->m_fill = color;
	this->m_fillOpacity = opacity;
}

RGB_Color Fill::getFill() { return this->m_fill; }
void Fill::setFill(RGB_Color color) { this->m_fill = color; }
float Fill::getFillOpacity() { return this->m_fillOpacity; }
void Fill::setFillOpacity(float opacity) { this->m_fillOpacity = opacity; }

string Fill::getFillCode()
{
	string Code;
	ostringstream buffer;
	Code += "fill=";
	Code += this->m_fill.getCode();

	if (this->m_fillOpacity != 1.0)
	{
		Code += "fill-opacity=\"";
		buffer << this->m_fillOpacity;
		Code += buffer.str();
		Code += "\" ";
	}
	return Code;
}

Fill::~Fill() {}