#include "stdafx.h"
#include "Fill.h"

//Fill
Fill::Fill() { this->m_fill = 0; }

Fill::Fill(RGB_Color color)
{
	this->m_fill = color;
}

const char* Fill::getAttrName() { return "fill"; }

RGB_Color Fill::getValue() { return this->m_fill; }
void Fill::setValue(RGB_Color color) { this->m_fill = color; }

void Fill::setValue(int fill) { this->m_fill = fill; }

void Fill::setValue(char* charColor)
{
	this->m_fill.setColor(charColor);
}

Fill::~Fill() {}

//FillOpacity
FillOpacity::FillOpacity(float opacity)
{
	this->m_fillOpacity = opacity;
}

const char* FillOpacity::getAttrName() { return "fill-opacity"; }

float FillOpacity::getValue() { return this->m_fillOpacity; }
void FillOpacity::setValue(float opacity) { this->m_fillOpacity = opacity; }
void FillOpacity::setValue(char* charOpacity)
{
	this->m_fillOpacity = atof(charOpacity);
}

FillOpacity::~FillOpacity() {}