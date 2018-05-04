#include "stdafx.h"
#include "Stroke.h"

//Stroke
Stroke::Stroke(RGB_Color color, int width, float opacity)
{
	this->m_stroke = color;
	this->m_strokeWidth = width;
	this->m_strokeOpacity = opacity;
}

RGB_Color Stroke::getStroke() { return this->m_stroke; }
void Stroke::setStroke(RGB_Color color) { this->m_stroke = color; }
int Stroke::getStrokeWidth() { return this->m_strokeWidth; }
void Stroke::setStrokeWidth(int width) { this->m_strokeWidth = width; }
float Stroke::getStrokeOpacity() { return this->m_strokeOpacity; }
void Stroke::setStrokeOpacity(float opacity) { this->m_strokeOpacity = opacity; }

string Stroke::getStrokeCode()
{
	ostringstream buffer;
	string Code = "stroke=";
	Code += this->m_stroke.getCode();
	Code += "stroke-width=\"";
	buffer << (int) this->m_strokeWidth;
	Code += buffer.str();
	buffer.str("");
	Code += "\" ";

	if (this->m_strokeOpacity != 1.0)
	{
		Code += "stroke-opacity=\"";
		buffer << this->m_strokeOpacity;
		Code += buffer.str();
		Code += "\" ";
	}
	return Code;
}

Stroke::~Stroke() {}