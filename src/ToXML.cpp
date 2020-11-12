#pragma once

#include "stdafx.h"
#include "Figure.h"
#include "Line.h"
#include "Rectagle.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Polygon.h"
#include "Polyline.h"
#include "Text.h"
#include "Group.h"
#include "General.h"

//Fill
string Fill::getFillCode()
{
	string Code;
	ostringstream buffer;
	Code += "fill=";
	Code += this->m_fill.getCode();
	return Code;
}

//Fill Opacity
string FillOpacity::getFillOpacityCode()
{
	string Code;
	ostringstream buffer;
	if (this->m_fillOpacity != 1.0)
	{
		Code += "fill-opacity=\"";
		buffer << this->m_fillOpacity;
		Code += buffer.str();
		Code += "\" ";
	}
	return Code;
}

//Stroke
string Stroke::getStrokeCode()
{
	ostringstream buffer;
	string Code = "stroke=";
	Code += this->m_stroke.getCode();
	return Code;
}

//Stroke Opacity
string StrokeOpacity::getStrokeOpacityCode()
{
	ostringstream buffer;
	string Code;

	if (this->m_strokeOpacity != 1.0)
	{
		Code += "stroke-opacity=\"";
		buffer << this->m_strokeOpacity;
		Code += buffer.str();
		Code += "\" ";
	}
	return Code;
}

//Stroke Width
string StrokeWidth::getStrokeWidthCode()
{
	ostringstream buffer;
	string Code = "stroke-width=\"";
	buffer << (int) this->m_strokeWidth;
	Code += buffer.str();
	buffer.str("");
	Code += "\" ";
	return Code;
}


//Figure
string Figure::getXmlCode()
{
	string Code;
	Code += dynamic_cast<Stroke*>(this->m_attributes["stroke"])->getStrokeCode();
	Code += dynamic_cast<StrokeWidth*>(this->m_attributes["stroke-width"])->getStrokeWidthCode();
	Code += dynamic_cast<StrokeOpacity*>(this->m_attributes["stroke-opacity"])->getStrokeOpacityCode();
	Code += dynamic_cast<ListTransform*>(this->m_attributes["transform"])->getTransformCode();
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

//Fill Figure
string FillFigure::getXmlCode()
{
	string Code;
	Code += Figure::getXmlCode();
	Code += dynamic_cast<Fill*>(this->m_attributes["fill"])->getFillCode();
	Code += dynamic_cast<FillOpacity*>(this->m_attributes["fill-opacity"])->getFillOpacityCode();
	return Code;
}

//Line
string myLine::getXmlCode()
{
	ostringstream buffer;
	string Code = "<line x1=\"";
	buffer << this->getFirstPoint().x;
	Code += buffer.str();
	buffer.str("");
	Code += "\" y1=\"";
	buffer << this->getFirstPoint().y;
	Code += buffer.str();
	buffer.str("");

	Code += "\" x2=\"";
	buffer << this->getSecondPoint().x;
	Code += buffer.str();
	buffer.str("");
	Code += "\" y2=\"";
	buffer << this->getSecondPoint().y;
	Code += buffer.str();
	buffer.str("");

	Code += "\" ";
	Code += Figure::getXmlCode();

	Code += "/>\n";
	return Code;
}

//Rectangle
string myRectangle::getXmlCode()
{
	ostringstream buffer;
	string Code = "<rect x=\"";
	buffer << this->getTopLeft().x;
	Code += buffer.str();
	buffer.str("");
	Code += "\" y=\"";
	buffer << this->getTopLeft().y;
	Code += buffer.str();
	buffer.str("");

	Code += "\" width=\"";
	buffer << this->getWidth();
	Code += buffer.str();
	buffer.str("");
	Code += "\" height=\"";
	buffer << this->getHeight();
	Code += buffer.str();
	buffer.str("");
	Code += "\" ";
	Code += FillFigure::getXmlCode();

	Code += "/>\n";
	return Code;
}

//Circle
string myCircle::getXmlCode()
{
	ostringstream buffer;
	string Code = "<circle cx=\"";
	buffer << this->getCenter().x;
	Code += buffer.str();
	buffer.str("");
	Code += "\" cy=\"";
	buffer << this->getCenter().y;
	Code += buffer.str();
	buffer.str("");

	Code += "\" r=\"";
	buffer << this->getR();
	Code += buffer.str();
	buffer.str("");
	Code += "\" ";
	Code += FillFigure::getXmlCode();

	Code += "/>\n";
	return Code;
}

//Ellipse
string myEllipse::getXmlCode()
{
	ostringstream buffer;
	string Code = "<ellipse cx=\"";
	buffer << this->getCenter().x;
	Code += buffer.str();
	buffer.str("");
	Code += "\" cy=\"";
	buffer << this->getCenter().y;
	Code += buffer.str();
	buffer.str("");

	Code += "\" rx=\"";
	buffer << this->getRx();
	Code += buffer.str();
	buffer.str("");
	Code += "\" ry=\"";
	buffer << this->getRy();
	Code += buffer.str();
	buffer.str("");
	Code += "\" ";
	Code += FillFigure::getXmlCode();

	Code += "/>\n";
	return Code;
}

//Polyline
string myPolyline::getXmlCode()
{
	ostringstream buffer;
	string Code = "<polyline ";
	Code += FillFigure::getXmlCode();

	Code += "points=\"";
	for (int i = 0; i < this->m_pointData.size(); ++i)
	{
		buffer << this->m_pointData[i].x;
		Code += buffer.str();
		buffer.str("");
		Code += ",";
		buffer << this->m_pointData[i].y;
		Code += buffer.str();
		buffer.str("");
		Code += " ";
	}

	Code.back() = '\"';
	Code += " />\n";
	return Code;
}

//Polygon
string myPolygon::getXmlCode()
{
	ostringstream buffer;
	string Code = "<polygon ";
	Code += FillFigure::getXmlCode();

	Code += "points=\"";
	for (int i = 0; i < this->m_pointData.size(); ++i)
	{
		buffer << this->m_pointData[i].x;
		Code += buffer.str();
		buffer.str("");
		Code += ",";
		buffer << this->m_pointData[i].y;
		Code += buffer.str();
		buffer.str("");
		Code += " ";
	}

	Code.back() = '\"';
	Code += " />\n";
	return Code;
}

//Text
string myText::getXmlCode()
{
	return "";
}

//Group
string myGroup::getXmlCode()
{
	string Code = "Group:\n";
	for (int i = 0; i < this->m_listFigure.size(); ++i)
	{
		Code += this->m_listFigure[i]->getXmlCode();
	}
	return Code;
}