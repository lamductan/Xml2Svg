#pragma once
#include "stdafx.h"

struct RGB_Color
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;

	RGB_Color(int red = 0, int green = 0, int blue = 0);
	RGB_Color& operator=(int);
	string getCode();
	RGB_Color& setColor(char*);
	virtual ~RGB_Color();
};

int convert_char_to_int(char*, int, int, const char endCharacter = '\0');
void convert_RGB_to_unsigned_char(unsigned char*, const RGB_Color&);