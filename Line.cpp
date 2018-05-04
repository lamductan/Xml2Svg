#include "stdafx.h"
#include "Line.h"

//myLine
myLine::myLine() {}

myLine::myLine(myPoint firstPoint, myPoint secondPoint,
	RGB_Color stroke,
	int strokeWidth,
	float strokeOpacity,
	int transformOrder,
	myPoint translate,
	int rotate) : Figure(stroke, strokeWidth, strokeOpacity, transformOrder, translate, rotate)
{
	this->m_firstPoint = firstPoint;
	this->m_secondPoint = secondPoint;
}

myLine::myLine(myPoint firstPoint, myPoint secondPoint,
	const vector<char>& transformOrder,
	const vector<myPoint>& translate,
	const vector<char>& rotate,
	RGB_Color stroke,
	int strokeWidth,
	float strokeOpacity) : Figure(transformOrder, translate, rotate, stroke, strokeWidth, strokeOpacity)
{
	this->m_firstPoint = firstPoint;
	this->m_secondPoint = secondPoint;
}

myLine::myLine(xml_node<>* node)
{
	for (xml_attribute<> *attr = node->first_attribute();
		attr; attr = attr->next_attribute())
	{
		this->convertFromCString(attr);
	}
}

void myLine::setPoints(myPoint firstPoint, myPoint secondPoint)
{
	this->m_firstPoint = firstPoint;
	this->m_secondPoint = secondPoint;
}

void myLine::draw(CImg<unsigned char>& img)
{
	unsigned char color[3];
	convert_RGB_to_unsigned_char(color, this->m_stroke);
	myPoint firstPoint(this->m_firstPoint.transform(this->m_translate, this->m_rotate, this->m_transformOrder));
	myPoint secondPoint(this->m_secondPoint.transform(this->m_translate, this->m_rotate, this->m_transformOrder));

	for (int i = 0; i < this->m_strokeWidth; ++i)
		img.draw_line(firstPoint.x + i, firstPoint.y + i, secondPoint.x + i, secondPoint.y + i,
			color, this->m_strokeOpacity);
}

void myLine::draw(HDC& hdc)
{
	Graphics graphics(hdc);

	Pen pen(Color(BYTE(this->m_strokeOpacity * 255), this->m_stroke.red, this->m_stroke.green, this->m_stroke.blue), this->m_strokeWidth);

	myPoint myFirstPoint(this->m_firstPoint.transform(this->m_translate, this->m_rotate, this->m_transformOrder));
	myPoint mySecondPoint(this->m_secondPoint.transform(this->m_translate, this->m_rotate, this->m_transformOrder));

	graphics.DrawLine(&pen, myFirstPoint.x, myFirstPoint.y, mySecondPoint.x, mySecondPoint.y);
}

string myLine::getXmlCode()
{
	ostringstream buffer;
	string Code = "<line x1=\"";
	buffer << this->m_firstPoint.x;
	Code += buffer.str();
	buffer.str("");
	Code += "\" y1=\"";
	buffer << this->m_firstPoint.y;
	Code += buffer.str();
	buffer.str("");

	Code += "\" x2=\"";
	buffer << this->m_secondPoint.x;
	Code += buffer.str();
	buffer.str("");
	Code += "\" y2=\"";
	buffer << this->m_secondPoint.y;
	Code += buffer.str();
	buffer.str("");

	Code += "\" ";
	Code += Figure::getXmlCode();

	Code += "/>\n";
	return Code;
}

void myLine::convertFromCString(xml_attribute<>* attr)
{
	if (strcmp(attr->name(), "x1") == 0)
		this->m_firstPoint.x = convert_char_to_int(attr->value(), 0, 5);
	else if (strcmp(attr->name(), "y1") == 0)
		this->m_firstPoint.y = convert_char_to_int(attr->value(), 0, 10);
	else if (strcmp(attr->name(), "x2") == 0)
		this->m_secondPoint.x = convert_char_to_int(attr->value(), 0, 10);
	else if (strcmp(attr->name(), "y2") == 0)
		this->m_secondPoint.y = convert_char_to_int(attr->value(), 0, 10);
	else
		Figure::convertFromCString(attr);
}

myLine::~myLine() {}
