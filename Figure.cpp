#include "stdafx.h"
#include "Figure.h"

#define MAXLENGTH 5000

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

//Figure
Figure::Figure(RGB_Color stroke,
	int strokeWidth,
	float strokeOpacity,
	char transformOrder,
	myPoint translate,
	char rotate) : Stroke(stroke, strokeWidth, strokeOpacity),
	Transformer(transformOrder, translate, rotate) {}

Figure::Figure(const vector<char>& transformOrder,
	const vector<myPoint>& translate,
	const vector<char>& rotate,
	RGB_Color stroke,
	int strokeWidth,
	float strokeOpacity) : Stroke(stroke, strokeWidth, strokeOpacity),
	Transformer(transformOrder, translate, rotate) {}

string Figure::getXmlCode()
{
	string Code;
	Code += this->getStrokeCode();
	Code += this->getTransformerCode();
	return Code;
}

bool Figure::drawToFile(char* fileName)
{
	FILE* f = fopen(fileName, "r");
	if (f == NULL)
	{
		return false;
		//cout << "Draw figure to file unsuccessfully" << endl;
	}

	fclose(f);

	removeLastCharacters(fileName);
	f = fopen(fileName, "a");
	string Code = this->getXmlCode();
	fseek(f, 0, SEEK_END);
	fputs(Code.c_str(), f);
	fputs("</svg>", f);

	fclose(f);
	//cout << "Draw figure to file successfully" << endl;
	return true;
}

bool Figure::removeFromFile(char* fileName)
{
	FILE* f = fopen(fileName, "r");
	if (f == NULL)
		return false;

	FILE* tmp = fopen("tmp.svg", "w");

	string Code = this->getXmlCode();
	char* delCode = new char[Code.length() + 1];
	strcpy(delCode, Code.c_str());
	char* myLine = new char[MAXLENGTH];
	while (fgets(myLine, MAXLENGTH, f))
	{
		if (strcmp(myLine, delCode) != 0)
		{
			fputs(myLine, tmp);
		}
	}
	fclose(tmp);
	fclose(f);
	delete delCode;
	delete myLine;
	int res = remove(fileName);
	if (res == 0)
	{
		//cout << "Remove figure successfully" << endl;
		rename("tmp.svg", fileName);
	}
	else
	{
		//cout << "Remove figure unsuccessfully" << endl;
		remove("tmp.svg");
	}
	return true;
}
Figure::~Figure() {}

//Fill Figure
FillFigure::FillFigure(RGB_Color stroke,
	int strokeWidth,
	float strokeOpacity,
	RGB_Color fill,
	float fillOpacity,
	char transformOrder,
	myPoint translate,
	char rotate) : Figure(stroke, strokeWidth, strokeOpacity, transformOrder, translate, rotate),
	Fill(fill, fillOpacity) {}

FillFigure::FillFigure(const vector<char>& transformOrder,
	const vector<myPoint>& translate,
	const vector<char>& rotate,
	RGB_Color stroke,
	int strokeWidth,
	float strokeOpacity,
	RGB_Color fill,
	float fillOpacity) : Figure(transformOrder, translate, rotate, stroke, strokeWidth, strokeOpacity),
	Fill(fill, fillOpacity) {}

string FillFigure::getXmlCode()
{
	string Code;
	Code += Figure::getXmlCode();
	Code += Fill::getFillCode();
	return Code;
}

void Figure::convertFromCString(xml_attribute<>* attr)
{
	if (strcmp(attr->name(), "stroke") == 0)
	{
		RGB_Color* strokeColor = new RGB_Color;
		strokeColor->setColor(attr->value());
		this->setStroke(*strokeColor);
		delete strokeColor;
	}
	else if (strcmp(attr->name(), "stroke-width") == 0)
		this->setStrokeWidth(atoi(attr->value()));
	else if (strcmp(attr->name(), "stroke-opacity") == 0)
		this->setStrokeOpacity(atof(attr->value()));
	else if (strcmp(attr->name(), "transform") == 0)
	{
		this->setTransformer(attr->value(), INVERSE_ORDER);
	}
}

void FillFigure::convertFromCString(xml_attribute<>* attr)
{
	if (strcmp(attr->name(), "fill") == 0)
	{
		RGB_Color* fillColor = new RGB_Color;
		fillColor->setColor(attr->value());
		this->setFill(*fillColor);
		delete fillColor;
	}
	else if (strcmp(attr->name(), "fill-opacity") == 0)
		this->setFillOpacity(atof(attr->value()));
	else 
		Figure::convertFromCString(attr);
}

FillFigure::~FillFigure() {}