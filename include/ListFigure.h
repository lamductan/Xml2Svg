#pragma once

#include "stdafx.h"
#include "Figure.h"

class ListFigure
{
protected:
	vector<Figure*> m_figures;
public:
	ListFigure();
	INT readXML(char* fileName);
	void draw(CImg<unsigned char>&);
	void draw(HDC&);
	virtual ~ListFigure();
};