#include "stdafx.h"
#include "RGB.h"

//RGB_Color
RGB_Color::RGB_Color(int red, int green, int blue)
{
	this->red = (unsigned char)(red % 256);
	this->green = (unsigned char)(green % 256);
	this->blue = (unsigned char)(blue % 256);
}

RGB_Color& RGB_Color::operator=(int value)
{
	this->red = this->green = this->blue = (unsigned char)value;
	return *this;
}

string RGB_Color::getCode()
{
	ostringstream buffer;
	string Code = "\"rgb(";

	buffer << (int) this->red;
	Code += buffer.str();
	buffer.str("");
	Code += ",";

	buffer << (int) this->green;
	Code += buffer.str();
	buffer.str("");
	Code += ",";

	buffer << (int) this->blue;
	Code += buffer.str();

	Code += ")\" ";
	return Code;
}

RGB_Color& RGB_Color::setColor(char* charColor)
{
	int value = 0;
	char a[4];
	a[3] = '\0';
	int cnt = 0, cur = 0;
	for (int i = 4; i < strlen(charColor); ++i)
		if (charColor[i] == ' ') continue;
		else if (charColor[i] == ',')
		{
			value = atoi(a);
			if (cnt == 0) this->red = (unsigned char)value;
			else this->green = (unsigned char)value;
			for (int j = 0; j < 3; ++j) a[j] = '\0';
			cur = 0;
			++cnt;
		}
		else if (charColor[i] == ')')
			this->blue = (unsigned char)atoi(a);
		else
		{
			a[cur++] = charColor[i];
		}
	return *this;
}

RGB_Color::~RGB_Color() {}

void convert_RGB_to_unsigned_char(unsigned char* a, const RGB_Color& color)
{
	a[0] = color.red;
	a[1] = color.green;
	a[2] = color.blue;
}

int convert_char_to_int(char* s, int begin, int end, const char endCharacter)
{
	int result, firstPos = begin, cur = 0;
	bool positive = true;
	char a[5];
	a[4] = '\0';
	for (int i = begin; i <= end; ++i)
		if (s[i] == ' ') ++firstPos;
		else break;

	if (s[firstPos] == '-')
	{
		positive = !positive;
		firstPos++;
	}
	for(int i = firstPos; i <= end; ++i)
		if (s[i] == endCharacter)
		{
			a[cur] = '\0';
			result = atoi(a);
			if (!positive)
				result = -result;
			break;
		}
		else
		{
			a[cur++] = s[i];
		}
	return result;
}