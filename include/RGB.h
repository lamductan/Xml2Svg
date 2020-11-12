#pragma once
#include "stdafx.h"

struct RGB_Color
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;

	RGB_Color() {};
	RGB_Color(int red, int green, int blue);
	RGB_Color& operator=(int);
	string getCode();
	RGB_Color& setColor(char*);
	virtual ~RGB_Color();
};

