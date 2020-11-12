#include "stdafx.h"
#include "General.h"

void convert_RGB_to_unsigned_char(unsigned char* a, const RGB_Color& color)
{
	a[0] = color.red;
	a[1] = color.green;
	a[2] = color.blue;
}

void removeLastCharacters(char* fileName, int charsToDelete)
{
	char cContent[MAXLENGTH];
	string sContent = "";
	fstream file_op(fileName, ios::in);
	while (file_op.getline(cContent, MAXLENGTH))
	{
		sContent += cContent;
		sContent += "\n";
	}
	file_op.close();
	sContent.erase(sContent.end() - charsToDelete, sContent.end());
	ofstream outFile;
	outFile.open(fileName);
	outFile.write(sContent.c_str(), sContent.length());
	outFile.close();
}

bool isNewCommand(char* s)
{
	return (s[0] < '1' || s[0] > '9');
}

WCHAR* convertStringToWCHAR(string text)
{
	if (text == "")
		text = "Times New Roman";
	size_t newsize = text.length() + 1;
	char* tmp = new char[newsize];
	strcpy(tmp, text.c_str());
	WCHAR* wcstring = new WCHAR[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, tmp, _TRUNCATE);
	delete[]tmp;
	return wcstring;
}