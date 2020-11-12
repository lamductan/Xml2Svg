#include "stdafx.h"
#include "Stroke.h"

//Stroke
Stroke::Stroke() { this->m_stroke = 255; }

Stroke::Stroke(RGB_Color color)
{
	this->m_stroke = color;
}

const char* Stroke::getAttrName() { return "stroke"; }

RGB_Color Stroke::getValue() { return this->m_stroke; }
void Stroke::setValue(RGB_Color color) { this->m_stroke = color; }
void Stroke::setValue(int stroke) { this->m_stroke = stroke; }
void Stroke::setValue(char* charColor) { this->m_stroke.setColor(charColor); }

Stroke::~Stroke() {}

//StrokeWidth
StrokeWidth::StrokeWidth(float width)
{
	this->m_strokeWidth = width;
}

const char* StrokeWidth::getAttrName() { return "stroke-width"; }

float StrokeWidth::getValue() { return this->m_strokeWidth; }
void StrokeWidth::setValue(float width) { this->m_strokeWidth = width; }
void StrokeWidth::setValue(char* charWidth) { this->m_strokeWidth = atof(charWidth); }

StrokeWidth::~StrokeWidth() {}

//StrokeOpacity
StrokeOpacity::StrokeOpacity(float opacity)
{
	this->m_strokeOpacity = opacity;
}

const char* StrokeOpacity::getAttrName() { return "stroke-opacity"; }

float StrokeOpacity::getValue() { return this->m_strokeOpacity; }
void StrokeOpacity::setValue(float opacity) { this->m_strokeOpacity = opacity; }
void StrokeOpacity::setValue(char* charOpacity) { this->m_strokeOpacity = atof(charOpacity); }

StrokeOpacity::~StrokeOpacity() {}